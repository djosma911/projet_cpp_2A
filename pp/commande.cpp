#include "commande.h"
#include <QDialog>
commande::commande()
{
id="";
model="";
carb="";
datee="";
tel="";
}
commande::commande(QString id,QString model,QString carb,QString datee,QString tel)
{
    this->id=id;
    this->model=model;
    this->carb=carb;
    this->datee=datee;
    this->tel=tel;
}


bool commande::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO  COMMANDE(ID,MODEL,CARB,DATEE,TEL) VALUES (:id,:model,:carb,:datee,:tel)");
    query.bindValue(":id",id);
    query.bindValue(":model",model);
    query.bindValue(":carb",carb);
    query.bindValue(":datee",datee);
    query.bindValue(":tel",tel);
    //eviter sql injection

    return query.exec();

  }

bool commande::supprimer(QString id)
{
QSqlQuery query;

    query.prepare("Delete from COMMANDE where id = :id");
    query.bindValue(":id",id);
return    query.exec();


}
QSqlQueryModel * commande::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from COMMANDE");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("MODEL"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("CARB"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATEE"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("TEL"));

    return model;
}
