#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "maze.h"
#include "serv.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    serveur = new serv;

    connect(serveur,SIGNAL(nombre(int)),this,SLOT(setuserCount(int)));
    connect(serveur,SIGNAL(niveau(QString)),this,SLOT(setLevl(QString)));
}

MainWindow::~MainWindow()
{
    serveur->stop();
    delete serveur;
    delete ui;
}

void MainWindow::showEvent(QShowEvent * e)
{
    Q_UNUSED(e);
    serveur->start();
}

void MainWindow::setLevl(QString lvl)
{
    ui->niveau->setText(lvl);
}

void MainWindow::setuserCount(int nb)
{
    ui->nbuser->setText(QString::number(nb));
}

void MainWindow::on_pushButton_clicked()
{
    maze = new Maze();
    connect(maze, SIGNAL(finished(QString)), this, SLOT(setMapsGenerated(QString)));

    maze->generate();
}

void MainWindow::setMapsGenerated(QString number)
{
    ui->attente->setText(number);

    delete(maze);
}
