#include "processlistwindow.h"
#include "ui_processlistwindow.h"
#include "mainwindow.h"

ProcessListWIndow::ProcessListWIndow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProcessListWIndow)
{
    ui->setupUi(this);
    connect(
                ui->lineEdit, SIGNAL( textEdited(QString) ),
                this, SLOT(list_filter(QString))
            );

    HANDLE hSnap = CreateToolhelp32Snapshot(PROCESS_ALL_ACCESS, 0);
    if( hSnap != INVALID_HANDLE_VALUE )
    {
        PROCESSENTRY32 pe;
        pe.dwSize = sizeof(pe);
        if( Process32First(hSnap, &pe) )
        {
            DWORD curID = GetCurrentThreadId();
            do{
                if(pe.th32ProcessID && pe.th32ProcessID != curID)
                {
                    QListWidgetItem *it = new QListWidgetItem(
                                /* QIcon(""), */
                                PaddingZero(QString::number(pe.th32ProcessID, 16)).toUpper() +
                                "-" +
                                QString::fromWCharArray(pe.szExeFile),
                                ui->list
                     );
                    ui->list->addItem(it);
                    //printf("name: %ls, id: %d\n",pe.szExeFile,pe.th32ProcessID);
                }
            }while( Process32Next(hSnap, &pe) );
        }
    }
    CloseHandle(hSnap);
}

ProcessListWIndow::~ProcessListWIndow()
{
    delete ui;
}

QString ProcessListWIndow::PaddingZero(QString str)
{
    while(true)
    {
        if(str.length() >= 8)
        {
            return str;
        }
        str = "0"+str;
    }
}

void ProcessListWIndow::on_pushButton_clicked()
{
    selectText = ui->list->currentItem()->text();
    this->close();
}

void ProcessListWIndow::list_filter(QString filter_string)
{
    for(int row(0); row < ui->list->count(); row++ )
        ui->list->item(row)->setHidden(true);

    QList<QListWidgetItem*> matches ( ui->list->findItems(filter_string, Qt::MatchFlag::MatchContains) );
    for(QListWidgetItem* item : matches)
        item->setHidden(false);
}
