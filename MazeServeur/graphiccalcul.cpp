#include "graphiccalcul.h"
#include <QDir>

GraphicCalcul::GraphicCalcul()
{

}

GraphicCalcul::~GraphicCalcul()
{

}

bool GraphicCalcul::loadMap(int idx)
{
    mapArray.clear();

    QString fileName = QDir::currentPath()+"/map/map" + QString::number(idx) + ".txt";
    QString ligne = "";

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&file);
    while (!in.atEnd())
    {
        ligne = in.readLine();
        mapArray.append(ligne);
        if(ligne.contains("D"))
        {
            placement.depart = QPoint(mapArray.size()-1,ligne.indexOf("D"));
        }
        else if(ligne.contains("A"))
        {
            placement.arrive = QPoint(mapArray.size()-1,ligne.indexOf("A"));
        }
    }
    file.close();
    placement.joueur = placement.depart;
    placement.life = 3;
    return true;
}

void GraphicCalcul::up()
{
    if( placement.joueur.rx() >= 1 &&
        mapArray.at(placement.joueur.rx()-1).at(placement.joueur.ry()) != '*')
    {
        if( mapArray.at(placement.joueur.rx()-1).at(placement.joueur.ry()) == 'P')
        {
            if(placement.invicible)
                placement.invicible  = false;
            else
                randomPoint();
        }
        else if(mapArray.at(placement.joueur.rx()-1).at(placement.joueur.ry()) == 'Q')
        {
            if(placement.invicible)
                placement.invicible  = false;
            else
                placement.joueur = placement.depart;
        }
        else if(mapArray.at(placement.joueur.rx()-1).at(placement.joueur.ry()) == 'B')
            placement.life++;
        else if(mapArray.at(placement.joueur.rx()-1).at(placement.joueur.ry()) == 'C')
            placement.life--;
        else if(mapArray.at(placement.joueur.rx()-1).at(placement.joueur.ry()) == 'R')
            placement.invicible = true;
        else
            placement.joueur.rx()--;
    }
    if(placement.life == 0)
    {
        placement.joueur = placement.depart;
        placement.life = 3;
    }
    traitment = true;
}

void GraphicCalcul::down()
{
    if( placement.joueur.rx() <= 28 &&
        mapArray.at(placement.joueur.rx()+1).at(placement.joueur.ry()) != '*')
    {
        if( mapArray.at(placement.joueur.rx()+1).at(placement.joueur.ry()) == 'P')
        {
            if(placement.invicible)
                placement.invicible  = false;
            else
                randomPoint();
        }
        else if(mapArray.at(placement.joueur.rx()+1).at(placement.joueur.ry()) == 'Q')
        {
            if(placement.invicible)
                placement.invicible  = false;
            else
                placement.joueur = placement.depart;
        }
        else if(mapArray.at(placement.joueur.rx()+1).at(placement.joueur.ry()) == 'B')
            placement.life++;
        else if(mapArray.at(placement.joueur.rx()+1).at(placement.joueur.ry()) == 'C')
            placement.life--;
        else if(mapArray.at(placement.joueur.rx()+1).at(placement.joueur.ry()) == 'R')
            placement.invicible = true;
        else
            placement.joueur.rx()++;
    }
    if(placement.life == 0)
    {
        placement.joueur = placement.depart;
        placement.life = 3;
    }
    traitment = true;
}

void GraphicCalcul::left()
{
    if( placement.joueur.ry() >= 1 &&
        mapArray.at(placement.joueur.rx()).at(placement.joueur.ry()-1) != '*')
    {
        if( mapArray.at(placement.joueur.rx()).at(placement.joueur.ry()-1) == 'P')
        {
            if(placement.invicible)
                placement.invicible  = false;
            else
                randomPoint();
        }
        else if(mapArray.at(placement.joueur.rx()).at(placement.joueur.ry()-1) == 'Q')
        {
            if(placement.invicible)
                placement.invicible  = false;
            else
                placement.joueur = placement.depart;
        }
        else if(mapArray.at(placement.joueur.rx()).at(placement.joueur.ry()-1) == 'B')
            placement.life++;
        else if(mapArray.at(placement.joueur.rx()).at(placement.joueur.ry()-1) == 'C')
            placement.life--;
        else if(mapArray.at(placement.joueur.rx()).at(placement.joueur.ry()-1) == 'R')
            placement.invicible = true;
        else
            placement.joueur.ry()--;
    }
    if(placement.life == 0)
    {
        placement.joueur = placement.depart;
        placement.life = 3;
    }
    traitment = true;
}

void GraphicCalcul::right()
{
    if( placement.joueur.ry() <= 28 &&
        mapArray.at(placement.joueur.rx()).at(placement.joueur.ry()+1) != '*')
    {
        if( mapArray.at(placement.joueur.rx()).at(placement.joueur.ry()+1) == 'P')
        {
            if(placement.invicible)
                placement.invicible  = false;
            else
                randomPoint();
        }
        else if(mapArray.at(placement.joueur.rx()).at(placement.joueur.ry()+1) == 'Q')
        {
            if(placement.invicible)
                placement.invicible  = false;
            else
                placement.joueur = placement.depart;
        }
        else if(mapArray.at(placement.joueur.rx()).at(placement.joueur.ry()+1) == 'B')
            placement.life++;
        else if(mapArray.at(placement.joueur.rx()).at(placement.joueur.ry()+1) == 'C')
            placement.life--;
        else if(mapArray.at(placement.joueur.rx()).at(placement.joueur.ry()+1) == 'R')
            placement.invicible = true;
        else
            placement.joueur.ry()++;
    }
    if(placement.life == 0)
    {
        placement.joueur = placement.depart;
        placement.life = 3;
    }
    traitment = true;
}

QString GraphicCalcul::getPlayer()
{
    return QString(QString::number(placement.joueur.rx()) + "&" + QString::number(placement.joueur.ry()));
}

bool GraphicCalcul::getTraitment() const
{
    return traitment;
}

void GraphicCalcul::setTraitment(bool value)
{
    traitment = value;
}

bool GraphicCalcul::isArrived()
{
    return (placement.joueur == placement.arrive);
}

void GraphicCalcul::randomPoint()
{
    /* initialize random seed: */
    srand (time(NULL));

    int x,y;
    bool isValide = false;
    do
    {
        x = rand() % 29 + 1;
        y = rand() % 29 + 1;
        isValide = mapArray.at(x).at(y) != '*' && mapArray.at(x).at(y) != 'A' && mapArray.at(x).at(y) != 'P' && mapArray.at(x).at(y) != 'Q';
    }while(isValide == false);
    placement.joueur = QPoint(x,y);
}


