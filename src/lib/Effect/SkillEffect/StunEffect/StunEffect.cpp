#include "Effect/SkillEffect/StunEffect/StunEffect.hpp"
#include <cstdlib>  
#include <ctime>    

StunEffect::StunEffect(string name, string description, int duration, float effectChance) : SkillEffect(name, description, duration, effectChance) {}

StunEffect::~StunEffect() {}

void StunEffect::apply(Unit *target) {
    float roll = static_cast<float>(rand()) / RAND_MAX; 

    if (roll <= getEffectChance()) {
        target->setStunned(true);
        cout << getName() << " applies " << getName() << " to " << target->getName() << "!" << endl;
    } else {
        cout << getName() << " failed to apply to " << target->getName() << "." << endl;
    }
}

void StunEffect::remove(Unit *target) {
    target->setStunned(false);
    cout << "Stun effect on " << target->getName() << " has worn off." << endl;
}

StunEffect::StunEffect(const StunEffect& other) : SkillEffect(other) {}

Effect* StunEffect::clone() const {
    return new StunEffect(*this);
}