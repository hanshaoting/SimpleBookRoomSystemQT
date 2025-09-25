#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"QTableWidget"
#include <QMainWindow>
#include"books.h"
#include<QString>
#include<QVector>
#include"library.h"
#include"reader.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



protected:
    void deleteBooksTable(int);//从表格中移除被删除书籍
    void addBooksTable(Books&);//在表格中添加新书籍
    void addLoanTable(Books&,int);//新建借阅记录显示
    void addReadTable(reader&);//新建读者信息显示

private slots:
    void on_actionz_triggered();//增加书籍槽函数
    void on_actions_triggered();//删除书籍槽函数
    void on_action_cha_triggered();//查询书籍信息槽函数
    void on_actionj_triggered();//借书槽函数
    void on_action_c_triggered();//查询借阅信息槽函数
    void on_actionh_triggered();//还书槽函数
    void on_actiondakai_triggered();//读取文件槽函数
    void on_actionbaocun_triggered();//保存文件槽函数
    void on_actionu_triggered();//添加读者
    void on_actionjilu_triggered();//查询读者借阅信息
signals:

private:
    Ui::MainWindow *ui;
    Library m_InfoTable;//*总数据调用库

};
#endif // MAINWINDOW_H
