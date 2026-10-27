#ifndef DUNGEON_HPP
#define DUNGEON_HPP

#include <iostream>
#include <vector>
#include <string>

#include "Unit/Unit.hpp"
#include "Unit/Mob/BasicMob/Goblin/Goblin.hpp"
#include "Unit/Mob/BasicMob/Slime/Slime.hpp"
#include "Unit/Mob/BasicMob/Skeleton/Skeleton.hpp"
#include "Unit/Mob/BasicMob/Orc/Orc.hpp"
#include "Unit/Mob/BasicMob/BasicMob.hpp"
#include "Unit/Mob/BossMob/Ogre/Ogre.hpp"
#include "Unit/Mob/BossMob/BossMob.hpp"
#include "Unit/Mob/BossMob/Lich/Lich.hpp"
#include "Unit/Mob/BossMob/DarkKnight/DarkKnight.hpp"
#include "Unit/Mob/BossMob/DemonLord/DemonLord.hpp"
#include "Unit/Mob/Mob.hpp"
#include "Unit/Character/Character.hpp"

using namespace std;

class Dungeon
{
protected:
    int minLevel;
    int minMobLevel;
    int maxMobLevel;
    int goldCost;
    int totalChamber;
    int currentChamber;
    int scaling;

    Character *player;
    vector<Item *> itemPrize;
    int goldPrize;
    int expPrize;
    int masteryPrize;
    map<int, vector<Mob *>> dungeonMob; 

    bool isSpecial;
    bool isWin;
    bool isDouble;

public:
    Dungeon();
    virtual ~Dungeon();

    virtual void populate() = 0;

    bool canEnter(Character *player);

    bool isChamberFinished();
    map<int, vector<Mob *>> getDungeonMob();
    vector<Mob *> getChamberMob();

    void update();

    int getCurrentChamber();
    int getTotalChamber();

    void setSpecial();
    bool getSpecial();

    void setDoubleDungeon();

    bool isDungeonFinished();

    void nextChamber();

    bool getIsDouble();

    void scaleMobs(int scale);

    int getGoldCost();

    void setIsWin();
    bool getIsWin();

    int getGoldPrize();
    int getExpPrize();
    int getMasteryPrize();

    int getGoldPenalty();
    int getExpPenalty();
};

#endif