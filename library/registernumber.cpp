#include "registernumber.h"
#include "ui_registernumber.h"

registernumber::registernumber(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::registernumber)
{
    ui->setupUi(this);
}

registernumber::~registernumber()
{
    delete ui;
}
QString registernumber::Number()
{
    return ui->lineEdit->text();
}
