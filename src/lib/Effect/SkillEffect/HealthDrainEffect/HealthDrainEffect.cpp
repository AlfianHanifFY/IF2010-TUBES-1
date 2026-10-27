#include "Effect/SkillEffect/HealthDrainEffect/HealthDrainEffect.hpp"
#include <cstdlib>  
#include <ctime>    

HealthDrainEffect::HealthDrainEffect(string name, string description, int duration, float effectChance, int drainAmount, Unit* source) 
    : SkillEffect(name, description, duration, effectChance) {
    this->drainAmount = drainAmount;
    this->source = source;
}

HealthDrainEffect::~HealthDrainEffect() {
}


int HealthDrainEffect::getDrainAmount() const {
    return drainAmount;
}

Unit* HealthDrainEffect::getSource() const {
    return source;
}


void HealthDrainEffect::setDrainAmount(int amount) {
    this->drainAmount = amount;
}

void HealthDrainEffect::setSource(Unit* source) {
    this->source = source;
}

void HealthDrainEffect::apply(Unit *target) {
    cout << target->getName() << " is marked by " << getName() << "!" << endl;
}

void HealthDrainEffect::tick(Unit *target) {
    float chance = static_cast<float>(rand()) / RAND_MAX;
    if (chance <= getEffectChance()) {
        cout << target->getName() << " loses " << drainAmount << " HP from " << getName() << "!" << endl;
        cout << source->getName() << " drains " << drainAmount << " HP!" << endl;
        
        target->takeDamage(drainAmount);
        source->heal(drainAmount);
    } else {
        cout << getName() << " failed to drain health from " << target->getName() << "." << endl;
    }

    Effect::tick(target);
}

void HealthDrainEffect::remove(Unit* target) {
    cout << getName() << " on " << target->getName() << " has faded." << endl;
}


HealthDrainEffect::HealthDrainEffect(const HealthDrainEffect& other) : SkillEffect(other) {
    this->drainAmount = other.drainAmount;
    this->source = other.source;
}

Effect* HealthDrainEffect::clone() const {
    return new HealthDrainEffect(*this);
}