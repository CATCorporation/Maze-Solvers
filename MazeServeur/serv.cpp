#include "serv.h"

serv::serv()
{
    connect(this, SIGNAL(newConnection()), this, SLOT(handleNewConnection()));
}

serv::~serv()
{

}


void serv::start()
{
    listen(QHostAddress::LocalHost, 1234);
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
    if(ligne.contains("connect"))
    {
        if(isFree(ligne))
            sendConnexion(client,"YES");
        else
            sendConnexion(client,"NO");
    }
    else
        sendMsg(ligne);
}

bool serv::isFree(QString text)
{
    QString nom = text.split("|").at(1);
    for(int i=0; i < pseudo.size(); i++)
        if(pseudo.at(i) == nom)
            return true;

    return false;
}

void serv::sendConnexion(QTcpSocket *client,QString valid)
{
    QTextStream flux(client);
    flux << "connect|" << valid << endl;
}

QList<QTcpSocket *> serv::getClientConnections() const
{
    return clientConnections;
}

void serv::setClientConnections(const QList<QTcpSocket *> &value)
{
    clientConnections = value;
}

