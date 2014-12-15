/*
 * find_path.cpp
 *
 *  Created on: 13.12.2014
 *      Author: MegaAlex
 */

#include "find_path.h"


void Find_path::init()
{
	for (unsigned i = 0; i < MAP_WIDTH; ++i)
	{
		for (unsigned j = 0; j < MAP_HEIGHT; ++j)
		{
			cell[i][j].color = WHITE;
            cell[i][j].cost  = INFINITE_PATH;
            cell[i][j].prev  = 0;
		}
	}
	queue.clear();
}


bool Find_path::is_needed_adj(Map* map, Point const is_adj, Point& adj, unsigned& id_adj)
{
	if (map->field[is_adj.X][is_adj.Y].road.size() != 0)
	{
		if (id_adj == 0)
		{
			adj.X = is_adj.X;
			adj.Y = is_adj.Y;
			return true;
		}
		else
		{
			--id_adj;
		}
	}

	return false;
}

bool Find_path::get_adj(Point const src, Point& adj, Map* map, unsigned id_adj)
{
	for (unsigned i = 0; i < MAX_ADJ; ++i)
	{
		switch (i)
		{
			case 0: //left adj
				if (src.X == 0) continue;
				if (is_needed_adj(map, Point(src.X-1,src.Y), adj, id_adj)) return true;
				break;
			case 1: //right adj
				if (src.X == MAP_WIDTH) continue;
				if (is_needed_adj(map, Point(src.X+1,src.Y), adj, id_adj)) return true;
				break;
			case 2: //top adj
				if (src.Y == 0) continue;
				if (is_needed_adj(map, Point(src.X,src.Y-1), adj, id_adj)) return true;
				break;
			case 3: //bot adj
				if (src.Y == MAP_HEIGHT) continue;
				if (is_needed_adj(map, Point(src.X,src.Y+1), adj, id_adj)) return true;
				break;
		}
	}

	return false;
}

void Find_path::find_road_path (Map* map, Point src, Point dst, std::deque<Point>* path)
{
	Point v;

	init();

	cell[src.X][src.Y].color = GRAY;
	cell[src.X][src.Y].cost	 = 0;
	cell[src.X][src.Y].prev	 = 0;

	queue.push_back(src);

	while (queue.size() != 0)
	{
		Point u = queue.front();
		queue.pop_front();

        if ((u.X == dst.X) && (u.Y == dst.Y))
        {
            path_point* p = &cell[u.X][u.Y];
            while (p != 0)
            {
                path->push_front(p->self_point);
                p = p->prev;
            }
        }

		unsigned i=0;
		while (get_adj(u, v, map, i++))
		{
			if (cell[v.X][v.Y].color == WHITE)
			{
				cell[v.X][v.Y].color = GRAY;
				cell[v.X][v.Y].cost = cell[u.X][u.Y].cost+1;
                cell[v.X][v.Y].prev = &cell[u.X][u.Y];
				queue.push_back(v);
			}
		}
		cell[u.X][u.Y].color = BLACK;
	}
}




