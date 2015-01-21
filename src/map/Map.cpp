/*
 * Map.cpp
 *
 *  Created on: Dec 9, 2014
 *      Author: akukushk
 */


#include "Map.h"

template <class T>
void delete_objects(T it, T ite)
{
    for (; it != ite; ++it)
    {
        delete (*it);
    }
}

void Map::clear()
{
    for (unsigned i = 0; i < MAP_WIDTH; ++i)
    {
        for (unsigned j = 0; j < MAP_HEIGHT; ++j)
        {
            field[i][j].dynObjects.clear();
            field[i][j].object.clear();

            delete_objects(field[i][j].road.begin(), field[i][j].road.end());
            field[i][j].road.clear();
        }
    }

    delete_objects(dynObjects.begin(), dynObjects.end());
    dynObjects.clear();

    delete_objects(object.begin(), object.end());
    object.clear();

}

TMainObject* Map::get_build_object(Point point)
{
	if (field[point.X][point.Y].object.size() != 0)
	{
		return *field[point.X][point.Y].object.begin();
	}

	return 0;
}


void Map::delBuildFromMap(TMainObject* obj, Point point)
{
    std::list<TMainObject*>::iterator it  = field[point.X][point.Y].object.begin();
    std::list<TMainObject*>::iterator ite = field[point.X][point.Y].object.end();
	for(; it != ite; ++it)
	{
		if (*it == obj)
		{
			field[point.X][point.Y].object.erase(it);
			break;
		}
	}
}

void Map::addExistObj(TMainObject* obj, Point point)
{
	obj->cur_pos.X = point.X;
	obj->cur_pos.Y = point.Y;

	field[point.X  ][point.Y  ].object.push_front(obj);
	field[point.X+1][point.Y  ].object.push_front(obj);
	field[point.X  ][point.Y+1].object.push_front(obj);
	field[point.X+1][point.Y+1].object.push_front(obj);
}

void Map::moveBuildObj(TMainObject* obj, Point new_point)
{
	if (new_point.X != obj->cur_pos.X || new_point.Y != obj->cur_pos.Y)
	{
		delBuildFromMap(obj, Point(obj->cur_pos.X  ,obj->cur_pos.Y  ));
		delBuildFromMap(obj, Point(obj->cur_pos.X+1,obj->cur_pos.Y  ));
		delBuildFromMap(obj, Point(obj->cur_pos.X  ,obj->cur_pos.Y+1));
		delBuildFromMap(obj, Point(obj->cur_pos.X+1,obj->cur_pos.Y+1));

		addExistObj(obj, new_point);
	}
}
