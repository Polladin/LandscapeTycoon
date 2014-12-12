#ifndef PAINTER_H
#define PAINTER_H

#include <QtGui>

#include "../../src/map/Map.h"


void paint_map_on_display(QPainter* painter, Map* map);

void paint_road(QPainter* painter, TMainRoad* road);

void paint_build(QPainter* painter, TMainObject* road);

void paintDynObject(QPainter* painter, TMainDynObject* obj);

bool isPainted(t_status status);

#endif // PAINTER_H
