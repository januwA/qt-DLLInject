#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ManualMap.cpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    processListWIndow = new ProcessListWIndow(this);
    processListWIndow->setWindowTitle("进程列表");
    processListWIndow->setAttribute(Qt::WA_DeleteOnClose);
    connect( processListWIndow,  SIGNAL(destroyed()), this, SLOT(process_list_wIndow_close()) );
    processListWIndow->show();
}

void MainWindow::process_list_wIndow_close()
{
    ui->lineEdit->setText(  processListWIndow->selectText );
    selectText = processListWIndow->selectText;
}

void MainWindow::on_pushButton_2_clicked()
{
    QString filters = "DLL (*.dll)";
    QString filePath = QFileDialog::getOpenFileName(this, "Open File", NULL, filters);
    if(filePath == "") return;
    ui->lineEdit_2->setText( filePath );
    dllpath = filePath;
}

void MainWindow::on_pushButton_3_clicked()
{
    if( selectText.isEmpty() )
    {
        QMessageBox::information(this, NULL, "选择进程!!!");
        return;
    }

    if( dllpath.isEmpty() )
    {
        QMessageBox::information(this, NULL, "选择DLL文件!!!");
        return;
    }

    QString pidHex = selectText.mid(0, 8);
    bool bStatus = false;
    uint pid =  pidHex.toUInt(&bStatus, 16);

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (!hProcess) {
        QMessageBox::information(this, NULL, "打开进程失败!!!");
        return;
    }

    if(ManualMap(this, hProcess, ui->lineEdit_2->text().toStdString() ))
    {
        // QMessageBox::information(this, NULL, "注入成功");
    }
    else
    {
        QMessageBox::information(this, NULL, "注入失败");
    }

    CloseHandle(hProcess);
}
