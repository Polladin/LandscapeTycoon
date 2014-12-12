
#include "animate.h"
#include "../../src/dyn_obj/TMainDynObject.cpp"

void animate_one_state(Map* map)
{
    for (std::list<TMainDynObject*>::iterator i = map->dynObjects.begin(); i != map->dynObjects.end(); ++i)
    {
        TMainDynObject* obj = *i;
        if (obj->steps.size() == 0)
        {
            TMainObject* build = map->get_build_object(Point((*obj->next_station).point.X,(*obj->next_station).point.Y));
            if (build != 0)
            {
                obj->arrived(build);
            }
            if ( (++obj->next_station) == obj->stations.end()) obj->next_station = obj->stations.begin();
            calcStepsForDynObject(map, obj);
        }
        stepToDynObject(*i);
    }
}


void stepToDynObject(TMainDynObject* obj)
{
    if (obj->steps.size() != 0)
    {
        obj->left_path += obj->speed;
        if (obj->orientation == STEP_BOT || obj->orientation == STEP_TOP )
        {
            if (obj->left_path > POINT_HEIGHT)
            {
                doOneStep(obj);
            }
        }
        else
        {
            if (obj->left_path > POINT_WIDTH)
            {
                doOneStep(obj);
            }
        }
    }
}


void doOneStep(TMainDynObject* obj)
{
    switch (obj->orientation)
    {
        case STEP_TOP:
                --obj->cur_pos.Y;
            break;

        case STEP_BOT:
                ++obj->cur_pos.Y;
            break;

        case STEP_LEFT:
                --obj->cur_pos.X;
            break;

        case STEP_RIGHT:
                ++obj->cur_pos.X;
            break;
    }

    obj->orientation = *obj->steps.begin();
    obj->steps.erase(obj->steps.begin());
    obj->left_path = 0;
}
