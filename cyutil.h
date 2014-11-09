#ifndef CYUTIL_H
#define CYUTIL_H

#include <QMainWindow>

namespace Ui {
class CYUtil;
}

class CYUtil : public QMainWindow
{
    Q_OBJECT

public:
    explicit CYUtil(QWidget *parent = 0);
    ~CYUtil();

private slots:
    void on_pushButton_clicked();

    void on_plainTextEdit_destroyed();

private:
    Ui::CYUtil *ui;
};

#endif // CYUTIL_H
