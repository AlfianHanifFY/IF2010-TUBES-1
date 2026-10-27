#include "Unit/Mob/BossMob/DemonLord/DemonLord.hpp"

DemonLord::DemonLord(int level) : BossMob("Demon Lord", level)
{
    
    

    
    
    Skill *infernalCurseSkill = new Skill("Infernal Curse", 30, 0, 0);
    infernalCurseSkill->addEffect(new StatReductionEffect("Stat Reduction Effect", "Mengurangi attack power dan defense power pemain untuk durasi yang cukup lama (5 turn)", 5, 1.0f, 0.5f, 0.6f));
    addSkill(infernalCurseSkill);
    setAssets("./Assets/Unit/Mob/Boss/DemonLord");
}

DemonLord::~DemonLord() {}

void DemonLord::act(Unit *target)
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
    if (chance <= 0.15)
    {
        useSkill(getSkill("Infernal Curse"), target);
        return;
    }

    attack(target);
}