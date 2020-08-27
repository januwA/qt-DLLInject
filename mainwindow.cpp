#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "injectMethods/ManualMap.cpp"
#include "injectMethods/NormalInject.cpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initMenu();
    initComboBoxItems();
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
    if (!hProcess)
    {
        QMessageBox::information(this, NULL, "打开进程失败!!!");
        return;
    }

    int selectIndex = ui->comboBox->currentIndex();
    if(selectIndex == 0)
    {
        if(!NormalInject(hProcess,dllpath.toStdString().c_str() ))
        {
            QMessageBox::information(this, NULL, "注入失败");
        }
    }
    else if(selectIndex == 1)
    {

        if(!ManualMap(this, hProcess, dllpath.toStdString() ))
        {
            QMessageBox::information(this, NULL, "注入失败");
        }
    }

    CloseHandle(hProcess);
}

void MainWindow::on_menu1_1()
{

    QString URL = "https://github.com/januwA/qt-DLLInject";
    QDesktopServices::openUrl(QUrl(URL.toLatin1()));
}
void MainWindow::on_menu1_2()
{
    QString URL = "https://github.com/januwA/qt-DLLInject/releases";
    QDesktopServices::openUrl(QUrl(URL.toLatin1()));
}
void MainWindow::initComboBoxItems()
{
    ui->comboBox->addItem("普通的线程注入");
    ui->comboBox->addItem("手动映射DLL");
}

void MainWindow::initMenu()
{
    connect(ui->actionasd_1, SIGNAL(triggered()), this, SLOT(on_menu1_1()));
    connect(ui->actionasd_2, SIGNAL(triggered()), this, SLOT(on_menu1_2()));
    ui->actionasd_3->setText(version);
}
