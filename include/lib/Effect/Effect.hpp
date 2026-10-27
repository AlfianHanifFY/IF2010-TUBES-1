#ifndef EFFECT_HPP
#define EFFECT_HPP

#include <iostream>
using namespace std;

class Unit;

class Effect
{
protected:
    string name;
    string description;
    int duration;
    int remainingDuration;
    float effectChance;

public:
    Effect(string name, string description, int duration, float effectChance);
    virtual ~Effect();

    Effect(const Effect &other);
    
    string getName() const;
    string getDescription() const;
    int getDuration() const;
    int getRemainingDuration() const;
    float getEffectChance() const;

    
    void setRemainingDuration(int duration);
    void setEffectChance(float effectChance);
    void setPermanent();

    
    virtual void apply(Unit *target) = 0;
    virtual void remove(Unit *target) = 0;
    virtual void tick(Unit *target);
    bool isExpired() const;
    void reduceDuration();
    void reset();

    virtual Effect *clone() const = 0;

    
    bool operator==(const Effect &other) const;
};

#endif