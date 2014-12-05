#ifndef GLOBAL_PAINTER_H
#define GLOBAL_PAINTER_H

#include <QMainWindow>
#include <QtGui>
#include <QWidget>

enum{
    CHOOSE_BUILD = 1,
    CHOOSE_NEXT_TRAIN_BUILD = 2,

    MAX_BUILD = 100,
    MAX_LINK = 100,
    MAX_TRAIN = 100,


    //Train
    TRAIN_FORWARD = 1,
    TRAIN_BACK = 2,
    TRAIN_SPEED_1 = 4
};

unsigned int builds[MAX_BUILD][2];
unsigned int links[MAX_LINK][2];

struct s_train
{
    QPoint          p1, p2;
    float           left_path[2];
    unsigned int    state;
    float           speed_x, speed_y;
};

s_train trains[MAX_TRAIN];

unsigned int rect_hight = 20;
unsigned int rect_width = 20;
unsigned int line_width = 3;

unsigned int count_rect = 3;
unsigned int count_link = 3;
unsigned int count_train = 0;

unsigned int coord_rect[3][2] = {
    {100, 250},
    {600, 100},
    {300, 350}
};

unsigned int link_road[3][2] = {
    {0, 1},
    {1, 2},
    {2, 0}
};

QString str;

#endif // GLOBAL_PAINTER_H
