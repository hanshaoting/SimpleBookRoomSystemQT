#ifndef BOOKS_H
#define BOOKS_H
#include <qdatetime.h>
#include <qstring.h>
#include "register.h"
#include <QTextStream>
#include<QVector>
class Books
{
public:
    Books();
    Books(const Books &book);
    virtual ~Books();

    void SaveBook(QTextStream &aStream);//写入书籍信息
    void ReadBook(QTextStream &aStream);//读入书籍信息

    QString m_strBookName;//书名
    QString m_strBookNumber;//书目编号
    QString m_strAuthorName;//作者名
    QDate m_dateTime;//出版日期
    QString m_strPress;//出版社
    int m_nSum;//库存册数

    QVector<Register>m_register;//登记信息；包含登记号


};

#endif // BOOKS_H
