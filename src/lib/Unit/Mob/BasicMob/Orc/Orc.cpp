#include "Unit/Mob/BasicMob/Orc/Orc.hpp"

Orc::Orc(int level) : BasicMob("Orc", level)
{
    
    

    Skill *brutalStrikeSkill = new Skill("Brutal Strike", 30, 0, 1.5 * attackDamage);
    brutalStrikeSkill->addEffect(new StunEffect("Stun Effect 0.5", "Stuns the target for 1 turn with 0.5 chance", 1, 0.5f));
    addSkill(brutalStrikeSkill);

    setAssets("./Assets/Unit/Mob/Basic/Orc");
}

Orc::~Orc() {}

void Orc::act(Unit *target)
{
    if (!target)
        return;

    
    float chance = static_cast<float>(rand()) / RAND_MAX;
    if (currentHealth < maxHealth * 0.5 && chance <= 0.05)
    {
        useSkill(getSkill("Heal"), this);
        return;
    }

    
    chance = static_cast<float>(rand()) / RAND_MAX;
    if (chance <= 0.15)
    {
        useSkill(getSkill("Brutal Strike"), target);
        return;
    }

    attack(target);
}