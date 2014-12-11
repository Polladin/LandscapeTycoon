/*
 * TMainDynObject.h
 *
 *  Created on: Dec 10, 2014
 *      Author: akukushk
 */

#ifndef TMAINDYNOBJECT_H_
#define TMAINDYNOBJECT_H_

#include "../common/common.h"

class TMainDynObject
{
  public:

	TMainDynObject(){ loads = 0; max_loads = 1;}

	void arrived(TMainObject*);

    Point cur_pos;

    std::vector<t_step> steps;
    std::vector<checkPoint> stations;
    std::vector<checkPoint>::iterator next_station;

    t_step orientation;
    float speed;
    float left_path;

    std::list<Package> goods;
    unsigned loads;
    unsigned max_loads;
};

#endif /* TMAINDYNOBJECT_H_ */
