#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <windows.h>
#include <psapi.h>
#include <tlhelp32.h>
#include <iostream>
#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include "processlistwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ProcessListWIndow *processListWIndow;
    QString str;
    QString selectText;
    QString dllpath;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_pushButton_clicked();
    void process_list_wIndow_close();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
