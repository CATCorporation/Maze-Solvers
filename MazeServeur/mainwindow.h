#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "serv.h"

class Maze;
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
    Maze *maze;

private slots:
    void setLevl(QString lvl);
    void setuserCount(int nb);
    void on_pushButton_clicked();
    void setMapsGenerated(QString number);
};

#endif // MAINWINDOW_H
