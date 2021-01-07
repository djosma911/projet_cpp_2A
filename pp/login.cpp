
#include "login.h"
#include "ui_login.h"
#include<QMessageBox>
#include"mainwindow.h"
login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_clicked()
{
    bool test=a.login(ui->usename->text(),ui->password->text());
    if(test){
        MainWindow *w=new MainWindow();
        w->show();
    }
    else{
        QMessageBox::critical(nullptr,QObject::tr("Connexion"),QObject::tr("username or pwd incorrect!"),QMessageBox::Cancel);
    }
}
