#include "library.h"
#include <QFile>
#include <QTextStream>
#include <QtCore5Compat/QTextCodec>

Library::Library()
{
}


int Library::getSize()
{
    return m_books.size();//返回书籍列表大小
}

Books* Library::getBook(int index)
{
    return m_books.at(index);//返回一本书（指针）
}


void Library::addBook(Books* bk)//增加书籍
{
    bk->m_register.resize(bk->m_nSum);//设置登记信息列表的大小，等于该种书籍的库存数量
    m_books.push_back(bk);//将新书添加到列表中
    for(int i=0;i<bk->m_nSum;i++)//创建登记号
    {
        bk->m_register[i].m_strRegisterNumber=bk->m_strBookName+QString::number(i);//书名+序号，便于后续还书。
    }
}

void Library::deleteBook(int a)
{
    m_books.erase(m_books.begin() + a);//从书籍列表移除序号a的书籍

}

void Library::addReader(reader* tempreader)//添加读者
{
    m_readers.push_back(tempreader);
}



int Library::NameSearch(QString str)//搜索书名
{

    for(int i=0;i<getSize();i++)
    {
        QString index=m_books[i]->m_strBookName;
        if(index==str)
        {
            return i;//返回书籍序号
        }


    }
    return -1;//未找到返回-1
}

int Library::NumberSearch(QString str)//搜索书目编号
{
    qDebug()<<"getSize="<<getSize();

    for(int i=0;i<getSize();i++)
    {

        QString index=m_books[i]->m_strBookNumber;
        if(index==str)
        {
            return i;//返回书籍序号
        }

    }
    return -1;

}

int Library::LoanSearch(QString str)//搜索读者
{
    for(int i=0;i<m_readers.size();i++)
    {
        if(m_readers[i]->m_strLoanNum==str)
            return i;//返回读者序号
    }
    return -1;
}



int Library::ReadBookFromFile(const QString &aReadFileName)
{
    QFile aFile(aReadFileName);//得到文件路径信息
    if(!aFile.exists()) //文件不存在
        return 0;
    if(!aFile.open(QIODevice::ReadOnly | QIODevice::Text)) //只能以文本方式打开
        return 0;

    QTextStream stream(&aFile);
    //指定编码
    stream.setEncoding(QStringConverter::Utf8);
    //初始化

    //开始逐个读取书籍信息
    int sum;
    stream>>sum;//读取文件中的书籍种数
    if(sum>0)
    {
        for(int i=0;i<sum;i++)
        {
            //读取书籍信息，添加到书籍列表中
            Books* tempbook=new Books();
            tempbook->ReadBook(stream);
            m_books.push_back(tempbook);

        }
    }
    aFile.close();
    return sum;
}

bool Library::SaveBookToFile(const QString &aSaveFileName)
{
    QFile aFile(aSaveFileName);
    if(!aFile.open(QIODevice::WriteOnly| QIODevice::Text)) //保存为文本
        return false;

    QTextStream stream(&aFile);
    //指定编码
    stream.setEncoding(QStringConverter::Utf8);


    stream<<m_books.size()<<"\n";//写入书籍种数
    if(m_books.size()>0)
    {
        for(int i=0;i<m_books.size();i++)
        {
            m_books[i]->SaveBook(stream);
        }
    }
    aFile.close();
    return true;
}


int Library::getReaderSum()
{
    return m_readers.size();
}

reader* Library::getReader(int a)//返回列表中的reader
{
    return m_readers[a];
}
