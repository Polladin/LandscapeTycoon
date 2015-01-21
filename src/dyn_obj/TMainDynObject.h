/*
 * TMainDynObject.h
 *
 *  Created on: Dec 10, 2014
 *      Author: akukushk
 */

#ifndef TMAINDYNOBJECT_H_
#define TMAINDYNOBJECT_H_

#include <deque>

#include "../common/common.h"

enum{
      STATE_STOP = 0
    , STATE_MOVE = 1
};

class TMainDynObject
{

private:

    t_step find_next_step(Point cur_pos, Point next_pos);

public:

    TMainDynObject()
    {
        loads       = 0;
        max_loads   = 1;
        speed       = 0.5;
        state       = STATE_MOVE;
    }

    void resetObj()
    {
        left_path    = 0;
        state       = STATE_MOVE;
        stations.clear();
        steps.clear();
    }

	void arrived(TMainObject*);
    bool change_path(std::deque<Point>& path);

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

    unsigned state;
};

#endif /* TMAINDYNOBJECT_H_ */
