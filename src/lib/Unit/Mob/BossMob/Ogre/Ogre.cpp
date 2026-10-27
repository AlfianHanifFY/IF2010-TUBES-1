#include "Unit/Mob/BossMob/Ogre/Ogre.hpp"

Ogre::Ogre(int level) : BossMob("Ogre", level)
{

    Skill *pulverizeSkill = new Skill("Pulverize", 30, 0, 2.5 * attackDamage);
    pulverizeSkill->addEffect(new StunEffect("Stun Effect 0.9", "Stuns the target for 1 turn with 0.9 chance", 1, 0.9f));
    addSkill(pulverizeSkill);

    setAssets("./Assets/Unit/Mob/Boss/Ogre");
}

Ogre::~Ogre() {}

void Ogre::act(Unit *target)
{
    if (!target)
        return;

    if (!rageActivated && currentHealth <= maxHealth * 0.2)
    {
        activateRage();
    }

    float chance = static_cast<float>(rand()) / RAND_MAX;
    if (currentHealth < maxHealth * 0.5 && chance <= 0.05)
    {
        useSkill(getSkill("Heal"), this);
        return;
    }

    chance = static_cast<float>(rand()) / RAND_MAX;
    if (chance <= 0.3)
    {
        useSkill(getSkill("Pulverize"), target);
        return;
    }

    attack(target);
}