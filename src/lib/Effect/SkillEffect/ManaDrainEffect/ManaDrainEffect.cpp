#include "Effect/SkillEffect/ManaDrainEffect/ManaDrainEffect.hpp"

ManaDrainEffect::ManaDrainEffect(string name, string description, int duration, float effectChance, int manaLossPerTurn) 
    : SkillEffect(name, description, duration, effectChance) {
    this->manaLossPerTurn = manaLossPerTurn;
}

ManaDrainEffect::~ManaDrainEffect() {}


int ManaDrainEffect::getManaLossPerTurn() const {
    return manaLossPerTurn;
}

void ManaDrainEffect::apply(Unit *target) {
    cout << target->getName() << " is affected by " << getName() << " and is losing mana!" << endl;
}

void ManaDrainEffect::tick(Unit *target) {
    cout << target->getName() << " loses " << manaLossPerTurn << " mana from " << getName() << "!" << endl;
    target->setCurrentMana(target->getCurrentMana() - manaLossPerTurn);
    Effect::tick(target);
}

void ManaDrainEffect::remove(Unit* target) {
    cout << getName() << " on " << target->getName() << " has worn off." << endl;
}


ManaDrainEffect::ManaDrainEffect(const ManaDrainEffect& other) : SkillEffect(other) {
    this->manaLossPerTurn = other.manaLossPerTurn;
}

Effect* ManaDrainEffect::clone() const {
    return new ManaDrainEffect(*this);
}