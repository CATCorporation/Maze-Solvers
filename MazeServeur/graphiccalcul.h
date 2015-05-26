#ifndef GRAPHICCALCUL_H
#define GRAPHICCALCUL_H

#include <QObject>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QPoint>
#include <time.h>

class GraphicCalcul
{
public:
    GraphicCalcul();
    ~GraphicCalcul();

    bool loadMap(int idx);
    void up();
    void down();
    void left();
    void right();
    QString getPlayer();
    bool getTraitment() const;
    void setTraitment(bool value);
    bool isArrived();

private:
    struct Gps {
        QPoint depart;
        QPoint arrive;
        QPoint joueur;
        int life;
        bool invicible;
    };
    bool traitment;
    Gps placement;
    QStringList mapArray;
    void randomPoint();
};

#endif // GRAPHICCALCUL_H
