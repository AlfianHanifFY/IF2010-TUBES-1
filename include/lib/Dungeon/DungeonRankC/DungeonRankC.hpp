#ifndef DUNGEON_RANK_C_HPP
#define DUNGEON_RANK_C_HPP

#include "../Dungeon.hpp"

using namespace std;

class DungeonRankC : public Dungeon
{
public:
    DungeonRankC();
    ~DungeonRankC();
    void populate() override; 
};

#endif
