#ifndef DUNGEONRANKE_HPP
#define DUNGEONRANKE_HPP

#include <iostream>
using namespace std;

#include "../Dungeon.hpp"

class DungeonRankE : public Dungeon
{
public:
    DungeonRankE();
    ~DungeonRankE();

    void populate() override;
};

#endif