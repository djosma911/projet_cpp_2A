#ifndef RECLAMATION_H
#define RECLAMATION_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class reclamation
{
public:
    reclamation();

    reclamation(QString,QString,QString,QString);
    QString get_id;
    QString get_amail;
    QString get_id_r;
    QString get_description;
    bool ajouterr();
    bool supprimerr(QString);
     QSqlQueryModel * afficher();
private:
     QString id,amail,id_r,description;
};

#endif // RECLAMATION_H
