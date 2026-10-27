#include "Unit/Mob/BasicMob/Slime/Slime.hpp"

Slime::Slime(int level) : BasicMob("Slime", level)
{
    
    

    Skill *acidicCorrosionSkill = new Skill("Acidic Corrosion", 30, 0, getStat(1) * 2);
    acidicCorrosionSkill->addEffect(new BurnEffect("Acidic Corrosion Effect", "Menyebabkan damage over time (kerusakan berkelanjutan) selama 3 turn", 3, 1.0f, getStat(1) * 2));
    addSkill(acidicCorrosionSkill);

    setAssets("./Assets/Unit/Mob/Basic/Slime");
}

Slime::~Slime() {}

void Slime::act(Unit *target)
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
    if (chance <= 0.2)
    {
        useSkill(getSkill("Acidic Corrosion"), target);
        return;
    }

    attack(target);
}