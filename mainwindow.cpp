#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_dlgOpenData_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(0, QString(), QString(),
                                                     tr("JSON Database (*.json)"));
    QString data;
    QFile database;
    database.setFileName(fileName);
    database.open(QIODevice::ReadOnly | QIODevice::Text);
    data = database.readAll();
    database.close();

    QJsonDocument fullDocument = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject globalObject = fullDocument.object();

    allData = extractData(globalObject);

    ui->cmbxLevel1->clear();
    foreach (const Item item, allData)
    {
       ui->cmbxLevel1->addItem(item.name);
    }
    ui->cmbxLevel1->setEnabled(true);
}

QVector<Item> MainWindow::extractData(QJsonObject obj)
{
    QVector<Item> items;
    QJsonArray objItemsArray = obj["items"].toArray();
    if(!objItemsArray.isEmpty())
    {
        foreach (const QJsonValue & value, objItemsArray)
        {
            QJsonObject vObj = value.toObject();
            Item i;
            i.name = vObj["name"].toString();
            i.items = extractData(vObj);
            i.solutions = getSolutions(vObj);
            items.append(i);
        }
    }
    return items;
}

QVector<Solution> MainWindow::getSolutions(QJsonObject obj)
{
    QVector<Solution> solutions;
    QJsonArray objSolutionsArray = obj["solutions"].toArray();
    if(!objSolutionsArray.isEmpty())
    {
        foreach (const QJsonValue & value, objSolutionsArray)
        {
            QJsonObject vObj = value.toObject();
            Solution s;
            s.step = vObj["step"].toInt();
            s.description = vObj["description"].toString();
            s.image = vObj["image"].toString();
            solutions.append(s);
        }
    }
    return solutions;
}

void MainWindow::on_cmbxLevel1_currentIndexChanged(const QString &arg1)
{
    ui->cmbxLevel2->clear();
    QString selectedLevel1 = ui->cmbxLevel1->currentText();
    QVector<Item> level2Array = getItemsForCombo(selectedLevel1, allData);
    foreach (const Item item, level2Array)
    {
       ui->cmbxLevel2->addItem(item.name);
    }
    ui->cmbxLevel2->setEnabled(true);

}

QVector<Item> MainWindow::getItemsForCombo(QString parentName, QVector<Item> data)
{
    QVector<Item> empty;
    foreach (const Item item, data)
    {
       if(item.name == parentName)
       {
           return item.items;
       }
       if(!item.items.isEmpty())
       {
           QVector<Item> found = getItemsForCombo(parentName, item.items);
           if(!found.isEmpty())
           {
               return found;
           }
       }
    }
    return empty;
}

void MainWindow::on_cmbxLevel2_currentIndexChanged(int index)
{
    ui->cmbxLevel3->clear();
    QString selectedLevel2 = ui->cmbxLevel2->currentText();
    QVector<Item> level3Array = getItemsForCombo(selectedLevel2, allData);
    foreach (const Item item, level3Array)
    {
       ui->cmbxLevel3->addItem(item.name);
    }
    ui->cmbxLevel3->setEnabled(true);
}

void MainWindow::on_cmbxLevel3_currentIndexChanged(int index)
{
    ui->lwSolutions->clear();
    QString selectedItem = ui->cmbxLevel1->currentText();
    QVector<Item> levelArray = getItemsForCombo(selectedItem, allData);

    selectedItem = ui->cmbxLevel2->currentText();
    levelArray = getItemsForCombo(selectedItem, levelArray);

    selectedItem = ui->cmbxLevel3->currentText();

    foreach (const Item item, levelArray)
    {
        if(item.name == selectedItem)
        {
            foreach (const Solution s, item.solutions)
            {
                QListWidgetItem *itm = new QListWidgetItem(QString::number(s.step) + ". " + s.description);
                ui->lwSolutions->addItem(itm);
                QString currentPath = QDir::currentPath() + "/data/images/";
                QIcon icon = QIcon(currentPath + s.image);
                itm->setIcon(icon);
            }
        }
    }
    ui->cmbxLevel3->setEnabled(true);
}

