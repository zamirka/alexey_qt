#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#include "item.h"
#include "solution.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_dlgOpenData_clicked();

    void on_cmbxLevel1_currentIndexChanged(const QString &arg1);

    void on_cmbxLevel2_currentIndexChanged(int index);

    void on_cmbxLevel3_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    QVector<Item> extractData(QJsonObject obj);
    QVector<Solution> getSolutions(QJsonObject obj);
    QVector<Item> getItemsForCombo(QString parentName, QVector<Item> data);
    QVector<Item> allData;
};

#endif // MAINWINDOW_H
