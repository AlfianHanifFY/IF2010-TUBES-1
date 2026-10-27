#include "Unit/Character/Necromancer/Necromancer.hpp"

Necromancer::Necromancer(string name) : Character(name, 55, 3, 70, 6, 35, 1, 0, 0, 0)
{
    setStat(0, 40); 
    setStat(1, 90); 
    setStat(2, 45); 
    this->summon = 0;
    this->summonChance = 0.6;
    this->summonDamage = getStat(1) / 10;
    setDefense(0.5 * getStat(0) + 5 * level);
    initPath();
    setAssets("./Assets/Unit/Character/Necromancer");
}

Necromancer::~Necromancer() {}


int Necromancer::getSummon() const
{
    return this->summon;
}

float Necromancer::getSummonChance() const
{
    return this->summonChance;
}

int Necromancer::getSummonDamage() const
{
    return this->summonDamage;
}

string Necromancer::getCharType() const
{
    return "Necromancer";
}


void Necromancer::setSummonChance(float summonChance)
{
    this->summonChance = summonChance;
}

void Necromancer::setSummonDamage(int damage)
{
    this->summonDamage = damage;
}


int Necromancer::attack(Unit *target)
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

    if (summon < 8)
    {
        float chance = static_cast<float>(rand()) / RAND_MAX;
        if (chance <= summonChance)
        {
            summon++;
            log.push_back(getName() + " summons a new Undead Minion! (Total: " + to_string(summon) + ")");
        }
    }

    if (summon > 0)
    {
        int totalSummonDamage = 0;
        for (int i = 0; i < summon; i++)
        {
            int actualSummonDamage = target->takeDamage(summonDamage);
            totalSummonDamage += actualSummonDamage;
        }
        damage += totalSummonDamage;
        cout << summon << " Undead Minions attack " << target->getName() << " for a total of " << totalSummonDamage << " damage!" << endl;
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

bool Necromancer::useSkill(Skill *skill, Unit *target)
{
    if (!skill || !target)
    {
        return false;
    }

    if (Unit::useSkill(skill, target))
    {
        int lifestealAmount = getStat(1) / 10;
        int actualDamage = target->takeDamage(lifestealAmount);
        int heathAdded = heal(actualDamage);

        log.push_back(getName() + " steals " + to_string(actualDamage) + " health from " + target->getName() + " and regains " + to_string(heathAdded) + " health.");

        return true;
    }

    return false;
}

void Necromancer::levelUp()
{
    setStat(0, getStat(0) + 1);
    setStat(1, getStat(1) + 3);
    setStat(2, getStat(2) + 1);

    
    this->summonDamage = getStat(1) / 10;
    this->level += 1;
    int curr = getMaxHealth();
    setMaxHealth(curr + level * 100);
    int currMana = getMaxMana();
    setMaxMana(currMana + level * 50);
    setDefense(0.5 * getStat(0) + 5 * level);
    setAttackDamage(getAttackDamage() + (10 * level));
    log.push_back(getName() + " leveled up to level " + to_string(getLevel()) + "!");
}

void Necromancer::reset()
{
    summon = 0;
    Character::reset();

    log.push_back(getName() + " reset!" + "summon: " + to_string(summon));
}

void Necromancer::initPath()
{
    Skill *summonSkeleton = new Skill("Summon Skeleton", 6, 2, 22);
    summonSkeleton->addEffect(new HealEffect("Soul Bond", "Heals user slightly", 1, 1, 10));

    Skill *boneArmor = new Skill("Bone Armor", 8, 3, 30);
    boneArmor->addEffect(new HealEffect("Soul Bond", "Heals user slightly", 1, 1, 10));
    boneArmor->addEffect(new StatReductionEffect("Armor Thickening", "Reduces enemy attack", 2, 1, 0.5f, 1));

    Skill *soulExplosion = new Skill("Soul Explosion", 13, 5, 55);
    soulExplosion->addEffect(new HealEffect("Soul Bond", "Heals user slightly", 1, 1, 10));
    soulExplosion->addEffect(new DecayEffect("Soul Rot", "Decay over time", 3, 1, 12));
    soulExplosion->addEffect(new StatReductionEffect("Armor Thickening", "Reduces enemy attack", 2, 1, 0.5f, 1));

    Skill *darkPact = new Skill("Dark Pact", 9, 4, 35);
    darkPact->addEffect(new HealEffect("Soul Bond", "Heals user slightly", 1, 1, 10));
    darkPact->addEffect(new ManaDrainEffect("Forbidden Drain", "Drains mana", 2, 1, 20));

    Skill *armyOfDead = new Skill("Army of the Dead", 15, 6, 70);
    armyOfDead->addEffect(new HealEffect("Soul Bond", "Heals user slightly", 1, 1, 10));
    armyOfDead->addEffect(new StunEffect("Overwhelming Numbers", "Chance to stun", 1, 1));
    armyOfDead->addEffect(new ManaDrainEffect("Forbidden Drain", "Drains mana", 2, 1, 20));

    getSkillTree()->addSkill(summonSkeleton, "Base");
    getSkillTree()->addSkill(boneArmor, "A1");
    getSkillTree()->addSkill(soulExplosion, "A2");
    getSkillTree()->addSkill(darkPact, "B1");
    getSkillTree()->addSkill(armyOfDead, "B2");
}