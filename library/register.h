#ifndef REGISTER_H
#define REGISTER_H
#include <qstring.h>
#include <QTextStream>
#include<QDate>




class Register
{
public:
    Register();
    virtual ~Register();

    QString m_strRegisterNumber=" ";//登记号
    int m_bSendOut=0;//是否借出：1表示借出，0表示未借出
    QDate m_dateLoan;//借阅日期
    QString m_strLoanNumber=" ";//借书人的借书证号









    //待写：读写文件函数（思考：是写两个函数还是一个








};

#endif // REGISTER_H
