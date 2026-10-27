#include "Unit/Mob/BossMob/DarkKnight/DarkKnight.hpp"

DarkKnight::DarkKnight(int level) : BossMob("Dark Knight", level)
{
    
    
    Skill *soulSiphonSkill = new Skill("Soul Siphon", 30, 0, 1.5 * getStat(1));
    soulSiphonSkill->addEffect(new HealthDrainEffect("Health Drain Effect", "Mengurangi health pemain.", 1, 0.8f, 0, this));
    addSkill(soulSiphonSkill);
    setAssets("./Assets/Unit/Mob/Boss/DarkKnight");
}

DarkKnight::~DarkKnight() {}

void DarkKnight::act(Unit *target)
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
    if (chance <= 0.35)
    {
        useSkill(getSkill("Soul Siphon"), target);
        return;
    }

    attack(target);
}