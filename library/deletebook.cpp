#include "deletebook.h"
#include "ui_deletebook.h"
#include<QMessageBox>
DeleteBook::DeleteBook(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DeleteBook)
{
    ui->setupUi(this);
}

DeleteBook::~DeleteBook()
{
    delete ui;
}
QString DeleteBook::BookName()
{
    QString line=ui->lineEdit->text();
    return line;
}

void DeleteBook::on_comboBox_currentIndexChanged(int index)
{

}




void DeleteBook::on_buttonBox_accepted()
{
    //检查输入是否为空，弹出提示并中止读入

    if(ui->comboBox->currentText()=="书名")
    {
        this->m_nRecord=1;
    }
    else if(ui->comboBox->currentText()=="书目编号")
    {
        this->m_nRecord=2;
    }



    QString line=ui->lineEdit->text();

    if(line.isEmpty())
    {
        QMessageBox::critical(this,"注意","输入不能为空！");
        reject();
    }


}

