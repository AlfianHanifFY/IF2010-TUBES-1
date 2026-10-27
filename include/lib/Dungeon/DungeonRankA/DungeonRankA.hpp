#ifndef DUNGEONRANKA_HPP
#define DUNGEONRANKA_HPP

#include <iostream>
using namespace std;

#include "../Dungeon.hpp"

class DungeonRankA : public Dungeon
{
public:
    DungeonRankA();
    ~DungeonRankA();
    void populate() override;
};

#endif
