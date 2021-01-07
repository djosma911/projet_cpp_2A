#include "reclamation.h"

reclamation::reclamation()
{
    id="";
    amail="";
    id_r="";
    description="";

}





reclamation::reclamation(QString id,QString amail,QString id_r,QString description)
{
    this->id=id;
    this->amail=amail;
    this->id_r=id_r;
    this->description=description;

}

bool reclamation::ajouterr()
{
    QSqlQuery query;
    query.prepare("INSERT INTO  RECLAMATION (ID,AMAIL,ID_R,DESCRIPTION) VALUES (:id,:amail,:id_r,:description)");
    query.bindValue(":id",id);
    query.bindValue(":amail",amail);
    query.bindValue(":id_r",id_r);
    query.bindValue(":description",description);

    //eviter sql injection

    return query.exec();

  }

bool reclamation::supprimerr(QString id_r)
{
QSqlQuery query;

    query.prepare("Delete from RECLAMATION where id_r = :id_r");
    query.bindValue(":id_r",id_r);
return    query.exec();


}
QSqlQueryModel * reclamation::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from RECLAMATION");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID COMMANDE"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("ADRESSE MAIL"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("ID RECLAMATION"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("DESCRIPTION"));


    return model;
}
