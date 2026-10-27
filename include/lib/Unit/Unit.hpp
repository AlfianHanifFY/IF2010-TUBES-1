#ifndef UNIT_HPP
#define UNIT_HPP

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#include "../Skill/Skill.hpp"
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

class Skill;

class Unit
{
protected:
    string assets;
    string name;
    int currentHealth;
    int maxHealth;
    int healthRegen;
    int currentMana;
    int maxMana;
    int manaRegen;
    int attackDamage;
    int defense;
    vector<Skill *> skills;
    vector<Effect *> activeEffects;
    vector<int> stats; 
    bool isStunned;
    int level;
    vector<string> log;

public:
    Unit(string name, int maxHealth, int healthRegen, int maxMana, int manaRegen, int attackDamage);
    virtual ~Unit();

    
    string getName() const;
    int getCurrentHealth() const;
    int getMaxHealth() const;
    int getHealthRegen() const;
    int getCurrentMana() const;
    int getMaxMana() const;
    int getManaRegen() const;
    int getAttackDamage() const;
    int getDefense() const;
    const vector<int> &getStats() const; 
    int getStat(int idStat) const;       
    bool getStunned() const;
    Skill *getSkill(const string &skillName) const;
    vector<Skill *> getAllSkill();
    virtual string getAssets() const;
    string getRank();
    int getLevel();
    vector<Effect *> getActiveEffects();

    
    void setName(const string &name);
    void setStat(int idStat, int value);
    void setCurrentHealth(int health);
    void setMaxHealth(int health);
    void setCurrentMana(int mana);
    void setMaxMana(int mana);
    void setAttackDamage(int damage);
    void setDefense(int defense);
    void setHealthRegen(int regen);
    void setManaRegen(int regen);
    void setStunned(bool stunned);
    void setLevel(int level);

    
    virtual int attack(Unit *target);
    virtual int takeDamage(int damage);
    virtual int heal(int amount);
    virtual int restoreMana(int amount);
    virtual bool useSkill(Skill *skill, Unit *target);
    bool hasSkill(Skill *skill) const;
    virtual void addSkill(Skill *skill);
    virtual void removeSkill(Skill *skill);
    virtual void addEffect(Effect *effect);
    virtual void removeEffect(Effect *effect);
    virtual void reset();

    
    void updateEffects();
    
    void tick();

    
    void setAssets(string path);

    void scaleStats(double k);

    vector<string> getLog();
    void resetLog();
};

#endif