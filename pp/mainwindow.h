#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "commande.h"
#include"reclamation.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void afficher_combo_boc_reclamation();
private slots:
    void on_aj_triggered();

    void on_mo_triggered();

    void on_tableView_activated(const QModelIndex &index);

    void on_su_triggered();

    void on_act_triggered();

    void on_pushButton_clicked();

    void on_st_triggered();

    void on_lineEdit_4_textChanged(const QString &arg1);

    void on_actionajout_triggered();

    void on_actionmodif_triggered();

    void on_tableView_2_activated(const QModelIndex &index);

    void on_actionsupp_triggered();

    void on_pushButton_2_clicked();

    void on_actiontri_triggered();

    void on_lineEdit_6_textChanged(const QString &arg1);

private:
    commande tmpcmd;
    Ui::MainWindow *ui;
    reclamation tmprc;
};
#endif // MAINWINDOW_H
