#ifndef SERV_H
#define SERV_H

#include <QObject>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <stdlib.h>
#include <time.h>

#include "graphiccalcul.h"

class serv : public QTcpServer
{
    Q_OBJECT
    Q_ENUMS (commands)

public:
    serv();
    ~serv();
    void start();
    void stop();
    enum commands {UP,DOWN,LEFT,RIGHT };
    QList<QTcpSocket *> getClientConnections() const;
    void setClientConnections(const QList<QTcpSocket *> &value);

    int getCurrentLevel() const;
    void setCurrentLevel(int value);

    int getMap() const;
    void setMap(int value);


protected:
    void sendMsg(QString msg);

protected slots:
    void handleNewConnection();
    void clientDisconnected();
    void readClient();

private:
    QList<QTcpSocket *> clientConnections;
    QStringList pseudo;
    QStringList maze;
    int currentLevel;
    int indexMap;
    GraphicCalcul * graphicCalcul;

    bool isFree(QString text);
    void sendSpecificMessage(QTcpSocket * client, QString valid);
    void generateKey();


signals:
    void niveau(QString niv);
    void nombre(int nb);

};

#endif // SERV_H
