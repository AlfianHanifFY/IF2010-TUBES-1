#include "Effect/SkillEffect/BurnEffect/BurnEffect.hpp"

BurnEffect::BurnEffect(string name, string description, int duration, float effectChance, int damagePerTurn) : SkillEffect(name, description, duration, effectChance) {
    this->damagePerTurn = damagePerTurn;
}

BurnEffect::~BurnEffect() {}


int BurnEffect::getDamagePerTurn() const {
    return damagePerTurn;
}

void BurnEffect::apply(Unit *target) {
    cout << getName() << " applies " << getName() << " to " << target->getName() << "!" << endl;
}

void BurnEffect::tick(Unit *target) {
    cout << target->getName() << " takes " << damagePerTurn << " damage from " << getName() << "!" << endl;
    target->takeDamage(damagePerTurn);
    Effect::tick(target);
}

void BurnEffect::remove(Unit* target){
    cout << "Burn effect on " << target->getName() << " has worn off." << endl;
}

BurnEffect::BurnEffect(const BurnEffect& other) : SkillEffect(other) {
    this->damagePerTurn = other.damagePerTurn;
}

Effect* BurnEffect::clone() const {
    return new BurnEffect(*this);
}