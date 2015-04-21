#ifndef SERV_H
#define SERV_H

#include <QObject>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>

class serv : public QTcpServer
{
    Q_OBJECT

public:
    serv();
    ~serv();
    void start();
    void stop();

    QList<QTcpSocket *> getClientConnections() const;
    void setClientConnections(const QList<QTcpSocket *> &value);

protected:
    void sendMsg(QString msg);

protected slots:
    void handleNewConnection();
    void clientDisconnected();
    void readClient();

private:
    QList<QTcpSocket *> clientConnections;
    QStringList pseudo;
    bool isFree(QString text);

    void sendConnexion(QTcpSocket * client, QString valid);
signals:
    void niveau(QString niv);
    void nombre(int nb);

};

#endif // SERV_H
