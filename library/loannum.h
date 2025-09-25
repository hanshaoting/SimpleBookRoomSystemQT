#ifndef LOANNUM_H
#define LOANNUM_H

#include <QDialog>

namespace Ui {
class LoanNum;
}

class LoanNum : public QDialog
{
    Q_OBJECT

public:
    explicit LoanNum(QWidget *parent = nullptr);
    ~LoanNum();
    QString Name();
    QDate Date();

    void setUI();//
private slots:
    void on_buttonBox_accepted();

private:
    Ui::LoanNum *ui;
};

#endif // LOANNUM_H
