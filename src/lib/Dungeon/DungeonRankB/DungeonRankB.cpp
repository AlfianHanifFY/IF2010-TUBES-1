#include "Dungeon/DungeonRankB/DungeonRankB.hpp"

DungeonRankB::DungeonRankB()
{
    this->minLevel = 25;
    this->minMobLevel = 20;
    this->maxMobLevel = 50;
    this->goldCost = 300;
    this->totalChamber = 4;

    this->currentChamber = 1;

    this->scaling = 3;
    this->goldPrize = scaling * totalChamber * 100;
    this->expPrize = scaling * totalChamber * 10;
    this->masteryPrize = scaling * totalChamber * 1;

    int chance = rand() % 100;
    if (chance <= 15)
    {
        setDoubleDungeon();
    }
}

DungeonRankB::~DungeonRankB() {}

void DungeonRankB::populate()
{
    
    for (int chamberLevel = 1; chamberLevel <= this->totalChamber; ++chamberLevel)
    {
        vector<Mob *> mobs = {};
        int randomSize = (rand() % 3) + 1;

        float increment = static_cast<float>(maxMobLevel - minMobLevel + 1) / totalChamber;
        int minLevel = minMobLevel + static_cast<int>((chamberLevel - 1) * increment);
        int maxLevel = minMobLevel + static_cast<int>(chamberLevel * increment) - 1;
        maxLevel = std::min(maxLevel, maxMobLevel); 

        if (chamberLevel < totalChamber)
        {
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
        }
        else
        {
            int randomMob = (rand() % 4);
            int level = (rand() % (maxLevel - minLevel + 1)) + minLevel;
            switch (randomMob)
            {
            case 0:
                mobs.push_back(new DarkKnight(level));
                break;
            case 1:
                mobs.push_back(new DemonLord(level));
                break;
            case 2:
                mobs.push_back(new Lich(level));
                break;
            case 3:
                mobs.push_back(new Ogre(level));
                break;
            }
        }

        dungeonMob[chamberLevel] = mobs;
    }

    scaleMobs(scaling);
}
