#include "Effect/SkillEffect/BrittleEffect/BrittleEffect.hpp"

BrittleEffect::BrittleEffect(string name, string description, int duration, float effectChance, float defenseReductionMultiplier) : SkillEffect(name, description, duration, effectChance){
    this->defenseReductionMultiplier = defenseReductionMultiplier;
} 

BrittleEffect::~BrittleEffect() {}


float BrittleEffect::getDefenseReductionMultiplier() const {
    return this->defenseReductionMultiplier;
}


void BrittleEffect::setDefenseReductionMultiplier(float defenseReductionMultiplier) {
    this->defenseReductionMultiplier = defenseReductionMultiplier;
}


BrittleEffect::BrittleEffect(const BrittleEffect& other) : SkillEffect(other) {
    this->defenseReductionMultiplier = other.defenseReductionMultiplier;
}

Effect* BrittleEffect::clone() const {
    return new BrittleEffect(*this);
}



void BrittleEffect::apply(Unit *target) {
    baseDefense = target->getDefense();
    target->setDefense(static_cast<int>(baseDefense * (1-defenseReductionMultiplier)));
    cout << target->getName() << " is now brittle!" << endl;
}

void BrittleEffect::remove(Unit *target) {
    target->setDefense(baseDefense);
    cout << target->getName() << " is no longer brittle!" << endl;
}