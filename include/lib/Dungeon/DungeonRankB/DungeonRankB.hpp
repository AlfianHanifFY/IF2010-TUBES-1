#ifndef DUNGEONRANKB_HPP
#define DUNGEONRANKB_HPP

#include <iostream>
using namespace std;

#include "../Dungeon.hpp"

class DungeonRankB : public Dungeon
{
public:
    DungeonRankB();
    ~DungeonRankB();
    void populate() override;
};

#endif
