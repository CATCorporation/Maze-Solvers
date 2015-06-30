#include "maze.h"
#include <QFile>
#include <QTextStream>
#include <QDir>

Maze::Maze(QObject *parent) : QObject(parent)
{

}

Maze::~Maze()
{

}

void Maze::generateMaze()
{
    depart = false;
    arrive = false;

    srand(time(0));

    list< pair< int, int > > drillers;

    maze.resize(maze_size_y);
    for(size_t y = 0; y < maze_size_y; y++)
        maze[y].resize(maze_size_x);

    for (size_t x = 0; x < maze_size_x; x++)
        for (size_t y = 0; y < maze_size_y; y++)
            maze[y][x]=false;

    drillers.push_back(make_pair(maze_size_x/2,maze_size_y/2));
    while(drillers.size()>0)
    {
        list < pair < int, int> >::iterator m,_m,temp;
        m=drillers.begin();
        _m=drillers.end();
        while (m!=_m)
        {
            bool remove_driller=false;
            switch(rand()%4)
            {
            case 0:
                (*m).second-=2;
                if ((*m).second<0 || maze[(*m).second][(*m).first])
                {
                    remove_driller=true;
                    break;
                }
                maze[(*m).second+1][(*m).first]=true;
                break;
            case 1:
                (*m).second+=2;
                if ((*m).second>=maze_size_y || maze[(*m).second][(*m).first])
                {
                    remove_driller=true;
                    break;
                }
                maze[(*m).second-1][(*m).first]=true;
                break;
            case 2:
                (*m).first-=2;
                if ((*m).first<0 || maze[(*m).second][(*m).first])
                {
                    remove_driller=true;
                    break;
                }
                maze[(*m).second][(*m).first+1]=true;
                break;
            case 3:
                (*m).first+=2;
                if ((*m).first>=maze_size_x || maze[(*m).second][(*m).first])
                {
                    remove_driller=true;
                    break;
                }
                maze[(*m).second][(*m).first-1]=true;
                break;
            }
            if (remove_driller)
                m = drillers.erase(m);
            else
            {
                drillers.push_back(make_pair((*m).first,(*m).second));
                // Commenter le if permet de rendre le maze plus facile
                if (rand()%2)
                    drillers.push_back(make_pair((*m).first,(*m).second));

                maze[(*m).second][(*m).first]=true;
                ++m;
            }
        }
    }
}

void Maze::generateFile(int counter)
{
    QString path = QDir::currentPath() + "/map" + QString::number(counter) + ".txt";
    QFile fic(path);
    fic.open(QFile::WriteOnly);
    QTextStream stream( &fic );

    // Done
    for (size_t y = 0; y < maze_size_y; y++)
    {
        for (size_t x = 0; x < maze_size_x; x++)
        {
            if (maze[y][x] == true && x != 29 && y != 29)
            {
                if(y > 0 && !depart)
                {
                    depart = true;
                    stream << "D" ;
                }
                else if(y > 24  && y < 29 && !arrive)
                {
                    arrive = true;
                    stream << "A" ;
                }
                else
                    stream << " " ;
            }
            else
            {
                stream << "*" ;
            }
        }
        stream << endl;
    }
    fic.close();
}

void Maze::generate()
{

    for (int i = 0; i < 5; ++i) {
        generateMaze();
        generateFile(i);
    }

    emit finished(QString::number(5));
}
