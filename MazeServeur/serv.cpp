#include "serv.h"

serv::serv()
{
    connect(this, SIGNAL(newConnection()), this, SLOT(handleNewConnection()));
    currentLevel =1;
    graphicCalcul = new GraphicCalcul;

}

serv::~serv()
{

}


void serv::start()
{
    listen(QHostAddress::LocalHost, 1234);
    generateKey();
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
        flux << msg << endl << endl;
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
    else if(ligne.contains("connect"))
    {
        if(isFree(ligne))
        {
            sendSpecificMessage(client,"connect|YES");
            QString ps = ligne.split("|").at(1);
            ps.remove("\n");
            pseudo.append(ps);
            sendSpecificMessage(client,"load|"+QString::number(indexMap));
        }
        else
            sendSpecificMessage(client,"connect|NO");
    }   
    else
    {
        QString command =  ligne.split(">> ").at(1);
        command.remove("\n");
        command = command.toUpper();

        sendMsg(ligne);
    }
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

    indexMap = rand() % 5 + 1;
}

int serv::getMap() const
{
    return indexMap;
}

void serv::setMap(int value)
{
    indexMap = value;
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

