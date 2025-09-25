#ifndef TABLE_H
#define TABLE_H
#include"books.h"
#include <QWidget>
#include<QDialog>
#include"reader.h"
namespace Ui {
class table;
}

class table : public QDialog
{
    Q_OBJECT

public:
    explicit table(QWidget *parent = nullptr);
    ~table();
    void ShowTable(Books&);//打印信息表格
    void ShowLendTable(Books&,int);
private:
    Ui::table *ui;
};

#endif // TABLE_H
