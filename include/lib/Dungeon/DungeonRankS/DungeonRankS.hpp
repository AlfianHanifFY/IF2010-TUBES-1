#ifndef DungeonRankS_HPP
#define DungeonRankS_HPP

#include <iostream>
using namespace std;

#include "../Dungeon.hpp"

class DungeonRankS : public Dungeon
{
public:
    DungeonRankS();
    ~DungeonRankS();

    void populate() override;
};

#endif