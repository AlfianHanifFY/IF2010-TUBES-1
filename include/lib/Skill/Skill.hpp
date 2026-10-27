#ifndef SKILL_HPP
#define SKILL_HPP

#include <iostream>
using namespace std;
#include "../Effect/Effect.hpp"
#include "../Unit/Unit.hpp"
#include "../Effect/SkillEffect/HealthDrainEffect/HealthDrainEffect.hpp"
#include <vector>

class Skill
{
protected:
    string name;
    int manaCost;
    int masteryCost;
    int damage;
    vector<Effect *> effects;
    vector<string> prerequisites;

public:
    Skill(string name, int manaCost, int masteryCost, int damage);
    virtual ~Skill();

    
    string getName() const;
    int getManaCost() const;
    int getMasteryCost() const;
    int getDamage() const;
    const vector<Effect *> &getEffects() const;
    const vector<string> &getPrerequisites() const;

    
    void setName(const string &name);
    void setManaCost(int manaCost);
    void setMasteryCost(int masteryCost);
    void setDamage(int damage);

    
    void addEffect(Effect *effect);
    void removeEffect(Effect *effect);

    void addPrerequisite(const string &prerequisiteSkillName);

    virtual bool use(Unit *target);

    
    bool operator==(const Skill &other) const;
};

#endif