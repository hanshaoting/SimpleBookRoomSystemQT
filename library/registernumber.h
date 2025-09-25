#ifndef REGISTERNUMBER_H
#define REGISTERNUMBER_H

#include <QDialog>

namespace Ui {
class registernumber;
}

class registernumber : public QDialog
{
    Q_OBJECT

public:
    explicit registernumber(QWidget *parent = nullptr);
    ~registernumber();
    QString Number();//读入登记号

private:
    Ui::registernumber *ui;
};

#endif // REGISTERNUMBER_H
