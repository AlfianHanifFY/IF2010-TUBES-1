#include "Unit/Mob/BossMob/BossMob.hpp"






BossMob::BossMob(string name, int level) : Mob(name, level)
{
    this->rageActivated = false;
    this->rageMultiplier = 1.5;

    this->maxHealth = 100 + level * 15;
    this->maxMana = 50 + level * 8;
    this->attackDamage = 10 + level * 3;

    
    setStat(0, 10 + level * 1.5);
    setStat(1, 10 + level * 1.5);
    setStat(2, 10 + level * 1.5);

    
    
    Skill *rageSkill = new Skill("Rage", 20, 0, 0);
    rageSkill->addEffect(new RageEffect("Rage Effect", "Meningkatkan seluruh stat dari Mob menjadi 1.5x lipat", -1, 1.0f, 1.5f));
    addSkill(rageSkill);
}

BossMob::~BossMob() {}

bool BossMob::isRageActivated() const
{
    return rageActivated;
}

void BossMob::activateRage()
{
    if (!rageActivated)
    {

        for (size_t i = 0; i < skills.size(); ++i)
        {
            if (skills[i]->getName() == "Rage")
            {
                useSkill(skills[i], this);
                return;
            }
        }

        rageActivated = true;
        cout << name << " becomes enraged! Its power increases!" << std::endl;
    }
}

void BossMob::act(Unit *target)
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

    attack(target);
}

string BossMob::getType()
{
    return "Boss";
}