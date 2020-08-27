#ifndef PROCESSLISTWINDOW_H
#define PROCESSLISTWINDOW_H

#include <QDialog>
#include <windows.h>
#include <psapi.h>
#include <tlhelp32.h>
#include <iostream>
#include <QDebug>
#include <qpixmap.h>

namespace Ui {
class ProcessListWIndow;
}

class ProcessListWIndow : public QDialog
{
    Q_OBJECT

public:
    QString selectText;
    explicit ProcessListWIndow(QWidget *parent = nullptr);
    ~ProcessListWIndow();
    QString PaddingZero(QString str);

private slots:
    void on_pushButton_clicked();
    void list_filter(QString filter_string);

private:
    Ui::ProcessListWIndow *ui;
};

#endif // PROCESSLISTWINDOW_H
