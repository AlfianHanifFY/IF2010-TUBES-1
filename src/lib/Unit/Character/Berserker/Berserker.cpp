#include "Unit/Character/Berserker/Berserker.hpp"

Berserker::Berserker(string name) : Character(name, 90, 6, 20, 1, 95, 1, 0, 0, 0)
{
    setStat(0, 95); 
    setStat(1, 20); 
    setStat(2, 70); 

    this->rageMultiplier = 1.0;
    setDefense(0.5 * getStat(0) + 5 * level);
    initPath();
    setAssets("./Assets/Unit/Character/Berseker");
}

Berserker::~Berserker() {}


float Berserker::getRageMultiplier() const
{
    return this->rageMultiplier;
}

string Berserker::getCharType() const
{
    return "Berserker";
}


void Berserker::setRageMultiplier(float rageMultiplier)
{
    this->rageMultiplier = rageMultiplier;
}


int Berserker::attack(Unit *target)
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

    int damage = (attackDamage + weaponDamage) * LevelFactor * 1 * rageMultiplier;

    int finalDamage = damage - defense;

    if (finalDamage < 0)
    {
        finalDamage = 0;
        log.push_back(target->getName() + " fully blocked " + getName() + " attack.");
    }

    log.push_back(getName() + " attacks " + target->getName() + " for " + to_string(finalDamage) + " damage.");

    rageMultiplier += 0.001;
    log.push_back(getName() + "'s rage increases! (Rage: " + to_string(rageMultiplier) + ")");

    return target->takeDamage(finalDamage);
}

bool Berserker::useSkill(Skill *skill, Unit *target)
{
    if (!skill || !target)
    {
        return false;
    }

    if (Unit::useSkill(skill, target))
    {
        rageMultiplier += 0.001;
        log.push_back(getName() + "'s rage increases! (Rage: " + to_string(rageMultiplier) + ")");
        return true;
    }

    return false;
}

void Berserker::levelUp()
{
    setStat(0, getStat(0) + 3);
    setStat(1, getStat(1) + 1);
    setStat(2, getStat(2) + 1);

    this->level += 1;
    int curr = getMaxHealth();
    setMaxHealth(curr + level * 100);
    int currMana = getMaxMana();
    setMaxMana(currMana + level * 50);
    setDefense(0.5 * getStat(0) + 5 * level);
    setAttackDamage(getAttackDamage() + (10 * level));
    log.push_back(getName() + " leveled up to level " + to_string(getLevel()) + "!");
}

void Berserker::reset()
{
    rageMultiplier = 1.0;

    Character::reset();

    log.push_back(getName() + " reset!" + "rageMultiplier: " + to_string(rageMultiplier));
}

void Berserker::initPath()
{
    Skill *rageBoost = new Skill("Rage Boost", 5, 2, 18);
    rageBoost->addEffect(new RageEffect("Anger Surge", "Increases rage level", 2, 1, 1.2f));

    Skill *bloodFrenzy = new Skill("Blood Frenzy", 8, 3, 35);
    bloodFrenzy->addEffect(new RageEffect("Anger Surge", "Increases rage level", 2, 1, 1.2f));
    bloodFrenzy->addEffect(new CriticalDamageEffect("Blood Strike", "High crit chance", 3, 1, 1.5f));

    Skill *berserkSmash = new Skill("Berserk Smash", 12, 5, 55);
    berserkSmash->addEffect(new RageEffect("Anger Surge", "Increases rage level", 2, 1, 1.2f));
    berserkSmash->addEffect(new CriticalDamageEffect("Blood Strike", "High crit chance", 3, 1, 1.5f));
    berserkSmash->addEffect(new CriticalDamageEffect("Brutal Hit", "High crit chance", 3, 1, 1.5f));

    Skill *roarOfFury = new Skill("Roar of Fury", 7, 3, 28);
    roarOfFury->addEffect(new RageEffect("Anger Surge", "Increases rage level", 2, 1, 1.2f));
    roarOfFury->addEffect(new StatReductionEffect("Intimidate", "Reduces enemy stats", 2, 1, 0.3f, 1));

    Skill *endlessCarnage = new Skill("Endless Carnage", 15, 6, 65);
    endlessCarnage->addEffect(new RageEffect("Anger Surge", "Increases rage level", 2, 1, 1.2f));
    endlessCarnage->addEffect(new StatReductionEffect("Intimidate", "Reduces enemy stats", 2, 1, 0.3f, 1));
    endlessCarnage->addEffect(new BurnEffect("Flaming Rage", "Burns enemy", 2, 1, 12));
    endlessCarnage->addEffect(new ManaDrainEffect("Mana Drain", "Reduces enemy mana", 2, 1, 10));

    getSkillTree()->addSkill(rageBoost, "Base");
    getSkillTree()->addSkill(bloodFrenzy, "A1");
    getSkillTree()->addSkill(berserkSmash, "A2");
    getSkillTree()->addSkill(roarOfFury, "B1");
    getSkillTree()->addSkill(endlessCarnage, "B2");
}
