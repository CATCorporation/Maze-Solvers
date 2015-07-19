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
            placement.m_start = QPoint(mapArray.size()-1,ligne.indexOf("D"));
        }
        else if(ligne.contains("A"))
        {
            placement.m_finish = QPoint(mapArray.size()-1,ligne.indexOf("A"));
        }
    }
    file.close();
    placement.teemo = placement.m_start;
    placement.life = 3;
    return true;
}

void GraphicCalcul::up()
{
    if( placement.teemo.rx() >= 1 &&
        mapArray.at(placement.teemo.rx()-1).at(placement.teemo.ry()) != '*')
    {
        if( mapArray.at(placement.teemo.rx()-1).at(placement.teemo.ry()) == 'P')
        {
            if(placement.invicibility)
                placement.invicibility  = false;
            else
                randomPoint();
        }
        else if(mapArray.at(placement.teemo.rx()-1).at(placement.teemo.ry()) == 'Q')
        {
            if(placement.invicibility)
                placement.invicibility  = false;
            else
                placement.teemo = placement.m_start;
        }
        else if(mapArray.at(placement.teemo.rx()-1).at(placement.teemo.ry()) == 'B')
            placement.life++;
        else if(mapArray.at(placement.teemo.rx()-1).at(placement.teemo.ry()) == 'C')
            placement.life--;
        else if(mapArray.at(placement.teemo.rx()-1).at(placement.teemo.ry()) == 'R')
            placement.invicibility = true;
        else
            placement.teemo.rx()--;
    }
    if(placement.life == 0)
    {
        placement.teemo = placement.m_start;
        placement.life = 3;
    }
    traitment = true;
}

void GraphicCalcul::down()
{
    if( placement.teemo.rx() <= 28 &&
        mapArray.at(placement.teemo.rx()+1).at(placement.teemo.ry()) != '*')
    {
        if( mapArray.at(placement.teemo.rx()+1).at(placement.teemo.ry()) == 'P')
        {
            if(placement.invicibility)
                placement.invicibility  = false;
            else
                randomPoint();
        }
        else if(mapArray.at(placement.teemo.rx()+1).at(placement.teemo.ry()) == 'Q')
        {
            if(placement.invicibility)
                placement.invicibility  = false;
            else
                placement.teemo = placement.m_start;
        }
        else if(mapArray.at(placement.teemo.rx()+1).at(placement.teemo.ry()) == 'B')
            placement.life++;
        else if(mapArray.at(placement.teemo.rx()+1).at(placement.teemo.ry()) == 'C')
            placement.life--;
        else if(mapArray.at(placement.teemo.rx()+1).at(placement.teemo.ry()) == 'R')
            placement.invicibility = true;
        else
            placement.teemo.rx()++;
    }
    if(placement.life == 0)
    {
        placement.teemo = placement.m_start;
        placement.life = 3;
    }
    traitment = true;
}

void GraphicCalcul::left()
{
    if( placement.teemo.ry() >= 1 &&
        mapArray.at(placement.teemo.rx()).at(placement.teemo.ry()-1) != '*')
    {
        if( mapArray.at(placement.teemo.rx()).at(placement.teemo.ry()-1) == 'P')
        {
            if(placement.invicibility)
                placement.invicibility  = false;
            else
                randomPoint();
        }
        else if(mapArray.at(placement.teemo.rx()).at(placement.teemo.ry()-1) == 'Q')
        {
            if(placement.invicibility)
                placement.invicibility  = false;
            else
                placement.teemo = placement.m_start;
        }
        else if(mapArray.at(placement.teemo.rx()).at(placement.teemo.ry()-1) == 'B')
            placement.life++;
        else if(mapArray.at(placement.teemo.rx()).at(placement.teemo.ry()-1) == 'C')
            placement.life--;
        else if(mapArray.at(placement.teemo.rx()).at(placement.teemo.ry()-1) == 'R')
            placement.invicibility = true;
        else
            placement.teemo.ry()--;
    }
    if(placement.life == 0)
    {
        placement.teemo = placement.m_start;
        placement.life = 3;
    }
    traitment = true;
}

void GraphicCalcul::right()
{
    if( placement.teemo.ry() <= 28 &&
        mapArray.at(placement.teemo.rx()).at(placement.teemo.ry()+1) != '*')
    {
        if( mapArray.at(placement.teemo.rx()).at(placement.teemo.ry()+1) == 'P')
        {
            if(placement.invicibility)
                placement.invicibility  = false;
            else
                randomPoint();
        }
        else if(mapArray.at(placement.teemo.rx()).at(placement.teemo.ry()+1) == 'Q')
        {
            if(placement.invicibility)
                placement.invicibility  = false;
            else
                placement.teemo = placement.m_start;
        }
        else if(mapArray.at(placement.teemo.rx()).at(placement.teemo.ry()+1) == 'B')
            placement.life++;
        else if(mapArray.at(placement.teemo.rx()).at(placement.teemo.ry()+1) == 'C')
            placement.life--;
        else if(mapArray.at(placement.teemo.rx()).at(placement.teemo.ry()+1) == 'R')
            placement.invicibility = true;
        else
            placement.teemo.ry()++;
    }
    if(placement.life == 0)
    {
        placement.teemo = placement.m_start;
        placement.life = 3;
    }
    traitment = true;
}

QString GraphicCalcul::getPlayer()
{
    return QString(QString::number(placement.teemo.rx()) + "&" + QString::number(placement.teemo.ry()) + "&" + QString::number(placement.life));
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
    return (placement.teemo == placement.m_finish);
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
    placement.teemo = QPoint(x,y);
}
