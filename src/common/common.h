#ifndef COMMON_H
#define COMMON_H

#include <vector>
#include <list>

enum{
      MAP_WIDTH = 100
    , MAP_HEIGHT = 100

    , MAY_BUILD_ROAD = 1
    , FILL_OBJECT = 2


    , POINT_WIDTH = 20
    , POINT_HEIGHT = 20

    , BUILD = 1

    , BUILD_WIDTH = 2
    , BUILD_HEIGHT = 2


    , STEP_STOP 	= 0
    , STEP_LEFT 	= 1
    , STEP_RIGHT 	= 2
    , STEP_TOP 		= 3
    , STEP_BOT 		= 4

    , SET_PATH_FOR_DYN_OBJ = 1
};

typedef int 		 t_coordinate;
typedef unsigned int t_status;
typedef unsigned int t_object;
typedef unsigned int t_road;
typedef unsigned int t_step;
typedef unsigned int t_good;

struct Point
{
    Point(){X=static_cast<t_coordinate>(0); Y=static_cast<t_coordinate>(0);}
    Point(t_coordinate x, t_coordinate y){X=x; Y=y;}
    t_coordinate X;
    t_coordinate Y;
};

struct Package
{
	t_good 			good_type;
	unsigned int	count_good;
	unsigned int	width_good;
};

struct checkPoint
{
	Point point;
    std::list<Package> doListArrive;
	std::list<Package> doListOut;

	bool get_all;
	bool put_all;
};

class TMainObject
{
  public:
    TMainObject()
    {
        loads = 100;
    }

    Point cur_pos;

    unsigned int object_id;
    t_object type;

    std::list<Package> goods;
    unsigned  loads;
};

class TMainRoad
{
  public:
    TMainRoad() { cur_pos.X=0; cur_pos.Y=0; }
    TMainRoad(Point p) { cur_pos.X=p.X; cur_pos.Y=p.Y; }

    Point cur_pos;

    unsigned int road_id;
    t_road type;
};


#endif // COMMON_H
