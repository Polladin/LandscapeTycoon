#ifndef ADD_FUNCTIONS_H
#define ADD_FUNCTIONS_H

#include <vector>
#include "../map/Map.h"


void addRoad(Map* map, t_coordinate x, t_coordinate y);

void addTestRoad(Map* map);


void addDynObject(Map* map, t_coordinate x, t_coordinate y);

void addBuildObj(Map* map, t_coordinate x, t_coordinate y, unsigned object_id);

void addTestObject(Map* map);

void addDynObject(Map* map, t_coordinate x, t_coordinate y, std::vector<Point> stations, unsigned first_station, float speed);
void fake_set_path(Map* map, Point p1, Point p2, std::vector<t_step>* path);
void calcStepsForDynObject(Map* map, TMainDynObject* obj);
void addTestDynObject(Map* map);

#endif // ADD_FUNCTIONS_H
