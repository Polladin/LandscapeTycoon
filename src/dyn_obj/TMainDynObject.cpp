/*
 * TMainDynObject.cpp
 *
 *  Created on: Dec 10, 2014
 *      Author: akukushk
 */


#include "TMainDynObject.h"


std::list<Package>::iterator findGood(std::list<Package>* goods, t_good good_type)
{
	std::list<Package>::iterator it  =  goods->begin();
	std::list<Package>::iterator ite =  goods->end();
	for (; it != ite; ++it)
	{
		if (it->good_type == good_type)
		{
			break;
		}
	}
	return it;
}

void TMainDynObject::arrived(TMainObject* end_point)
{
    if (cur_pos.X != next_station->point.X || cur_pos.Y != next_station->point.Y) return;

	//UNLOAD
	if (next_station->put_all && loads > 0)
	{
		std::list<Package>::iterator it_in_dyn_object  = goods.begin();
		std::list<Package>::iterator ite_in_dyn_object = goods.end();
		std::list<Package>::iterator it_in_build;

		while (it_in_dyn_object != ite_in_dyn_object)
		{
			if ((it_in_build = findGood(&end_point->goods, it_in_dyn_object->good_type)) != end_point->goods.end())
			{
				std::list<Package>::iterator rem = it_in_dyn_object;
				it_in_build->count_good += it_in_dyn_object->count_good;
				loads -= it_in_dyn_object->count_good * it_in_dyn_object->width_good;

				++it_in_dyn_object;
				goods.erase(rem);
			}
			else
			{
                std::list<Package>::iterator rem = it_in_dyn_object;
                Package pack;
                pack.good_type  = it_in_dyn_object->good_type;
                pack.width_good = it_in_dyn_object->width_good;
                pack.count_good =  it_in_dyn_object->count_good;

                loads -= it_in_dyn_object->count_good * it_in_dyn_object->width_good;

                end_point->goods.push_back(pack);
                ++it_in_dyn_object;
                goods.erase(rem);
			}
		}
	}

	//DOWNLAOD
	if(next_station->get_all && end_point->goods.size() != 0)
	{
		std::list<Package>::iterator it_in_build  = end_point->goods.begin();
		std::list<Package>::iterator ite_in_build = end_point->goods.end();
//		while (it_in_build != ite_in_build)
//		{
			Package pack;

			pack.good_type  = it_in_build->good_type;
			pack.width_good = it_in_build->width_good;

			if (it_in_build->count_good * it_in_build->width_good > max_loads - loads)
			{
                unsigned count_goods = (max_loads - loads) / it_in_build->width_good;
				pack.count_good = count_goods;
				loads += count_goods * it_in_build->width_good;
				it_in_build->count_good -= count_goods;
			}
			else
			{
				pack.count_good = it_in_build->count_good;
				loads += it_in_build->count_good * it_in_build->width_good;
				end_point->goods.erase(it_in_build);
			}

			goods.push_back(pack);
//		}
	}
}
