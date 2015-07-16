
#include "add_functions.h"

void addRoad(Map* map, t_coordinate x, t_coordinate y)
{
    TMainRoad* road = new TMainRoad;
    road->road_id = 1;
    road->cur_pos.X = x;
    road->cur_pos.Y = y;
    road->type = 0;
    map->field[x][y].road.push_back( road );
    map->field[x][y].status = FILL_OBJECT;
}

void addTestRoad(Map* map)
{
    addRoad(map, 11,11);
    addRoad(map, 11,12);
    addRoad(map, 12,12);
    addRoad(map, 12,13);
    addRoad(map, 12,14);
}

void addBuildObj(Map* map, TMainObject* build, t_coordinate x, t_coordinate y, unsigned object_id)
{
//    TMainObject* build = new TMainObject;
    build->object_id = object_id;
    build->cur_pos.X = x;
    build->cur_pos.Y = y;

    for (unsigned i = 0; i < BUILD_WIDTH; ++i)
    {
        for (unsigned j = 0; j < BUILD_HEIGHT; ++j)
        {
            map->field[x+i][y+j].object.push_back(build);
            map->field[x+i][y+j].status = FILL_OBJECT;
        }
    }

    Package pack;
    pack.count_good = 2;
    pack.good_type = 1;
    pack.width_good = 1;
    build->goods.push_back(pack);

}

void addTestObject(Map* map)
{
    TWareHouse* warhouse = new TWareHouse();
    TMine* mine = new TMine();
    TLumberJack* lumber_jack = new TLumberJack();

    addBuildObj(map, warhouse, 10, 9, 1);
    addBuildObj(map, mine, 13, 14, 2);
    addBuildObj(map, lumber_jack, 5, 10, 3);
}


void set_doList( TMainDynObject* obj, std::vector<checkPoint> stations, unsigned first_station)
{
    obj->resetObj();

    for (unsigned i = 0; i < stations.size(); ++i)
    {
//        qDebug() << "add station " << i;
        obj->stations.push_back(stations[i]);
    }
//    qDebug() << "Staton size = " << obj->stations.size();
    obj->next_station = obj->stations.end()-1;

}

void createDynObject(Map* map, Point pos, float speed)
{
    TMainDynObject* obj = new TMainDynObject;
    obj->cur_pos.X  = pos.X;
    obj->cur_pos.Y  = pos.Y;
    obj->speed      = speed;

    map->field[pos.X][pos.Y].dynObjects.push_back(obj);
    map->dynObjects.push_back(obj);
}

void addDynObject(Map* map, t_coordinate x, t_coordinate y, std::vector<checkPoint> stations, unsigned first_station
                  , float speed)
{
    TMainDynObject* obj = new TMainDynObject;
    obj->cur_pos.X = x;
    obj->cur_pos.Y = y;
    obj->speed = speed;

    set_doList(obj, stations, first_station);
    map->dynObjects.push_back(obj);
}

void calcStepsForDynObject(Map* map, TMainDynObject* obj)
{
    t_coordinate x_point = (*obj->next_station).point.X;
    t_coordinate y_point = (*obj->next_station).point.Y;

    if (map->field[x_point][y_point].road.size() != 0 || map->field[x_point][y_point].object.size() != 0)
    {
       std::deque<Point> path;
       Find_path find_path;
       find_path.find_road_path(map, Point(obj->cur_pos.X,obj->cur_pos.Y), Point(x_point,y_point), &path);

       if (path.size() != 0)
       {
           obj->change_path(path);
       }
    }

//    obj->orientation = obj->steps[0];
//    obj->steps.erase(obj->steps.begin());
//    obj->left_path = 0;
}

void addTestDynObject(Map* map)
{
    std::vector<checkPoint> stations;
    checkPoint station;

    station.point.X = 13;
    station.point.Y = 14;
    station.get_all = true;
    station.put_all = false;
    stations.push_back(station);

    station.point.X = 11;
	station.point.Y = 10;
	station.get_all = false;
	station.put_all = true;
	stations.push_back(station);

//    addDynObject(map, 11, 10, stations, 0, 4);
    createDynObject(map, Point(11,12), 4);

//    (*map->dynObjects.back()).cur_pos.X = 11;
//    (*map->dynObjects.back()).cur_pos.Y = 10;


//    calcStepsForDynObject(map, map->dynObjects.back());
}
