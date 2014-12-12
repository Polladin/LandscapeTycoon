#ifndef MAP_H
#define MAP_H

#include "../common/common.h"
#include "../dyn_obj/TMainDynObject.h"

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

    void delBuildFromMap(TMainObject* obj, Point);

    void addExistObj(TMainObject* obj, Point);

    TMainObject* get_build_object(Point);

    void moveBuildObj(TMainObject*, Point);
};

#endif // MAP_H
