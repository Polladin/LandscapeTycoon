
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

void addBuildObj(Map* map, t_coordinate x, t_coordinate y, unsigned object_id)
{
    TMainObject* build = new TMainObject;
    build->object_id = object_id;
    build->type = BUILD;
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
    addBuildObj(map, 10, 9, 1);
    addBuildObj(map, 13, 14, 2);
}



void addDynObject(Map* map, t_coordinate x, t_coordinate y, std::vector<checkPoint> stations, unsigned first_station
                  , float speed)
{
    TMainDynObject* obj = new TMainDynObject;
    obj->cur_pos.X = x;
    obj->cur_pos.Y = y;
    for (unsigned i = 0; i < stations.size(); ++i)
    {
        obj->stations.push_back(stations[i]);
    }
    obj->next_station = obj->stations.begin() + first_station;
    obj->speed = speed;
    obj->left_path = 0;

    map->dynObjects.push_back(obj);
}


void fake_set_path(Map* map, Point p1, Point p2, std::vector<t_step>* path)
{

	if(p1.X == 11 && p1.Y == 10 && p2.X == 13 && p2.Y == 14)
	{
        path->push_back(STEP_BOT);
		path->push_back(STEP_BOT);
		path->push_back(STEP_RIGHT);
		path->push_back(STEP_BOT);
		path->push_back(STEP_BOT);
		path->push_back(STEP_RIGHT);

		//stop step
		path->push_back(STEP_RIGHT);
	}
	else
	{
		path->push_back(STEP_LEFT);
		path->push_back(STEP_TOP);
		path->push_back(STEP_TOP);
		path->push_back(STEP_LEFT);
		path->push_back(STEP_TOP);
		path->push_back(STEP_TOP);

		//stop_step
		path->push_back(STEP_TOP);
	}
}

void calcStepsForDynObject(Map* map, TMainDynObject* obj)
{
    //call function to find path
    fake_set_path(map, obj->cur_pos, (*obj->next_station).point, &obj->steps);

    obj->orientation = obj->steps[0];
    obj->orientation = *obj->steps.begin();
    obj->steps.erase(obj->steps.begin());
    obj->left_path = 0;
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

    addDynObject(map, 11, 10, stations, 0, 4);
    calcStepsForDynObject(map, map->dynObjects.back());
}
