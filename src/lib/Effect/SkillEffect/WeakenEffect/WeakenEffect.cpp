#include "Effect/SkillEffect/WeakenEffect/WeakenEffect.hpp"

WeakenEffect::WeakenEffect(string name, string description, int duration, float effectChance, int attackDamageReduction) : SkillEffect(name, description, duration, effectChance) {
    this->attackDamageReduction = attackDamageReduction;
}

WeakenEffect::~WeakenEffect() {}

void WeakenEffect::apply(Unit *target) {
    cout << target->getName() << " is weakened! Attack reduced by " << attackDamageReduction << "." << endl;
    target->setAttackDamage(target->getAttackDamage() - attackDamageReduction);
}

void WeakenEffect::remove(Unit *target) {
    target->setAttackDamage(target->getAttackDamage() + attackDamageReduction);
    cout << "Weaken effect on " << target->getName() << " has worn off." << endl;
}



WeakenEffect::WeakenEffect(const WeakenEffect& other) : SkillEffect(other) {
    this->attackDamageReduction = other.attackDamageReduction;
}

Effect* WeakenEffect::clone() const {
    return new WeakenEffect(*this);
}