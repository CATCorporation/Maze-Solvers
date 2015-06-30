#ifndef MAZE_H
#define MAZE_H

#include <QObject>
#include <vector>
#include <list>

#define maze_size_x 30
#define maze_size_y 30

using namespace std;
class Maze : public QObject
{
    Q_OBJECT
public:
    explicit Maze(QObject *parent = 0);
    ~Maze();

signals:
    void finished(QString value);

public slots:
    void generate();

private:
    bool depart;
    bool arrive;
    vector< vector< bool > > maze;

    void generateMaze();
    void generateFile(int counter);
};

#endif // MAZE_H
