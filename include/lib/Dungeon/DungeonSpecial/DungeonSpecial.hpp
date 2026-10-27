#ifndef DungeonSpecial_HPP
#define DungeonSpecial_HPP

#include <iostream>
using namespace std;

#include "../Dungeon.hpp"

class DungeonSpecial : public Dungeon
{
public:
    DungeonSpecial();
    ~DungeonSpecial();

    void populate() override;
};

#endif