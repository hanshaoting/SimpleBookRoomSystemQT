#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"addbook.h"
#include"deletebook.h"
#include<QToolBar>
#include<QAction>
#include<QStatusBar>
#include<QLabel>
#include<QDialog>
#include<QDebug>
#include<QMessageBox>
#include"table.h"
#include"loannum.h"
#include<QBrush>
#include"registernumber.h"
#include<QFile>
#include<QFileDialog>
#include<QDir>
#include"addreader.h"
#include"reader.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("://qt2/project/library/icon1.png"));//设置图标

    QStatusBar * stbar=statusBar();//创建状态栏
    setStatusBar(stbar);
    QLabel * label= new QLabel("欢迎使用图书室管理系统！",this);
    stbar->addPermanentWidget(label);//

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//设置表头宽度适应并填充窗口宽度
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableWidget->verticalHeader()->setVisible(false);//设置表格行序号不显示
    ui->tableWidget_2->verticalHeader()->setVisible(false);
    ui->tableWidget_3->verticalHeader()->setVisible(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::addBooksTable(Books &tempbook)//增加表格行打印书籍信息

{

    int row=ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);//插入行

    for(int col=0;col<5;col++)
    {//写入书籍信息

        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(tempbook.m_strBookName));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(tempbook.m_strBookNumber));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(tempbook.m_strAuthorName));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(tempbook.m_strPress));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(tempbook.m_dateTime.toString()));

    }
    ui->tabWidget->setCurrentIndex(0);//跳转到对应tabWidget
}

void MainWindow::deleteBooksTable(int a)//删除书籍在表格中的显示
{
    ui->tableWidget->removeRow(a);
    m_InfoTable.deleteBook(a);
    ui->tabWidget->setCurrentIndex(0);

}

void MainWindow::addLoanTable(Books &tempbook,int a)//打印借阅信息
{
    int row = ui->tableWidget_2->rowCount();
    ui->tableWidget_2->setColumnCount(6);
    int h=1;//作标记用：该书是否在列表中
    for(int i=0;i<row;i++)//检查该书目前是否处在列表，直接作修改
    {
        if(ui->tableWidget_2->item(i,0)->text()==tempbook.m_strBookName)
        {
            if(ui->tableWidget_2->item(i,2)->text()==tempbook.m_register[a].m_strRegisterNumber)
            {
                ui->tableWidget_2->setItem(i,5,new QTableWidgetItem("已借出"));
                ui->tableWidget_2->item(i,5)->setBackground(QBrush(QColor("#ACD4FF")));//green #96FB9F
                ui->tableWidget_2->item(i,5)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                ui->tableWidget_2->setItem(i,3,new QTableWidgetItem(tempbook.m_register[a].m_strLoanNumber));
                ui->tableWidget_2->setItem(i,4,new QTableWidgetItem(tempbook.m_register[a].m_dateLoan.toString()));

                h=0;//标记更改：该书处在书籍列表中

                break;
            }

        }
    }
    if(h==1)//标记不变：该书不在列表中，新建行显示
    {
    ui->tableWidget_2->insertRow(row);
    for(int col=0;col<6;col++)
    {

        ui->tableWidget_2->setItem(row,col++,new QTableWidgetItem(tempbook.m_strBookName));
        ui->tableWidget_2->setItem(row,col++,new QTableWidgetItem(tempbook.m_strBookNumber));
        ui->tableWidget_2->setItem(row,col++,new QTableWidgetItem(tempbook.m_register[a].m_strRegisterNumber));
        ui->tableWidget_2->setItem(row,col++,new QTableWidgetItem(tempbook.m_register[a].m_strLoanNumber));
        ui->tableWidget_2->setItem(row,col++,new QTableWidgetItem(tempbook.m_register[a].m_dateLoan.toString()));
        ui->tableWidget_2->setItem(row,col++,new QTableWidgetItem("已借出"));
        ui->tableWidget_2->item(row,5)->setBackground(QBrush(QColor("#ACD4FF")));//green #96FB9F
        ui->tableWidget_2->item(row,5)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    }

    }
}


void MainWindow::on_actionz_triggered()//增加书籍
{
    class AddBook abk;//弹出增加书籍窗口
    int ret=abk.exec();
    if(ret==AddBook::Accepted)
    {
        //Books tempbook;
        Books*tempbook=new Books;//读取新书信息
        tempbook->m_strBookName=abk.BookName();
        tempbook->m_nSum=abk.Sum();
        tempbook->m_dateTime=abk.Time();
        tempbook->m_strAuthorName=abk.AuthorName();
        tempbook->m_strPress=abk.Press();
        tempbook->m_strBookNumber=abk.BookNumber();

        m_InfoTable.addBook(tempbook);//添加书籍到书籍列表
        addBooksTable(*tempbook);//打印书籍信息


    }

}

 void MainWindow::on_actions_triggered()//删除书籍
{

    class DeleteBook abk;

    int ret=abk.exec();

    if(ret==DeleteBook::Accepted)
    {
        int y;//作标记用：是否找到目标书籍
       if(abk.m_nRecord==1)
        {
        y=m_InfoTable.NameSearch(abk.BookName());
       }
       if(abk.m_nRecord==2)//=1时代表选中书名，=2时代表选中书名编号
       {
        y=m_InfoTable.NumberSearch(abk.BookName());
       }


       if(y!=-1)//找到该书籍
       {

        deleteBooksTable(y);
        QMessageBox::information(this,"结果","删除成功。");

       }
       else//未找到目标书籍
       {
     QMessageBox::information(this,"查询结果","您查询的书籍不存在。");
       }
   }

}


void MainWindow::on_action_cha_triggered()//查询书籍信息
{
    class DeleteBook abk;
    int ret=abk.exec();

    if(ret==DeleteBook::Accepted)
    {
        //Books tempbook;
        int y;//作标记：是否找到目标书籍
        if(abk.m_nRecord==1)
        {
            y=m_InfoTable.NameSearch(abk.BookName());
        }
        if(abk.m_nRecord==2)//=1时代表选中书名，=2时代表选中书名编号
        {
            y=m_InfoTable.NumberSearch(abk.BookName());

        }
        if(y!=-1)//找到目标书籍
        {
            table tb;
            tb.ShowTable(*m_InfoTable.getBook(y));//显示书籍信息
            tb.exec();
        }
        else//未找到书籍
        {
            QMessageBox::information(this,"查询结果","您查询的书籍不存在。");
        }
    }

}

void MainWindow::on_action_c_triggered()//查询具体书籍借阅信息
{
    registernumber rgsnum;
    int ret=rgsnum.exec();
    if(ret==registernumber::Accepted)
    {
        int lable=0;//作标记：是否找到目标书籍
        for(int i=0;i<m_InfoTable.getSize();i++)//遍历，寻找目标书籍
        {
            for(int j=0;j<m_InfoTable.getBook(i)->m_nSum;j++)
            {
                QString index=m_InfoTable.getBook(i)->m_register[j].m_strRegisterNumber;//书籍列表中书籍的登记号

                if(index==rgsnum.Number())//判断是否和用户输入的登记号一致
                {
                    if(m_InfoTable.getBook(i)->m_register[j].m_bSendOut)
                    {
                        QMessageBox::information(this,"结果","该册书已借出.");
                    }
                    else
                    {
                        QMessageBox::information(this,"结果","该册书可借.");
                    }

                    lable=1;//标记更改：成功找到书籍
                }
            }
        }
        if(lable==0)//标记不变：没有找到书籍
        {
            QMessageBox::information(this,"查询结果","您查询的书籍不存在。");
        }
    }

}

void MainWindow::on_actionj_triggered()//借书
{
    class DeleteBook abk;

    int ret=abk.exec();

    if(ret==DeleteBook::Accepted)
    {

        int y;//作标记：是否找到目标书籍
        if(abk.m_nRecord==1)
        {
            y=m_InfoTable.NameSearch(abk.BookName());
        }
        if(abk.m_nRecord==2)//record=1时代表选中书名，=2时代表选中书名编号
        {
            y=m_InfoTable.NumberSearch(abk.BookName());

        }
        if(y!=-1)//如果能找到目标书籍
        {

            LoanNum ln;
           int ret=ln.exec();

            if(ret==LoanNum::Accepted)
           {
               int index=0;//标记：是否找到借书证号
                int label;//读者信息处于列表中的位置
                //判断该读者的借书证号是否在读者信息列表中，如果不在，创建新的读者信息
                for(int i=0;i<m_InfoTable.getReaderSum();i++)
                {

                    if(ln.Name()==m_InfoTable.getReader(i)->m_strLoanNum)//如果填入的借书证号在读者列表中
                    {
                        index=1;//标记：找到借书证号
                        label=i;//得到读者信息位置
                        break;
                    }
                }

                if(index==0)//标记没有发生改变：借书证号不在列表中
                {
                    QMessageBox::information(this,"提示","查询到该借书证号不存在，请先新建该读者信息到系统。");
                    on_actionu_triggered();//新建读者信息

                    label=m_InfoTable.getReaderSum()-1;//得到新的读者信息位置
                }



               int t=0;//做标记：是否成功借书
               for(int i=0;i<m_InfoTable.getBook(y)->m_nSum;i++)
                {
                   if(!(m_InfoTable.getBook(y)->m_register.at(i).m_bSendOut))//如果未借出
                    {
                    m_InfoTable.getBook(y)->m_register[i].m_bSendOut=1;
                       m_InfoTable.getBook(y)->m_register[i].m_strLoanNumber= m_InfoTable.getReader(label)->m_strLoanNum;
                    m_InfoTable.getBook(y)->m_register[i].m_dateLoan=ln.Date();
                    //打印widget2
                    addLoanTable(*m_InfoTable.getBook(y),i);
                    QMessageBox::information(this,"借阅结果","借阅成功！所借阅书籍的登记号为：【"+m_InfoTable.getBook(y)->m_register[i].m_strRegisterNumber+"】.  可在主页【所有借阅信息】栏查看借阅信息.");

                    ui->tabWidget->setCurrentIndex(1);//跳转到借阅信息栏

                    t=1;//标记改变：借书成功
                    break;

                    }
               }//for end
               if(t==0)//标记没有发生改变：借书失败
               {
                   QMessageBox::information(this,"借阅结果","借阅失败！该书籍已无库存。");
               }
            }



        }
        else//没有在书库中查询到书籍
        {
            QMessageBox::information(this,"查询结果","您查询的书籍不存在。");
        }
    }

}



void MainWindow::on_actionh_triggered()//还书：输入登记号直接还书
{
    class registernumber rgst;//弹出窗口输入登记号
    int ret=rgst.exec();
    if(ret==registernumber::Accepted)
    {
        int y=0;//作标记:是否找到目标书籍
        {
            int row=ui->tableWidget_2->rowCount();
            for(int i=0;i<m_InfoTable.getSize();i++)//遍历查询
            {
                for(int j=0;j<m_InfoTable.getBook(i)->m_nSum;j++)
                {
                    QString index=m_InfoTable.getBook(i)->m_register[j].m_strRegisterNumber;//书籍列表中书册的登记号
                    QString str=rgst.Number();//读入用户输入的登记号
                    if(index==str)//找到目标书籍
                    {
                        for(int k=0;k<row;k++)
                        {
                            if(ui->tableWidget_2->item(k,2)->text()==str)//检查表格中是否有该册书
                            {
                                ui->tableWidget_2->setItem(k,5,new QTableWidgetItem("可借阅"));
                                ui->tableWidget_2->item(k,5)->setBackground(QBrush(QColor("#96FB9F")));//green #96FB9F
                                ui->tableWidget_2->item(k,5)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                                ui->tableWidget_2->setItem(k,3,new QTableWidgetItem(" "));//清空借书证号和借阅时间
                                ui->tableWidget_2->setItem(k,4,new QTableWidgetItem(" "));
                                m_InfoTable.getBook(i)->m_register[j].m_bSendOut=0;//书籍属性改为未借出

                                m_InfoTable.getBook(i)->m_register[j].m_strLoanNumber.clear();//清空借书证号

                                QMessageBox::information(this,"结果","还书成功！所借阅的书籍已回到书架上.  可在主页【所有借阅信息】栏查看该书籍信息.");
                                ui->tabWidget->setCurrentIndex(1);

                                y= 1;//标记改变：成功找到书籍
                                break;
                            }

                        }
                    }
                }
            }

        }

        if(y==0)//未找到对应书籍
        {

        QMessageBox::critical(this,"结果","还书失败！请检查登记号或该册书不存在.");

        }
    }

}



void MainWindow::on_actiondakai_triggered()//打开文件,思路：在原本书籍不动的情况下读入新的书籍信息，调用addbookstable打印新行
{
    QString curPath = QDir::currentPath();
    QString dlgTitle = "选择一个文件";
    QString filter = "文本文件(*.txt);;所有文件(*.*)";
    QString aFileName = QFileDialog::getOpenFileName(this, dlgTitle, curPath, filter);//打开文件页面

    if(aFileName.isEmpty())
        return;

    //创建成功，打开文件
    int readsum=m_InfoTable.ReadBookFromFile(aFileName);//文件里书籍种数
    if(readsum>0)
    {

        int row=ui->tableWidget->rowCount();
        for(int i=0;i<readsum;i++)
        {
            addBooksTable(*m_InfoTable.getBook(row+i));//打印新读入书的信息

        }
    }

}


void MainWindow::on_actionbaocun_triggered()//保存文件
{
    QString curPath = QDir::currentPath();
    QString dlgTitle = "另存为一个文件";
    QString filter = "文本文件(*.txt);;所有文件(*.*)";
    QString aFileName = QFileDialog::getSaveFileName(this, dlgTitle, curPath, filter);
    if(aFileName.isEmpty())//判断是否为空
        return;
    m_InfoTable.SaveBookToFile(aFileName);
}


void MainWindow::on_actionu_triggered()//添加读者
{
    class addReader ar;
    int ret=ar.exec();
    if(ret==addReader::Accepted)
    {
        reader*tempreader=new reader;
        tempreader->m_strLoanNum=ar.LoanNum();
        tempreader->m_strName=ar.Name();
        tempreader->m_nGender=ar.Gender();
        tempreader->m_strEmail=ar.Email();
        addReadTable(*tempreader);//打印读者信息
        m_InfoTable.addReader(tempreader);//增加读者到读者列表
    }
}

void MainWindow::addReadTable(reader& tempreader)//在主页表格显示读者信息
{
    int row = ui->tableWidget_3->rowCount();
    ui->tableWidget_3->setColumnCount(4);

        ui->tableWidget_3->insertRow(row);//插入行
        for(int col=0;col<4;col++)
        {

            ui->tableWidget_3->setItem(row,col++,new QTableWidgetItem(tempreader.m_strLoanNum));
            ui->tableWidget_3->setItem(row,col++,new QTableWidgetItem(tempreader.m_strName));
            if(tempreader.m_nGender==1)
            {
                ui->tableWidget_3->setItem(row,col++,new QTableWidgetItem("女"));
            }
            if(tempreader.m_nGender==0)
            {
                ui->tableWidget_3->setItem(row,col++,new QTableWidgetItem("男"));
            }
            ui->tableWidget_3->setItem(row,col++,new QTableWidgetItem(tempreader.m_strEmail));
        }
        QMessageBox::information(this,"结果","读者信息添加成功！可在主页【所有读者信息】栏查看。");

        ui->tabWidget->setCurrentIndex(2);

}

void MainWindow::on_actionjilu_triggered()//查询借阅记录
{
    class LoanNum ln;
    ln.setUI();
    int ret=ln.exec();
    if(ret==LoanNum::Accepted)
    {

        int t;
        QString num=ln.Name();//读取借书证号
        t=m_InfoTable.LoanSearch(num);//得到读者在读者列表中的位置
        if(t>=0)
        {
            QMessageBox::information(this,"信息","您正在查看读者"+m_InfoTable.getReader(t)->m_strName+"的借阅记录。");
            table tb;
            for(int i=0;i<m_InfoTable.getSize();i++)
            {
                for(int j=0;j<m_InfoTable.getBook(i)->m_register.size();j++)
                {
                    if(m_InfoTable.getBook(i)->m_register[j].m_strLoanNumber==num)//遍历书籍列表，寻找哪本书册的借书证号与用户输入的一致
                    {
                        tb.ShowLendTable(*m_InfoTable.getBook(i),j);

                    }
                }
            }
            tb.exec();

        }
        if(t==-1)//没有在读者列表中找到该读者
        {
            QMessageBox::critical(this,"注意","系统中无该读者信息记录，请检查借书证号或在系统中新建读者信息。");

        }
    }

}
