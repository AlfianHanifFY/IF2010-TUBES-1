#ifndef DUNGEONRANKD_HPP
#define DUNGEONRANKD_HPP

#include <iostream>
using namespace std;

#include "../Dungeon.hpp"

class DungeonRankD : public Dungeon
{
public:
    DungeonRankD();
    ~DungeonRankD();

    void populate() override;
};

#endif
