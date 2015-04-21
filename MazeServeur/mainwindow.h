#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "serv.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent *);
private:
    Ui::MainWindow *ui;
    serv *serveur;

private slots:
    void setLevl(QString lvl);
    void setuserCount(int nb);
};

#endif // MAINWINDOW_H
