#ifndef COMMON_H
#define COMMON_H

#include <vector>
#include <list>
#include <iterator>

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

namespace obj_types{

enum
{
      UNSPECIFIED
    , WAREHOUSE
    , MINE
    , LUMBERJACK
    , SAWMILL
    , CORN_FIELD
    , BAKERY
    , WELL
    , PIG_FARM
    , BUTCHER
};

}

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
        type = obj_types::UNSPECIFIED;
    }

    //return is container empty
    virtual bool unload(std::list<Package> &unload_container)
    {
        bool full_unload = false;

        std::list<Package>::iterator it  = unload_container.begin();
        std::list<Package>::iterator ite = unload_container.end();
        while (it != ite)
        {
            add_good(*it) ? it = unload_container.erase(it) : ++it, full_unload=false;
            /*if (add_good(*it))
                it = unload_container.erase(it);
            else
                ++it*/;
        }
    }

    Point cur_pos;

    unsigned int object_id;
    t_object type;

    std::list<Package> goods;
    unsigned  loads;

private:
    virtual bool add_good(Package &pack)
    {
        std::list<Package>::iterator it  = goods.begin();
        std::list<Package>::iterator ite = goods.end();
        for (; it != ite; ++it)
        {
            if (pack.good_type == it->good_type)
            {
                it->count_good += pack.count_good;
                pack.count_good = 0;
                return true;
            }
        }

        goods.push_back(pack);
        pack.count_good = 0;

        return true;
    }
};

class TWareHouse : public TMainObject
{
public:
    TWareHouse(): TMainObject()
    {
        type = obj_types::WAREHOUSE;
        get_all_types_of_goods = false;
    }

    unsigned int get_good_count()
    {
        unsigned int max_count = 0;
        std::list<Package>::iterator it  = goods.begin();
        std::list<Package>::iterator ite = goods.end();
        for (; it != ite; ++it)
        {
            max_count = it->count_good > max_count ? it->count_good : max_count;
        }

        return max_count;
    }

private:
    bool get_all_types_of_goods;
};

class TMine : public TMainObject
{
public:
    TMine(): TMainObject()
    {
        type = obj_types::MINE;

        good.count_good = 100;
        good.good_type = 1;
        good.width_good = 2;
    }

    unsigned int get_good_count()
    {
        return good.count_good;
    }

private:
    Package good;
};

class TLumberJack : public TMainObject
{
public:
    TLumberJack() : TMainObject()
    {
        type = obj_types::LUMBERJACK;
        wood.count_good = 50;
        wood.good_type  = 2;
        wood.width_good = 1;
    }

    unsigned int get_wood_count()
    {
        return wood.count_good;
    }

private:
    Package wood;
};

class TSawMill : public TMainObject
{
public:
    TSawMill() : TMainObject()
    {
        type = obj_types::SAWMILL;
    }

private:
    Package wood;
    Package timber;
};

class TCornField : public TMainObject
{
public:
    TCornField() : TMainObject()
    {
        type = obj_types::CORN_FIELD;
    }

private:
    Package corn;
};

class TBakery : public TMainObject
{
public:
    TBakery() : TMainObject()
    {
        type = obj_types::BAKERY;
    }

private:
    Package water;
    Package corn;
    Package bread;
};

class TWell : public TMainObject
{
public:
    TWell() : TMainObject()
    {
        type = obj_types::WELL;
    }

private:
    Package water;
};

class TPigFarm : public TMainObject
{
public:
    TPigFarm() : TMainObject()
    {
        type = obj_types::PIG_FARM;
    }

private:
    Package water;
    Package corn;
    Package pig;
};

class TButcher : public TMainObject
{
public:
    TButcher() : TMainObject()
    {
        type = obj_types::BUTCHER;
    }

private:
    Package pig;
    Package meet;
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
