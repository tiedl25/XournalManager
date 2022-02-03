#ifndef RENAME_H
#define RENAME_H

#include <QDialog>

#include "mainwindow.h"

namespace Ui {
class Rename;
}

class Rename : public QDialog
{
    Q_OBJECT

public:
    explicit Rename(QWidget *parent = nullptr);
    Rename(QWidget *parent, QString currentName);
    ~Rename();

signals:
    void sendNewName(const QString &newName);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Rename *ui;
};

#endif // RENAME_H
