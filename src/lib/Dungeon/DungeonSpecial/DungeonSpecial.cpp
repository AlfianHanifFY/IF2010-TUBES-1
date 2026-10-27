#include "Dungeon/DungeonSpecial/DungeonSpecial.hpp"

DungeonSpecial::DungeonSpecial()
{
    this->minLevel = 0;
    this->minMobLevel = 0;
    this->maxMobLevel = 1000;
    this->goldCost = 0;
    this->totalChamber = 100;
    this->currentChamber = 1;

    this->scaling = 1;

    this->isSpecial = true;
    this->goldPrize = scaling * totalChamber * 30;
    this->expPrize = scaling * totalChamber * 5;
    this->masteryPrize = scaling * totalChamber * 1;
}

DungeonSpecial::~DungeonSpecial() {}

void DungeonSpecial::populate()
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
