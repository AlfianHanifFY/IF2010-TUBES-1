#ifndef MOB_HPP
#define MOB_HPP

#include <iostream>
using namespace std;

#include <vector>

#include "../Unit.hpp"
#include "Item/Item.hpp"
#include "Effect/Effect.hpp"
#include "Effect/SkillEffect/StatReductionEffect/StatReductionEffect.hpp"
#include "Effect/SkillEffect/RageEffect/RageEffect.hpp"
#include "Effect/SkillEffect/SlowEffect/SlowEffect.hpp"
#include "Effect/SkillEffect/BurnEffect/BurnEffect.hpp"
#include "Effect/SkillEffect/StunEffect/StunEffect.hpp"
#include "Effect/SkillEffect/DecayEffect/DecayEffect.hpp"
#include "Effect/SkillEffect/HealthDrainEffect/HealthDrainEffect.hpp"
#include "Effect/SkillEffect/ManaDrainEffect/ManaDrainEffect.hpp"
#include "Effect/SkillEffect/HealEffect/HealEffect.hpp"
#include "Effect/SkillEffect/CriticalDamageEffect/CriticalDamageEffect.hpp"
#include "Effect/SkillEffect/SkillEffect.hpp"
#include "Effect/SkillEffect/WeakenEffect/WeakenEffect.hpp"
#include "Effect/SkillEffect/BrittleEffect/BrittleEffect.hpp"
#include "Effect/SkillEffect/StatReductionEffect/StatReductionEffect.hpp"

class Mob : public Unit
{
protected:
    int expReward;
    int goldReward;
    vector<pair<Item *, float>> lootItemProbability;

public:
    Mob(string name, int level);
    virtual ~Mob();

    
    int getLevel() const;
    int getExpReward() const;
    int getGoldReward() const;
    const vector<pair<Item *, float>> &getLootItemProbability() const;

    void setLevel(int level);
    void setExpReward(int expReward);
    void setGoldReward(int goldReward);

    
    virtual void act(Unit *target) = 0;

    
    void addLoot(Item *item, float dropProbability);
    vector<Item *> generateLoot();

    virtual string getType() = 0;
};

#endif
