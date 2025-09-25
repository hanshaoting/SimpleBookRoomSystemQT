#ifndef DELETEBOOK_H
#define DELETEBOOK_H

#include <QDialog>

namespace Ui {
class DeleteBook;
}

class DeleteBook : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteBook(QWidget *parent = nullptr);
    ~DeleteBook();
    QString BookName();//读入书名
    QString BookNumber();//读入书目编号
    int m_nRecord;//=1时代表选中书名，=2时代表选中书名编号

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_buttonBox_accepted();

private:
    Ui::DeleteBook *ui;
};

#endif // DELETEBOOK_H
