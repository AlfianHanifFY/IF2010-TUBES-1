#include "Effect/SkillEffect/StatReductionEffect/StatReductionEffect.hpp"

StatReductionEffect::StatReductionEffect(string name, string description, int duration, float effectChance, float attackReductionMultiplier, float defenseReductionMultiplier) : SkillEffect(name, description, duration, effectChance) {
    this->attackReductionMultiplier = attackReductionMultiplier;
    this->defenseReductionMultiplier = defenseReductionMultiplier;
    this->baseAttack = 0;
    this->baseDefense = 0;
}

StatReductionEffect::~StatReductionEffect() {}


float StatReductionEffect::getAttackReductionMultiplier() const {
    return attackReductionMultiplier;
}

float StatReductionEffect::getDefenseReductionMultiplier() const {
    return defenseReductionMultiplier;
}

void StatReductionEffect::apply(Unit *target) {
    baseAttack = target->getAttackDamage();
    baseDefense = target->getDefense();
    
    int newAttack = static_cast<int>(baseAttack * (1-attackReductionMultiplier));
    int newDefense = static_cast<int>(baseDefense * (1-defenseReductionMultiplier));
    
    target->setAttackDamage(newAttack);
    target->setDefense(newDefense);
    
    cout << target->getName() << " is cursed by " << getName() << "!" << endl;
    cout << "Attack reduced from " << baseAttack << " to " << newAttack << "!" << endl;
    cout << "Defense reduced from " << baseDefense << " to " << newDefense << "!" << endl;
}

void StatReductionEffect::tick(Unit *target) {
    cout << target->getName() << " is weakened by " << getName() << "!" << endl;
    Effect::tick(target);
}

void StatReductionEffect::remove(Unit* target) {
    target->setAttackDamage(baseAttack);
    target->setDefense(baseDefense);
    cout << target->getName() << " is no longer cursed. Stats returned to normal." << endl;
}


StatReductionEffect::StatReductionEffect(const StatReductionEffect& other) : SkillEffect(other) {
    attackReductionMultiplier = other.attackReductionMultiplier;
    defenseReductionMultiplier = other.defenseReductionMultiplier;
    baseAttack = other.baseAttack;
    baseDefense = other.baseDefense;
}

Effect* StatReductionEffect::clone() const {
    return new StatReductionEffect(*this);
}