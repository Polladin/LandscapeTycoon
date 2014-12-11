#ifndef ANIMATE_H
#define ANIMATE_H

#include "../../src/map/Map.h"
#include "../../src/dyn_obj/TMainDynObject.h"
#include "../../src/test/add_functions.h"

void animate_one_state(Map* map);

void stepToDynObject(TMainDynObject*);

void doOneStep(TMainDynObject*);

#endif // ANIMATE_H
