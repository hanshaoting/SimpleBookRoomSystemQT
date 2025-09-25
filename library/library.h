#ifndef LIBRARY_H
#define LIBRARY_H
#include"reader.h"
#include"books.h"
#include<QVector>
class Library
{
public:
    Library();
    void addBook(Books*);//增加书籍
    void deleteBook(int);//删除书籍
    void addReader(reader*);//增加读者
    int LoanSearch(QString);//查找读者信息在读者列表中的位置
    int NumberSearch(QString str);//搜索书目编号
    int NameSearch(QString);//搜索书名
    int getSize();//获得书籍种数
    int getReaderSum();//获得读者总数
    Books* getBook(int);//调用列表中的书籍对象
    reader* getReader(int);//调用列表中的读者信息
    int ReadBookFromFile(const QString& );//读入书籍信息
    bool SaveBookToFile(const QString& );//写入书籍信息

protected:
    QVector<Books*>m_books;//书籍列表
    QVector<reader*>m_readers;//读者列表
};

#endif // LIBRARY_H
