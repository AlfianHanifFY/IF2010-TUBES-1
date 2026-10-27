#include "Dungeon/DungeonRankE/DungeonRankE.hpp"

DungeonRankE::DungeonRankE()
{
    this->minLevel = 0;
    this->minMobLevel = 1;
    this->maxMobLevel = 10;
    this->goldCost = 0;
    this->totalChamber = 1;

    this->currentChamber = 1;

    this->scaling = 1;
    this->goldPrize = scaling * totalChamber * 100;
    this->expPrize = scaling * totalChamber * 10;
    this->masteryPrize = scaling * totalChamber * 1;

    int chance = rand() % 100;
    if (chance <= 30)
    {
        setDoubleDungeon();
    }
}

DungeonRankE::~DungeonRankE() {}

void DungeonRankE::populate()
{

    for (int chamberLevel = 1; chamberLevel <= this->totalChamber; ++chamberLevel)
    {
        vector<Mob *> mobs = {};
        int randomSize = (rand() % 3) + 1;

        float increment = static_cast<float>(maxMobLevel - minMobLevel + 1) / totalChamber;
        int minLevel = minMobLevel + static_cast<int>((chamberLevel - 1) * increment);
        int maxLevel = minMobLevel + static_cast<int>(chamberLevel * increment) - 1;
        maxLevel = std::min(maxLevel, maxMobLevel); 

        for (int i = 0; i < randomSize; ++i)
        {
            int randomMob = (rand() % 4);
            int level = (rand() % (maxLevel - minLevel + 1)) + minLevel;

            switch (randomMob)
            {
            case 0:
                mobs.push_back(new Skeleton(level));
                break;
            case 1:
                mobs.push_back(new Goblin(level));
                break;
            case 2:
                mobs.push_back(new Slime(level));
                break;
            case 3:
                mobs.push_back(new Orc(level));
                break;
            }
        }
        dungeonMob[chamberLevel] = mobs;
    }
    scaleMobs(scaling);
}
