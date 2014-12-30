/*
 * find_path.h
 *
 *  Created on: 13.12.2014
 *      Author: MegaAlex
 */

#ifndef FIND_PATH_H_
#define FIND_PATH_H_

#include <deque>

#include "../common/common.h"
#include "../map/Map.h"

enum
{
	  WHITE 	= 1
	, GRAY 		= 2
	, BLACK 	= 3

    , INFINITE_PATH = -1

	, MAX_ADJ	= 4 // need move to Map.h or common.h
};

struct path_point
{
    Point       self_point;
	unsigned 	color;
	int 		cost;
    path_point	*prev;
};


class Find_path
{

public:
    Find_path()
    {
        for (unsigned i = 0; i < MAP_WIDTH; ++i)
            for (unsigned j = 0; j < MAP_WIDTH; ++j)
                cell[i][j].self_point = Point(i,j);
    }

	void find_road_path (Map* map, Point src, Point dst, std::deque<Point>* path);

private:

	void init ();

	bool get_adj (Point const src, Point& adj, Map* map, unsigned id_adj);
	bool is_needed_adj(Map* map, Point const is_adj, Point& adj, unsigned& id_adj);
    bool is_pre_last_point(Map* map, Point const cur_pos, Point const target_pos);

	std::deque<Point> queue;

	path_point cell[MAP_WIDTH][MAP_HEIGHT];
};


#endif /* FIND_PATH_H_ */
