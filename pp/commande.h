#ifndef COMMANDE_H
#define COMMANDE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>


class commande
{
public:
    commande();
    commande(QString,QString,QString,QString,QString);
    QString get_id;
    QString get_model;
    QString get_carb;
    QString get_datee;
    QString get_tel;
    bool ajouter();
    bool supprimer(QString);
     QSqlQueryModel * afficher();

private:
     QString id,model,carb,datee,tel;
};

#endif // COMMANDE_H
