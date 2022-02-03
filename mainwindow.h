#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QLayoutItem>
#include <iostream>
#include <string>
#include <vector>

#include "rename.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    QDir getDir(QListWidgetItem *item);

    void addWorkspace(QDir dir);

    void storeWorkspace(QDir dir);

    std::vector<QDir> workspaces; //stores the added directorys to allow access from different functions
    int listIndex = 1; //index to connect given item and stored directory in vector

public slots:

    void receiveNewName(const QString newName);

private slots:

    void on_actionExit_triggered();

    void on_actionAdd_Location_triggered();

    void on_locations_itemClicked(QListWidgetItem *item);

    void on_xournals_itemDoubleClicked(QListWidgetItem *item);

    void on_actionAdd_Xournal_triggered();

    void on_buttonAdd_Xournal_clicked();

    void on_buttonAdd_Location_clicked();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
