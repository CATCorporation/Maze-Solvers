#include "serv.h"
#include <QDir>
#include <QFileInfoList>

serv::serv()
{
    connect(this, SIGNAL(newConnection()), this, SLOT(handleNewConnection()));
    currentLevel = 1;
    graphicCalcul = new GraphicCalcul;
    timerMode = new QTimer;
    connect(timerMode,SIGNAL(timeout()),this,SLOT(timeoutCommand()));
}

serv::~serv()
{

}

void serv::start()
{
   listen(QHostAddress::Any, 1234);
   generateAll();
   emit niveau(QString::number(currentLevel));
   emit nombre(clientConnections.size());
   up = down = left = right = 0;
   modeDeJeu = 50;
}

void serv::stop()
{
    qDeleteAll(clientConnections);
    pseudo.clear();
}

void serv::sendMsg(QString msg)
{
    for(int i=0; i< clientConnections.size();i++)
    {
        QTextStream flux(clientConnections.at(i));
        flux << msg << endl ;
    }
}

void serv::handleNewConnection()
{
    QTcpSocket *client = nextPendingConnection();
    connect(client, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
    connect(client, SIGNAL(readyRead()),this, SLOT(readClient()));
    clientConnections.append(client);
    emit nombre(clientConnections.size());

}

void serv::clientDisconnected()
{
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());

    if (!client)
        return;

    clientConnections.removeAll(client);
    client->deleteLater();
    emit nombre(clientConnections.size());
}

void serv::readClient()
{
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());

        if (!client)
            return;

    QString ligne;
    while(client->canReadLine())
    {
        ligne = client->readLine();
    }

    if(ligne.contains("disconnect"))
    {
            QString ps = ligne.split("|").at(1);
            ps.remove("\n");
            pseudo.removeAt(pseudo.indexOf(ps));
    }
    else if(ligne.contains("count"))
    {
        sendSpecificMessage(client,"count|" + QString::number(countMap()));
    }
    else if(ligne.contains("anarchie"))
    {
        QString command =  ligne.split(">> ").at(1);
        command.remove("\n");
        if(command == "anarchie" )
        {
            sendMsg(ligne+"|mode|" + QString::number(-1));
            modeDeJeu--;
        }

    }
    else if(ligne.contains("democratie"))
    {
        QString command =  ligne.split(">> ").at(1);
        command.remove("\n");
        if(command == "democratie" )
        {
            sendMsg(ligne+"|mode|" + QString::number(1));
            modeDeJeu++;
        }
        if(modeDeJeu > 50)
            timerMode->start(5000);
    }
    else if(ligne.contains("connect"))
    {
        if(isFree(ligne))
        {
            sendSpecificMessage(client,"connect|YES");
            QString ps = ligne.split("|").at(1);
            ps.remove("\n");
            pseudo.append(ps);
            sendSpecificMessage(client,"load|" + QString::number(indexMap) + "|" + QString::number(currentLevel) + "|move&down&" + graphicCalcul->getPlayer());
        }
        else
            sendSpecificMessage(client,"connect|NO");
    }   
    else
    {
        graphicCalcul->setTraitment(false);
        QString command =  ligne.split(">> ").at(1);
        command.remove("\n");
        command = command.toUpper();

        if(modeDeJeu > 50)
        {
            if(command == "UP")
                up++;
            if(command == "DOWN")
                down++;
            if(command == "LEFT")
                left++;
            if(command == "RIGHT")
                right++;
        }
        else
            executeCommand(command);

        if(graphicCalcul->getTraitment())
            sendMsg(ligne + "|move&" + command.toLower() + "&" + graphicCalcul->getPlayer());
        else
            sendMsg(ligne);
    }
    if(graphicCalcul->isArrived())
    {
        currentLevel++;
        generateAll();
        sendMsg("load|" + QString::number(indexMap) + "|" + QString::number(currentLevel)+ "|move&down&" + graphicCalcul->getPlayer());
        emit niveau(QString::number(currentLevel));
    }
}

void serv::timeoutCommand()
{

    QList<int> listeCommande;
    listeCommande << up << down << left << right;
    int save = -1;

    for(int i = 0; i < 4;  i++)
        if(listeCommande.at(0)< listeCommande.at(i))
            save = i;

    switch(save)
    {
        case 0:
            commandWin = "UP";
        break;
        case 1:
            commandWin = "DOWN";
        break;
        case 2:
            commandWin = "LEFT";
        break;
        case 3:
            commandWin = "RIGHT";
        break;
    }

    executeCommand(commandWin);
    if(graphicCalcul->getTraitment())
        sendMsg("|move&" + commandWin.toLower() + "&" + graphicCalcul->getPlayer());

    up = down = left = right =0;

    timerMode->start(5000);
}

bool serv::isFree(QString text)
{
    QString nom = text.split("|").at(1);
    nom.remove("\n");
    for(int i=0; i < pseudo.size(); i++)
        if(pseudo.at(i) == nom)
            return false;

    return true;
}

void serv::sendSpecificMessage(QTcpSocket *client,QString valid)
{
    QTextStream flux(client);
    flux << valid << endl;
}

void serv::generateKey()
{
    /* initialize random seed: */
    srand (time(NULL));

    int numberFiles = countMap();
    indexMap = rand() % numberFiles + 1;
}

void serv::generateAll()
{
    bool loadOK = false;
    do
    {
        generateKey();
        loadOK = graphicCalcul->loadMap(indexMap);
    }while(!loadOK);
}

void serv::executeCommand(QString cmd)
{
    if(cmd == "UP")
        graphicCalcul->up();
    if(cmd == "DOWN")
        graphicCalcul->down();
    if(cmd == "LEFT")
        graphicCalcul->left();
    if(cmd == "RIGHT")
        graphicCalcul->right();
}

int serv::getMap() const
{
    return indexMap;
}

void serv::setMap(int value)
{
    indexMap = value;
}

int serv::countMap()
{
    QDir dir = QDir::currentPath() + "/map/";

    QFileInfoList listRepertoire = dir.entryInfoList(QDir::Dirs | QDir::Files);
    int numberFiles = 0;

    for (int i = 0; i < listRepertoire.size(); ++i)
    {
        QFileInfo fileInfos = listRepertoire.at(i);
        if(fileInfos.isFile())
        {
            numberFiles++;
        }
    }
    return numberFiles;
}

int serv::getCurrentLevel() const
{
    return currentLevel;
}

void serv::setCurrentLevel(int value)
{
    currentLevel = value;
}


QList<QTcpSocket *> serv::getClientConnections() const
{
    return clientConnections;
}

void serv::setClientConnections(const QList<QTcpSocket *> &value)
{
    clientConnections = value;
}

