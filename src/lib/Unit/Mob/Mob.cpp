#include "Unit/Mob/Mob.hpp"
#include <cstdlib> 
#include <ctime>   







Mob::Mob(string name, int level) : Unit(name, 50 + level * 10, 1 + level * 0.2, 30 + level * 5, 1 + level * 0.2, 5 + level * 2)
{
    this->level = level;
    this->expReward = 50 + level * 10;
    

    
    setStat(0, 5 + level * 1);
    setStat(1, 5 + level * 1);
    setStat(2, 5 + level * 1);

    setDefense(0.5 * getStat(0) + 5 * level);

    
    int basicHealValue = getStat(1) * 5;

    
    
    Skill *healSkill = new Skill("Heal", 10, 0, 0);
    healSkill->addEffect(new HealEffect("Heal Effect", "Restores health", 1, 1.0f, basicHealValue));
    addSkill(healSkill);

    this->goldReward = 100 * level;
}

Mob::~Mob()
{
    for (size_t i = 0; i < lootItemProbability.size(); ++i)
    {
        delete lootItemProbability[i].first;
    }
    lootItemProbability.clear();
}


int Mob::getLevel() const
{
    return this->level;
}

int Mob::getExpReward() const
{
    return this->expReward;
}

int Mob::getGoldReward() const
{
    return this->goldReward;
}

const vector<pair<Item *, float>> &Mob::getLootItemProbability() const
{
    return this->lootItemProbability;
}

void Mob::setLevel(int level)
{
    this->level = level;
}

void Mob::setExpReward(int expReward)
{
    this->expReward = expReward;
}







void Mob::addLoot(Item *item, float dropProbability)
{
    lootItemProbability.push_back({item, dropProbability});
}

vector<Item *> Mob::generateLoot()
{
    vector<Item *> loot;

    for (size_t i = 0; i < lootItemProbability.size(); i++)
    {
        float chance = static_cast<float>(rand()) / RAND_MAX;
        if (chance <= lootItemProbability[i].second)
        {
            loot.push_back(lootItemProbability[i].first);
        }
    }

    return loot;
}