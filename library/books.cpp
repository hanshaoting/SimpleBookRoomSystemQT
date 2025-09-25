#include "books.h"

Books::Books()
{

}
Books::~Books(){}
Books::Books(const Books&book)//拷贝构造函数
{
    m_strBookName=book.m_strBookName;
    m_strBookNumber=book.m_strBookNumber;
    m_strAuthorName=book.m_strAuthorName;
    m_dateTime=book.m_dateTime;
    m_strPress=book.m_strPress;
    m_nSum=book.m_nSum;
}

void Books::SaveBook(QTextStream &aStream)//写入文件
{
    aStream<<m_strBookName<<"\n";
    aStream<<m_strBookNumber<<"\n";
    aStream<<m_strAuthorName<<"\n";
    aStream<<m_strPress<<"\n";
    aStream<<m_dateTime.year()<<" "<<m_dateTime.month()<<" "<<m_dateTime.day()<<"\n";
    aStream<<m_nSum<<"\n";
    for(int i=0;i<m_nSum;i++)
    {
        aStream<<m_register[i].m_strRegisterNumber<<"\n";
        aStream<<m_register[i].m_strLoanNumber<<"\n";
        aStream<<m_register[i].m_bSendOut<<"\n";
       aStream<<m_register[i].m_dateLoan.year()<<" "<<m_register[i].m_dateLoan.month()<<" "<<m_register[i].m_dateLoan.day()<<"\n";

    }

}

void Books::ReadBook(QTextStream &aStream)//读文件
{
    aStream >>m_strBookName;
    qDebug()<<"bookname="<<m_strBookName;
    aStream >>m_strBookNumber;
    aStream >>m_strAuthorName;
    aStream >>m_strPress;
    int year,month,day;
    aStream >>year>>month>>day;
    m_dateTime.setDate(year,month,day);
    aStream >>m_nSum;
    m_register.resize(m_nSum);
    for(int i=0;i<m_nSum;i++)
    {
        //依次读入每册数的登记信息
        aStream>>m_register[i].m_strRegisterNumber;

        aStream>>m_register[i].m_strLoanNumber;

        aStream>>m_register[i].m_bSendOut;

        int y,m,d;
        aStream>>y>>m>>d;
        m_register[i].m_dateLoan.setDate(y,m,d);

    }

}

