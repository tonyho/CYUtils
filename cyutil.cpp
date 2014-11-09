#include <QDebug>
#include "cyutil.h"
#include "ui_cyutil.h"
extern "C" {
#include "partprobe.h"
}

CYUtil::CYUtil(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::CYUtil)
{
        ui->setupUi(this);
}

CYUtil::~CYUtil()
{
        delete ui;
}

void CYUtil::on_pushButton_clicked()
{
//        QString *device;
//        device = qparted_main();
//        QDebug("Device: %s\n",*device);
          //char *p=qparted_main();
          //qDebug()<<p<<endl;
          ui->plainTextEdit->appendPlainText("Hello Append");
          //ui->plainTextEdit->appendPlainText(p);
          ui->plainTextEdit->appendPlainText(qparted_main());
          //QDebug("Device: %s\n",p);
}

void CYUtil::on_plainTextEdit_destroyed()
{

}
