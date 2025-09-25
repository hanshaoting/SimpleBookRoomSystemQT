#include "loannum.h"
#include "ui_loannum.h"
#include<QMessageBox>
LoanNum::LoanNum(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoanNum)
{
    ui->setupUi(this);
}

LoanNum::~LoanNum()
{
    delete ui;
}

QString LoanNum::Name()
{
   return  ui->lineEdit->text();
}

QDate LoanNum::Date()
{
    return ui->dateEdit->date();
}
void LoanNum::setUI()
{
    ui->label_2->hide();
    ui->dateEdit->hide();
}
void LoanNum::on_buttonBox_accepted()
{
    //检查输入是否为空
    QString index=ui->lineEdit->text();
    if(index.isEmpty())
    {
        QMessageBox::critical(this,"注意","输入不能为空！");
        reject();
    }
}

