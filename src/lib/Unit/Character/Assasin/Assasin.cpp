#include "Unit/Character/Assasin/Assasin.hpp"
#include <cstdlib> 
#include <ctime>   

Assasin::Assasin(string name) : Character(name, 60, 3, 40, 4, 85, 1, 0, 0, 0)
{
    setStat(0, 50); 
    setStat(1, 45); 
    setStat(2, 90); 

    this->criticalChance = 0.3;
    this->criticalMultiplier = 2.0;
    setDefense(0.5 * getStat(0) + 5 * level);
    initPath();
    setAssets("./Assets/Unit/Character/Assasin");
}

Assasin::~Assasin() {}


float Assasin::getCriticalChance() const
{
    return this->criticalChance;
}

float Assasin::getCriticalMultiplier() const
{
    return this->criticalMultiplier;
}

string Assasin::getCharType() const
{
    return "Assasin";
}


void Assasin::setCriticalChance(float criticalChance)
{
    this->criticalChance = criticalChance;
}

void Assasin::setCriticalMultiplier(float criticalMultiplier)
{
    this->criticalMultiplier = criticalMultiplier;
}


int Assasin::attack(Unit *target)
{
    if (!target)
    {
        return 0;
    }

    
    int weaponDamage = 0;
    if (weapon)
    {
        Weapon *w = dynamic_cast<Weapon *>(weapon);
        if (w)
        {
            weaponDamage += w->getDamage(target);
        }
        vector<Effect *> effects = w->getEffects();
        for (auto i = effects.begin(); i != effects.end(); i++)
        {
            float chance = static_cast<float>(rand()) / RAND_MAX;
            if (chance <= (*i)->getEffectChance())
            {
                HealthDrainEffect *drainEffect = dynamic_cast<HealthDrainEffect *>((*i)->clone());
                if (drainEffect != nullptr)
                {
                    drainEffect->setDrainAmount(100 * 0.3);
                    target->addEffect(drainEffect);
                }
                else
                {
                    target->addEffect((*i)->clone());
                }
            }
        }
    }

    
    float LevelFactor = 1 + (getLevel() - target->getLevel()) * 0.05;

    int damage = (attackDamage + weaponDamage) * LevelFactor * 1;

    float chance = static_cast<float>(rand()) / RAND_MAX;
    if (chance <= criticalChance)
    {
        damage *= criticalMultiplier;
        log.push_back("Critical hit!");
    }

    int finalDamage = damage - defense;

    if (finalDamage < 0)
    {
        finalDamage = 0;
        log.push_back(target->getName() + " fully blocked " + getName() + " attack.");
    }

    log.push_back(getName() + " attacks " + target->getName() + " for " + to_string(finalDamage) + " damage.");

    return target->takeDamage(finalDamage);
}

int Assasin::takeDamage(int damage)
{
    
    float missChance = getStat(2) * 0.005;

    if (missChance > 0.5)
    {
        missChance = 0.5;
    }

    float chance = static_cast<float>(rand()) / RAND_MAX;
    if (chance <= missChance)
    {
        log.push_back(getName() + " dodges the attack.");
        return 0;
    }

    return Character::takeDamage(damage);
}

void Assasin::levelUp()
{
    setStat(0, getStat(0) + 1);
    setStat(1, getStat(1) + 1);
    setStat(2, getStat(2) + 3);

    this->level += 1;
    int curr = getMaxHealth();
    setMaxHealth(curr + level * 100);
    int currMana = getMaxMana();
    setMaxMana(currMana + level * 50);
    setDefense(0.5 * getStat(0) + 5 * level);
    setAttackDamage(getAttackDamage() + (10 * level));
    cout << getName() << " leveled up to level " << getLevel() << "!" << endl; 
}

void Assasin::initPath()
{
    Skill *quickStab = new Skill("Quick Stab", 5, 2, 20);
    quickStab->addEffect(new CriticalDamageEffect("Vital Strike", "High crit chance", 1, 1, 1.4f));

    Skill *shadowStep = new Skill("Shadow Step", 8, 3, 30);
    shadowStep->addEffect(new CriticalDamageEffect("Vital Strike", "High crit chance", 1, 1, 1.4f));
    shadowStep->addEffect(new SlowEffect("Shadow Bind", "Reduces movement", 2, 1, 15));

    Skill *deadlyPrecision = new Skill("Deadly Precision", 13, 5, 55);
    deadlyPrecision->addEffect(new CriticalDamageEffect("Vital Strike", "High crit chance", 1, 1, 1.4f));
    deadlyPrecision->addEffect(new CriticalDamageEffect("Critical Focus", "Boosts crit damage", 2, 1, 1.6f));
    deadlyPrecision->addEffect(new SlowEffect("Shadow Bind", "Reduces movement", 2, 1, 15));

    Skill *smokeBomb = new Skill("Smoke Bomb", 6, 3, 25);
    smokeBomb->addEffect(new CriticalDamageEffect("Vital Strike", "High crit chance", 1, 1, 1.4f));
    smokeBomb->addEffect(new StatReductionEffect("Blind Effect", "Reduces accuracy", 2, 1, 0.4f, 1));

    Skill *silentExecution = new Skill("Silent Execution", 14, 6, 60);
    silentExecution->addEffect(new CriticalDamageEffect("Vital Strike", "High crit chance", 1, 1, 1.4f));
    silentExecution->addEffect(new StatReductionEffect("Blind Effect", "Reduces accuracy", 2, 1, 0.4f, 1));
    silentExecution->addEffect(new CriticalDamageEffect("Critical Execution", "Boosts crit damage", 2, 1, 1.6f));

    getSkillTree()->addSkill(quickStab, "Base");
    getSkillTree()->addSkill(shadowStep, "A1");
    getSkillTree()->addSkill(deadlyPrecision, "A2");
    getSkillTree()->addSkill(smokeBomb, "B1");
    getSkillTree()->addSkill(silentExecution, "B2");
}
