#include "Unit/Mob/BossMob/Lich/Lich.hpp"

Lich::Lich(int level) : BossMob("Lich", level)
{
    
    
    Skill *witheringTouchSkill = new Skill("Withering Touch", 30, 0, getStat(1));
    witheringTouchSkill->addEffect(new BurnEffect("Withering Touch Effect", "Menyebabkan damage over time (kerusakan berkelanjutan) selama 4 turn", 4, 1.0f, getStat(1)));
    witheringTouchSkill->addEffect(new ManaDrainEffect("Mana Drain Effect", "Mengurangi mana pemain.", 4, 1.0f, 5));
    addSkill(witheringTouchSkill);
    setAssets("./Assets/Unit/Mob/Boss/Lich");
}

Lich::~Lich() {}

void Lich::act(Unit *target)
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
    if (chance <= 0.2)
    {
        useSkill(getSkill("Withering Touch"), target);
        return;
    }

    attack(target);
}