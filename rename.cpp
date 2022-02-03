#include "rename.h"
#include "ui_rename.h"

Rename::Rename(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Rename)
{
    ui->setupUi(this);

    connect(this, SIGNAL(sendNewName(QString)), parent, SLOT(receiveNewName(QString)));

}
Rename::Rename(QWidget *parent, QString currentName) : Rename(parent)
{
    ui->name->setPlainText(currentName);
    ui->name->selectAll();
}

Rename::~Rename()
{
    delete ui;
}

void Rename::on_buttonBox_accepted()
{
    sendNewName(ui->name->toPlainText());
    this->close();
}


void Rename::on_buttonBox_rejected()
{
    this->close();
}

