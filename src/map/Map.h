#ifndef MAP_H
#define MAP_H

#include "../common/common.h"
#include "../dyn_obj/TMainDynObject.h"

#include <list>

struct Field{
//    t_coordinate 	X;
//    t_coordinate 	Y;
    Point           point;
    t_status		status;

    std::list<TMainRoad*> 	road;

    std::list<TMainObject*>	object;
    std::list<TMainDynObject*> dynObjects;
};

class Map{

  public:
    void clear();

    void delBuildFromMap(TMainObject* obj, Point);

    void addExistObj(TMainObject* obj, Point);

    void moveBuildObj(TMainObject*, Point);

    TMainObject* get_build_object(Point);



    Field field[MAP_WIDTH][MAP_HEIGHT];

    std::list<TMainDynObject*>  dynObjects;
    std::list<TMainObject*>     object;
};

#endif // MAP_H
