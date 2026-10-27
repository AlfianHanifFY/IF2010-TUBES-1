#include "Unit/Character/Mage/Mage.hpp"

Mage::Mage(string name) : Character(name, 50, 2, 80, 8, 30, 1, 0, 0, 0)
{
    setStat(0, 30); 
    setStat(1, 95); 
    setStat(2, 40); 

    this->extraMana = 10;
    setDefense(0.5 * getStat(0) + 5 * level);
    initPath();
    setAssets("./Assets/Unit/Character/Mage");
}

Mage::~Mage() {}


int Mage::getExtraMana() const
{
    return this->extraMana;
}

string Mage::getCharType() const
{
    return "Mage";
}


void Mage::setExtraMana(int extraMana)
{
    this->extraMana = extraMana;
}


int Mage::attack(Unit *target)
{
    restoreMana(extraMana);

    return Character::attack(target);
}

bool Mage::useSkill(Skill *skill, Unit *target)
{
    if (!skill || !target)
    {
        return false;
    }

    if (Unit::useSkill(skill, target))
    {
        skill->setManaCost(skill->getManaCost() - 5);

        
        int magicDamage = getStat(1) / 2;
        skill->setDamage(skill->getDamage() + magicDamage);

        return true;
    }

    return false;
}

void Mage::levelUp()
{
    setStat(0, getStat(0) + 1);
    setStat(1, getStat(1) + 3);
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

void Mage::initPath()
{
    Skill *arcaneBolt = new Skill("Arcane Bolt", 4, 2, 18);
    arcaneBolt->addEffect(new BurnEffect("Mana Spark", "Burns with arcane fire", 2, 1, 8));

    Skill *manaShield = new Skill("Mana Shield", 6, 3, 25);
    manaShield->addEffect(new BurnEffect("Mana Spark", "Burns with arcane fire", 2, 1, 8));
    manaShield->addEffect(new HealEffect("Arcane Fortitude", "Heals over time", 2, 1, 6));

    Skill *elementalStorm = new Skill("Elemental Storm", 11, 5, 50);
    elementalStorm->addEffect(new BurnEffect("Mana Spark", "Burns with arcane fire", 2, 1, 8));
    elementalStorm->addEffect(new StunEffect("Lightning Shock", "Chance to stun", 1, 0.25f));
    elementalStorm->addEffect(new BurnEffect("Fire Whirl", "Burns enemies", 2, 1, 10));
    elementalStorm->addEffect(new HealEffect("Arcane Fortitude", "Heals over time", 2, 1, 6));

    Skill *timeWarp = new Skill("Time Warp", 7, 4, 30);
    timeWarp->addEffect(new BurnEffect("Mana Spark", "Burns with arcane fire", 2, 1, 8));
    timeWarp->addEffect(new SlowEffect("Time Dilation", "Slows down enemy", 2, 1, 20));

    Skill *meteorFall = new Skill("Meteor Fall", 15, 6, 70);
    meteorFall->addEffect(new BurnEffect("Mana Spark", "Burns with arcane fire", 2, 1, 8));
    meteorFall->addEffect(new BurnEffect("Meteor Burn", "Burns target area", 3, 1, 15));
    meteorFall->addEffect(new SlowEffect("Time Dilation", "Slows down enemy", 2, 1, 20));

    getSkillTree()->addSkill(arcaneBolt, "Base");
    getSkillTree()->addSkill(manaShield, "A1");
    getSkillTree()->addSkill(elementalStorm, "A2");
    getSkillTree()->addSkill(timeWarp, "B1");
    getSkillTree()->addSkill(meteorFall, "B2");
}