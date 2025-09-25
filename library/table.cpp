#include "table.h"
#include "ui_table.h"

table::table(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::table)
{
    ui->setupUi(this);
}

table::~table()
{
    delete ui;
}
void table::ShowTable(Books& tempbook)//展示书籍基本信息表格
    {


        ui->tableWidget->setRowCount(1);
        ui->tableWidget->setColumnCount(5);
        ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"书名"<<"书目编号"<<"作者"<<"出版社"<<"出版时间");
        //使得表格的 高度，可以跟随主窗口的缩放而自适应变化。
        ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        for(int col=0;col<5;col++)//**
        {
        ui->tableWidget->setItem(0,col++,new QTableWidgetItem(tempbook.m_strBookName));
        ui->tableWidget->setItem(0,col++,new QTableWidgetItem(tempbook.m_strBookNumber));
        ui->tableWidget->setItem(0,col++,new QTableWidgetItem(tempbook.m_strAuthorName));
        ui->tableWidget->setItem(0,col++,new QTableWidgetItem(tempbook.m_strPress));
        ui->tableWidget->setItem(0,col++,new QTableWidgetItem(tempbook.m_dateTime.toString()));
        }


    }

    void table::ShowLendTable(Books& tempbook,int a)
    {
        int row=ui->tableWidget->rowCount();
        ui->tableWidget->setColumnCount(5);
        ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"借书证号"<<"书名"<<"书目编号"<<"所借书册登记号"<<"借阅时间");
        ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableWidget->insertRow(row);


        for(int col=0;col<5;col++)
        {
            ui->tableWidget->setItem(row,col++,new QTableWidgetItem(tempbook.m_register[a].m_strLoanNumber));
            ui->tableWidget->setItem(row,col++,new QTableWidgetItem(tempbook.m_strBookName));
            ui->tableWidget->setItem(row,col++,new QTableWidgetItem(tempbook.m_strBookNumber));
            ui->tableWidget->setItem(row,col++,new QTableWidgetItem(tempbook.m_register[a].m_strRegisterNumber));
            ui->tableWidget->setItem(row,col++,new QTableWidgetItem(tempbook.m_register[a].m_dateLoan.toString()));
        }

    }
