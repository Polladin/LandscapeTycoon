
#include "animate.h"


void animate_one_state(Map* map)
{
    for (std::list<TMainDynObject*>::iterator i = map->dynObjects.begin(); i != map->dynObjects.end(); ++i)
    {
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
