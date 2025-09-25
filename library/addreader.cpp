#include "addreader.h"
#include "ui_addreader.h"
#include <QButtonGroup>
#include<QMessageBox>
addReader::addReader(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addReader)
{
    ui->setupUi(this);

    QButtonGroup *m_btnGroup1 = new QButtonGroup;
    m_btnGroup1->addButton(ui->radioButton);
    m_btnGroup1->addButton(ui->radioButton_2);

    ui->radioButton->setChecked(1);

}

addReader::~addReader()
{
    delete ui;
}

QString addReader::LoanNum()
{
    return ui->lineEdit->text();
}

QString addReader::Name()
{
    return ui->lineEdit_2->text();
}

int addReader::Gender()
{
    // 如果按钮组内ID为0的单选按钮被选中
    if(ui->radioButton->isChecked() )
    {
        return 1;
    }
else
        return 0;
}
QString addReader::Email()
{
    return ui->lineEdit_3->text();
}

void addReader::on_buttonBox_accepted()
{
    if(LoanNum().isEmpty()||Name().isEmpty())
    {
        QMessageBox::critical(this,"注意","输入不能为空！");
        reject();
    }
}

