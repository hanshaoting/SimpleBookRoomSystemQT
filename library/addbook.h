#ifndef ADDBOOK_H
#define ADDBOOK_H

#include <QDialog>

namespace Ui {
class AddBook;
}

class AddBook : public QDialog
{
    Q_OBJECT

public:
    explicit AddBook(QWidget *parent = nullptr);
    ~AddBook();
    QString BookName();//读入书名
    QString BookNumber();//读入书目编号
    QString AuthorName();//作者名
    QDate Time();//出版日期
    QString Press();//出版社
    int Sum();//库存册数

private slots:

    void on_pushButton_clicked();

private:
    Ui::AddBook *ui;



};

#endif // ADDBOOK_H
