#ifndef ADDREADER_H
#define ADDREADER_H

#include <QDialog>

namespace Ui {
class addReader;
}

class addReader : public QDialog
{
    Q_OBJECT

public:
    explicit addReader(QWidget *parent = nullptr);
    ~addReader();
    QString LoanNum();
    QString Name();
    int Gender();
    QString Email();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::addReader *ui;
};

#endif // ADDREADER_H
