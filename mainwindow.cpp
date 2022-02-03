#include "mainwindow.h"
#include "ui_mainwindow.h"


std::vector<QDir> workspaces; //stores the added directorys to allow access from different functions
int listIndex = 1; //index to connect given item and stored directory in vector

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // read workspaces from file
    QFile file("storage.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        std::cerr << "File is not open" << std::endl;

    }
    QTextStream in(&file);
    while(!in.atEnd())
    {
        addWorkspace(in.readLine());
    }

    file.flush();
    file.close();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::receiveNewName(const QString newName)
{
    QListWidgetItem *item = ui->locations->currentItem();
    QListWidgetItem *xournal = ui->xournals->currentItem();
    QDir dir = getDir(item); //get Directory of Current item
    QString oldPath = dir.path() + "/" + xournal->text() + ".xopp";
    QString newPath = dir.path() + "/" + newName + ".xopp";
    QFile::rename(oldPath, newPath);
    on_locations_itemClicked(item);
}

void MainWindow::on_actionAdd_Location_triggered()
{
    QDir folder = QFileDialog::getExistingDirectory(this);
    if(folder.path() != ".")
    {
        addWorkspace(folder);
        storeWorkspace(folder);
    }
}

void MainWindow::addWorkspace(QDir workspace)
{
    workspaces.push_back(workspace);
    QString folder_name = QString::number(listIndex) + " " + workspace.dirName();
    listIndex++;
    ui->locations->addItem(folder_name);
}

void MainWindow::storeWorkspace(QDir workspace)
{
    QFile file("storage.txt");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
        std::cerr << "File is not open" << std::endl;

    }
    QTextStream out(&file);
    out << workspace.path() << Qt::endl;
    file.flush();
    file.close();
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

//Show Xournals in Workspace
void MainWindow::on_locations_itemClicked(QListWidgetItem *item)
{
    ui->xournals->clear(); //clear previous list of xournals
    QStringList files = getDir(item).entryList(QDir::Files); //get file list of the item directory
    for(QString q : files)
    {
        if(q.contains(".xopp") && !q.contains(".xopp~"))
        {
            q.remove(q.size()-5, 5); //remove .xopp extension
            ui->xournals->addItem(q); //add each file that contains the appendix .xopp to the xournals section
        }
    }
}

// Rename Xournal
void MainWindow::on_xournals_itemDoubleClicked(QListWidgetItem *item)
{
    Rename r(this, item->text()); //call copy constructor with currentName of file
    r.exec();
}

// Add new xournal.xopp to Workspace
void MainWindow::on_actionAdd_Xournal_triggered()
{
    if(ui->locations->currentItem() != nullptr)
    {
        QListWidgetItem *item = ui->locations->currentItem();
        QDir dir = getDir(item); //get Directory of Current item
        QString q = dir.path();
        std::string s = "cp xournal.xopp " + q.toStdString();
        std::system(s.c_str());
        on_locations_itemClicked(item);
    }
}

void MainWindow::on_buttonAdd_Xournal_clicked()
{
    on_actionAdd_Xournal_triggered();
}

// Add new Workspace
void MainWindow::on_buttonAdd_Location_clicked()
{
    on_actionAdd_Location_triggered();
}

//return the directory to a given item
QDir MainWindow::getDir(QListWidgetItem *item)
{
    QString f = item->text();
    int index = f.section(" ", 0, 0).toInt();
    return workspaces.at(index-1);
}

void MainWindow::on_actionUndo_triggered()
{

}


void MainWindow::on_actionRedo_triggered()
{

}
