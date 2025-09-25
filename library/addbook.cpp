#include "addbook.h"
#include "ui_addbook.h"
#include"mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
AddBook::AddBook(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddBook)
{
    ui->setupUi(this);
}

AddBook::~AddBook()
{
    delete ui;
}

QString AddBook::BookName()//书名
{

        return ui->lineEdit->text();


}

QString AddBook::AuthorName()
{
    return ui->lineEdit_3->text();
}

QString AddBook::BookNumber()
{
    return ui->lineEdit_2->text();
}

QDate AddBook::Time()
{
    return ui->dateEdit->date();
}

QString AddBook::Press()
{
    return ui->lineEdit_4->text();
}

int AddBook::Sum()
{
    QString s = ui->lineEdit_5->text();
    int height = s.toFloat();
    return  height;


}


void AddBook::on_pushButton_clicked()
{
    //检查输入是否为空，弹出提示信息并中止读入
    QString line=ui->lineEdit->text();
    QString line_2=ui->lineEdit_2->text();
    if(line.isEmpty()||line_2.isEmpty())
    {
        QMessageBox::critical(this,"提示","书名及书目编号不能为空！");
        reject();
    }



    QString s = ui->lineEdit_5->text();
    int height = s.toFloat();
    if(height<=0)
    {
    QMessageBox::critical(this,"提示","库存数量须大于0.");
    reject();
    }

}

