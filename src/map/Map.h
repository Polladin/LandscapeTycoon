#ifndef MAP_H
#define MAP_H

#include "../common/common.h"

#include <list>

struct Field{
    t_coordinate 	X;
    t_coordinate 	Y;
    t_status		status;
    std::list<TMainObject*>	object;
    std::list<TMainRoad*> 	road;
};

class Map{

  public:
    Field field[MAP_WIDTH][MAP_HEIGHT];
    std::list<TMainDynObject*> dynObjects;
};

#endif // MAP_H
