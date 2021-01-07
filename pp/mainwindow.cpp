#include "mainwindow.h"
#include "commande.h"
#include"reclamation.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include<QSqlError>
#include<QPainter>
#include<QPdfWriter>
#include<QtWidgets>
#include <ui_mainwindow.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(tmpcmd.afficher());//refresh
    ui->tableView_2->setModel(tmprc.afficher());
    afficher_combo_boc_reclamation();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::afficher_combo_boc_reclamation()
{
    QSqlQuery qry;
    qry.prepare("SELECT * FROM COMMANDE");
    if(qry.exec())
    {
       int i(0);
        while ( qry.next())
        {
            QString ID = qry.value(0).toString();
           ui->comboBox_2->addItem(ID);
          i++;
       }
    }
}


void MainWindow::on_aj_triggered()
{
    QString id = ui->lineEdit->text();
    QString model = ui->lineEdit_2->text();
    QString carb = ui->carbedit->text();
    QString datee = ui->dateEdit->text();
    QString tel = ui->teledit->text();
commande c(id,model,carb,datee,tel);

   bool test=c.ajouter();
   if(test)
   {
     ui->lineEdit->clear();
     ui->lineEdit_2->clear();
     ui->carbedit->clear();
     ui->dateEdit->clear();
     ui->teledit->clear();

     ui->tableView->setModel(tmpcmd.afficher());//refresh
     QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
     notifyIcon->show();
     notifyIcon->setIcon(QIcon("icone.png"));

     notifyIcon->showMessage("GESTION COMMANDE ","cmd Ajouté",QSystemTrayIcon::Information,15000);

 QMessageBox::information(nullptr, QObject::tr("ajouter cmd"),
                       QObject::tr("cmd ajouté./n"
                          "click cancel to exit."),QMessageBox::Cancel);
 }

 else
        ui->tableView->setModel(tmpcmd.afficher());//refresh
     QMessageBox::critical(nullptr, QObject::tr("ajouter cmd"),
                           QObject::tr("Erreur !./n"
                              "click cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_mo_triggered()
{
    QString id = ui->lineEdit->text();
    QString model = ui->lineEdit_2->text();
    QString carb = ui->carbedit->text();
    QString datee = ui->dateEdit->text();
    QString tel = ui->teledit->text();

    QSqlQuery query;
    query.prepare("UPDATE COMMANDE SET ID='"+id+"',MODEL='"+model+"',CARB='"+carb+"',DATEE='"+datee+"',TEL='"+tel+"' where ID = '"+id+"'");
    bool test = query.exec();

    if(test)
    {

        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->carbedit->clear();
        ui->dateEdit->clear();
        ui->teledit->clear();

        ui->tableView->setModel(tmpcmd.afficher());//refresh
       QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
       notifyIcon->show();
       notifyIcon->setIcon(QIcon("icone.png"));

       notifyIcon->showMessage("GESTION COMMANDE ","cmde Modifié",QSystemTrayIcon::Information,15000);

        QMessageBox::information(nullptr, QObject::tr("Modifier commande"),
                    QObject::tr("commande Modifieé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Modifier commande"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}



void MainWindow::on_tableView_activated(const QModelIndex &index)
    {
        QString val=ui->tableView->model()->data(index).toString();
           QSqlQuery qry;
           qry.prepare("select * from COMMANDE where ID='"+val+"'");
           if(qry.exec())
           {
               while(qry.next())
               {




                   ui->lineEdit->setText(qry.value(0).toString());
                   ui->lineEdit_2->setText(qry.value(1).toString());
                   ui->carbedit->setText(qry.value(2).toString());
                   ui->dateEdit->setDate(qry.value(3).toDate());
                   ui->teledit->setText(qry.value(4).toString());

               }

           }
           else
           {
               QMessageBox::critical(this,tr("error::"),qry.lastError().text());
           }
    }


void MainWindow::on_su_triggered()

    {
        QString id = ui->lineEdit->text();
        bool test=tmpcmd.supprimer(id);
        if(test)
        {ui->tableView->setModel(tmpcmd.afficher());//refresh
            ui->lineEdit->clear();
            ui->lineEdit_2->clear();
            ui->carbedit->clear();
            ui->dateEdit->clear();
            ui->teledit->clear();
            QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
            notifyIcon->show();
            notifyIcon->setIcon(QIcon("icone.png"));

            notifyIcon->showMessage("GESTION COMMANDE ","commande supprimé",QSystemTrayIcon::Information,15000);

            QMessageBox::information(nullptr, QObject::tr("Supprimer une commande"),
                        QObject::tr("commande supprimé.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Supprimer une commande"),
                        QObject::tr("Erreur !.\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);
    }


void MainWindow::on_act_triggered()
{
    ui->tableView->setModel(tmpcmd.afficher());//refresh
                ui->lineEdit->clear();
                ui->lineEdit_2->clear();
                ui->carbedit->clear();
                ui->dateEdit->clear();
                ui->teledit->clear();

     ui->tableView_2->setModel(tmprc.afficher());//refresh
                        ui->lineEdit_5->clear();
                        ui->lineEdit_3->clear();
                        ui->textEdit->clear();

                QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                notifyIcon->show();
                notifyIcon->setIcon(QIcon("icone.png"));

                notifyIcon->showMessage("GESTION COMMANDE ET RECLAMATION ","system actualisé",QSystemTrayIcon::Information,15000);
}

void MainWindow::on_pushButton_clicked()
{
//QDateTime datecreation = date.currentDateTime();
        //QString afficheDC = "Date de Creation PDF : " + datecreation.toString() ;
               QPdfWriter pdf("C:/Users/HP/Documents/projet/commande.pdf");
               QPainter painter(&pdf);
              int i = 4000;
                   painter.setPen(Qt::blue);
                   painter.setFont(QFont("Arial", 30));
                   painter.drawText(1100,1200,"Liste commande");
                   painter.setPen(Qt::black);
                   painter.setFont(QFont("Arial", 15));
                  // painter.drawText(1100,2000,afficheDC);
                   painter.drawRect(100,100,7300,2600);
                   //painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/RH/Desktop/projecpp/image/logopdf.png"));
                   painter.drawRect(0,3000,9600,500);
                   painter.setFont(QFont("Arial", 9));
                   painter.drawText(200,3300,"id");
                   painter.drawText(1300,3300,"model");
                   painter.drawText(2100,3300,"carburant");
                   painter.drawText(3200,3300,"date");
                    painter.drawText(4100,3300,"tel");

                   QSqlQuery query;
                   query.prepare("select * from COMMANDE");
                   query.exec();
                   while (query.next())
                   {
                       painter.drawText(200,i,query.value(0).toString());
                       painter.drawText(1300,i,query.value(1).toString());
                       painter.drawText(2200,i,query.value(2).toString());
                       painter.drawText(3200,i,query.value(3).toString());
                       painter.drawText(4200,i,query.value(4).toString());

                      i = i + 500;
                   }
                   int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
                       if (reponse == QMessageBox::Yes)
                       {
                           QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                           notifyIcon->show();
                           notifyIcon->setIcon(QIcon("icone.png"));

                           notifyIcon->showMessage("GESTION COMMANDE ","Liste CMD prete à imprimer",QSystemTrayIcon::Information,15000);

                           painter.end();
                       }
                       if (reponse == QMessageBox::No)
                       {
                            painter.end();
                       }
}

void MainWindow::on_st_triggered()

    {
        QSqlQueryModel *model= new QSqlQueryModel();
                QSqlQuery   *query= new QSqlQuery();
            query->prepare("SELECT * FROM COMMANDE order by ID");//+tri
    query->exec();
        model->setQuery(*query);
    ui->tableView->setModel(model);


}

void MainWindow::on_lineEdit_4_textChanged(const QString &arg1)
{
    QSqlQueryModel *model= new QSqlQueryModel();
            QSqlQuery   *query= new QSqlQuery();
    if(ui->comboBox->currentText()=="Ref"
            "erence"){
        query->prepare("SELECT * FROM COMMANDE WHERE ID LIKE'"+arg1+"%'");//+tri
query->exec();
    model->setQuery(*query);
ui->tableView->setModel(model);


    }
    else {
        if(ui->comboBox->currentText()=="Model"){
            query->prepare("SELECT * FROM COMMANDE WHERE MODEL LIKE'"+arg1+"%'");//+tri
    query->exec();
        model->setQuery(*query);
    ui->tableView->setModel(model);
        }
        else {
            if(ui->comboBox->currentText()=="Tel"){
            query->prepare("SELECT * FROM COMMANDE WHERE TEL LIKE'"+arg1+"%'");//+tri
    query->exec();
        model->setQuery(*query);
    ui->tableView->setModel(model);
            }

        }

    }
}

void MainWindow::on_actionajout_triggered()
{
    QString id = ui->comboBox_2->currentText();
    QString amail = ui->lineEdit_3->text();
    QString id_r = ui->lineEdit_5->text();
    QString description = ui->textEdit->toPlainText();

reclamation r(id,amail,id_r, description);
 ui->tableView_2->setModel(tmprc.afficher());//refresh
   bool test=r.ajouterr();
   if(test)
   {

     ui->lineEdit_5->clear();
     ui->lineEdit_3->clear();
     ui->textEdit->clear();

     ui->tableView_2->setModel(tmprc.afficher());//refresh
     QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
     notifyIcon->show();
     notifyIcon->setIcon(QIcon("icone.png"));

     notifyIcon->showMessage("GESTION RECLAMATION ","reclamation Ajouté",QSystemTrayIcon::Information,15000);

 QMessageBox::information(nullptr, QObject::tr("ajouter reclamation"),
                       QObject::tr("reclamation ajouté./n"
                          "click cancel to exit."),QMessageBox::Cancel);
 }

 else
        ui->tableView->setModel(tmprc.afficher());//refresh
     QMessageBox::critical(nullptr, QObject::tr("ajouter cmd"),
                           QObject::tr("Erreur !./n"
                              "click cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_actionmodif_triggered()
{

    QString id = ui->comboBox_2->currentText();
    QString amail = ui->lineEdit_3->text();
    QString id_r = ui->lineEdit_5->text();
    QString description = ui->textEdit->toPlainText();

    QSqlQuery query;
    query.prepare("UPDATE RECLAMATION SET ID='"+id+"',AMAIL='"+amail+"',ID_R='"+id_r+"',DESCRIPTION='"+description+"' where ID_R = '"+id_r+"'");
    bool test = query.exec();

    if(test)
    {

        ui->lineEdit_5->clear();
        ui->lineEdit_3->clear();
        ui->textEdit->clear();

        ui->tableView_2->setModel(tmprc.afficher());//refresh
       QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
       notifyIcon->show();
       notifyIcon->setIcon(QIcon("icone.png"));

       notifyIcon->showMessage("GESTION RECLAMATION ","reclamation Modifié",QSystemTrayIcon::Information,15000);

        QMessageBox::information(nullptr, QObject::tr("Modifier reclamation"),
                    QObject::tr("reclamation Modifieé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Modifier reclamation"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_tableView_2_activated(const QModelIndex &index)
{
    {
        QString val=ui->tableView_2->model()->data(index).toString();
           QSqlQuery qry;
           qry.prepare("select * from RECLAMATION where ID_R='"+val+"'");
           if(qry.exec())
           {
               while(qry.next())
               {




                   ui->comboBox_2->setCurrentText(qry.value(0).toString());
                   ui->lineEdit_3->setText(qry.value(1).toString());
                   ui->lineEdit_5->setText(qry.value(2).toString());
                  ui->textEdit->setText(qry.value(3).toString());

               }

           }
           else
           {
               QMessageBox::critical(this,tr("error::"),qry.lastError().text());
           }
    }
}

void MainWindow::on_actionsupp_triggered()
{
    QString id_r = ui->lineEdit_5->text();
    bool test=tmprc.supprimerr(id_r);
    if(test)
    {ui->tableView_2->setModel(tmprc.afficher());//refresh
        ui->lineEdit_5->clear();
        ui->lineEdit_3->clear();
        ui->textEdit->clear();
        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
        notifyIcon->show();
        notifyIcon->setIcon(QIcon("icone.png"));

        notifyIcon->showMessage("GESTION RECLAMATION ","reclamation supprimé",QSystemTrayIcon::Information,15000);

        QMessageBox::information(nullptr, QObject::tr("Supprimer reclamation"),
                    QObject::tr("reclamation supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer reclamation"),
                    QObject::tr("Erreur !.\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_2_clicked()
{

    QPdfWriter pdf("C:/Users/HP/Documents/projet/reclamation.pdf");
    QPainter painter(&pdf);
   int i = 4000;
        painter.setPen(Qt::blue);
        painter.setFont(QFont("Arial", 30));
        painter.drawText(1100,1200,"Liste reclamation");
        painter.setPen(Qt::black);
        painter.setFont(QFont("Arial", 15));

        painter.drawRect(100,200,7300,2600);

        painter.drawRect(0,3000,9600,500);
        painter.setFont(QFont("Arial", 9));
        painter.drawText(200,3300,"ID COMMANDE");
        painter.drawText(1500,3300,"ADRESSE MAIL");
        painter.drawText(3000,3300,"ID RECLAMATION");
        painter.drawText(4500,3300,"DESCRIPTION");


        QSqlQuery query;
        query.prepare("select * from RECLAMATION");
        query.exec();
        while (query.next())
        {
            painter.drawText(200,i,query.value(0).toString());
            painter.drawText(1500,i,query.value(1).toString());
            painter.drawText(3000,i,query.value(2).toString());
            painter.drawText(4500,i,query.value(3).toString());


           i = i + 500;
        }
        int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
            if (reponse == QMessageBox::Yes)
            {
                QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                notifyIcon->show();
                notifyIcon->setIcon(QIcon("icone.png"));

                notifyIcon->showMessage("GESTION RECLAMATION ","Liste CMD prete à imprimer",QSystemTrayIcon::Information,15000);

                painter.end();
            }
            if (reponse == QMessageBox::No)
            {
                 painter.end();
            }
}

void MainWindow::on_actiontri_triggered()
{
    QSqlQueryModel *model= new QSqlQueryModel();
            QSqlQuery   *query= new QSqlQuery();
        query->prepare("SELECT * FROM RECLAMATION order by ID_R");//+tri
query->exec();
    model->setQuery(*query);
ui->tableView_2->setModel(model);
}

void MainWindow::on_lineEdit_6_textChanged(const QString &arg1)
{
    QSqlQueryModel *model= new QSqlQueryModel();
            QSqlQuery   *query= new QSqlQuery();
    if(ui->comboBox_3->currentText()=="ID COMMANDE"){
        query->prepare("SELECT * FROM RECLAMATION WHERE ID LIKE'"+arg1+"%'");//+tri
query->exec();
    model->setQuery(*query);
ui->tableView_2->setModel(model);


    }
    else {
        if(ui->comboBox_3->currentText()=="REF RECLAMATION"){
            query->prepare("SELECT * FROM RECLAMATION WHERE ID_R LIKE'"+arg1+"%'");//+tri
    query->exec();
        model->setQuery(*query);
    ui->tableView_2->setModel(model);
        }




    }
}
