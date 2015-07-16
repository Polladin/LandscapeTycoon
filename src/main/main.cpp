
#include <iostream>
#include <list>

#include "../map/Map.h"
#include "../test/add_functions.h"

int main()
{
    Map map;

    addTestDynObject(&map);

    TMainDynObject* obj= *map.dynObjects.begin();
    
    std::cout << "Tests are starting" << std::endl;

    if (obj->steps.size() != 0)
    {
        std::cout << "Test 1       [PASS]\n";
    }

    std::cout << "Press any key\n";
    std::cin.get();

    return 0;
}
