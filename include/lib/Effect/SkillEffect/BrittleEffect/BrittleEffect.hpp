#ifndef BRTITTELEFFECT_HPP
#define BRTITTELEFFECT_HPP

#include <iostream>
using namespace std;

#include "../SkillEffect.hpp"
#include "Unit/Unit.hpp"

class BrittleEffect : public SkillEffect {
    float defenseReductionMultiplier;
    int baseDefense;
    
public:
    BrittleEffect(string name, string description, int duration, float effectChance, float defenseReductionMultiplier);
    ~BrittleEffect();

    
    float getDefenseReductionMultiplier() const;

    
    void setDefenseReductionMultiplier(float defenseReductionMultiplier);

    
    virtual void apply(Unit *target) override;
    virtual void remove(Unit *target) override;

    
    BrittleEffect(const BrittleEffect &other);

    virtual Effect *clone() const override;
};

#endif

