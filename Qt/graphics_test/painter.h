#ifndef PAINTER_H
#define PAINTER_H

#include <QtGui>

#include "../../src/map/Map.h"

const unsigned menu_coords[][4] =
{
    {250,20,300,50},
    {270,80,40 ,20},
    {340,80,40 ,20},
    {410,80,40 ,20},
    {150,20,40 ,20},
    {150,60,40 ,20}
};

enum{
      LABEL         = 0
    , BUT_OK        = 1
    , BUT_LOAD      = 2
    , BUT_UNLOAD    = 3
    , BUT_SAVE      = 4
    , BUT_LOADXML   = 5

    , COUNT_BUT     = 6
};

int isButtonPress(Point);

void paint_map_on_display(QPainter* painter, Map* map);

void paint_road(QPainter* painter, TMainRoad* road);

void paint_build(QPainter* painter, TMainObject* road);

void paintDynObject(QPainter* painter, TMainDynObject* obj);

bool isPainted(t_status status);


// Debug label painter
inline QRect get_menu_rect(unsigned name);

void paint_debug_label(QPainter* painter, QString label);

#endif // PAINTER_H
