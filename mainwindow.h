#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <iostream>
#include <windows.h>
#include <psapi.h>
#include <tlhelp32.h>
#include <winbase.h>

#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <qdesktopservices.h>
#include "processlistwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QString version = "v1.3.1"; // 字符串x.y.z版本号
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
    void on_menu1_1();// 查看源码
    void on_menu1_2();// 查看所有版本

private:
    Ui::MainWindow *ui;
    void initComboBoxItems();
    void initMenu();
};
#endif // MAINWINDOW_H
