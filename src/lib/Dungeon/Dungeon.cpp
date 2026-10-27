#include "Dungeon/Dungeon.hpp"

using namespace std;

Dungeon::Dungeon() : currentChamber(1)
{

    this->isSpecial = false;
    this->totalChamber = 0;
    this->isWin = false;
    this->isDouble = false;
}

Dungeon::~Dungeon()
{
    
    for (auto &pair : dungeonMob)
    {
        for (Mob *mob : pair.second)
        {
            delete mob; 
        }
    }

    
    for (Item *item : itemPrize)
    {
        delete item; 
    }

    
    if (player)
    {
        delete player; 
    }
}

bool Dungeon::canEnter(Character *player)
{
    if (player->getLevel() < minLevel)
    {
        return false;
    }
    else if (player->getGold() < goldCost)
    {
        return false;
    }
    else
    {
        this->player = player;
        return true;
    }
}

int Dungeon::getGoldPenalty()
{
    return (30 * totalChamber * scaling * -1);
}

int Dungeon::getExpPenalty()
{
    return (5 * totalChamber * scaling * -1);
}

bool Dungeon::isChamberFinished()
{
    vector<Mob *> mobs = this->getChamberMob();

    for (auto it = mobs.begin(); it != mobs.end(); it++)
    {
        if ((*it)->getCurrentHealth() > 0)
        {
            return false;
        }
    }

    return true;
}

void Dungeon::nextChamber()
{
    if (currentChamber < totalChamber)
    {
        currentChamber += 1;
    }
}

vector<Mob *> Dungeon::getChamberMob()
{
    return dungeonMob.at(currentChamber);
}

void Dungeon::update()
{
}

int Dungeon::getCurrentChamber()
{
    return this->currentChamber;
}

void Dungeon::setDoubleDungeon()
{
    this->isDouble = true;
    scaling *= 2;
}

bool Dungeon::isDungeonFinished()
{
    if (currentChamber == totalChamber)
    {
        return isChamberFinished();
    }
    else
    {
        return false;
    }
}

void Dungeon::scaleMobs(int scale)
{
    
    for (int i = 1; i <= totalChamber; i++)
    {
        for (size_t j = 0; j < dungeonMob.at(i).size(); j++)
        {
            dungeonMob.at(i).at(j)->scaleStats(scale);
        }
    }
}

int Dungeon::getTotalChamber()
{
    return this->totalChamber;
}

map<int, vector<Mob *>> Dungeon::getDungeonMob()
{
    return this->dungeonMob;
}

int Dungeon::getGoldCost()
{
    return this->goldCost;
}

void Dungeon::setIsWin()
{
    this->isWin = true;
}

bool Dungeon::getIsWin()
{
    return this->isWin;
}

int Dungeon::getGoldPrize()
{
    return this->goldPrize;
}
int Dungeon::getExpPrize()
{
    return this->expPrize;
}
int Dungeon::getMasteryPrize()
{
    return this->masteryPrize;
}

void Dungeon::setSpecial()
{
    this->isSpecial = true;
}
bool Dungeon::getSpecial()
{
    return this->isSpecial;
}

bool Dungeon::getIsDouble()
{
    return this->isDouble;
}