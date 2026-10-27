#include "Unit/Character/Fighter/Fighter.hpp"

Fighter::Fighter(string name) : Character(name, 85, 5, 50, 3, 70, 1, 0, 0, 0)
{
    setStat(0, 80); 
    setStat(1, 35); 
    setStat(2, 80); 

    this->blockChance = 0.2;
    setDefense(0.5 * getStat(0) + 5 * level);
    initPath();
    setAssets("./Assets/Unit/Character/Fighter");
}

Fighter::~Fighter() {}


float Fighter::getBlockChance() const
{
    return blockChance;
}

string Fighter::getCharType() const
{
    return "Fighter";
}


void Fighter::setBlockChance(float blockChance)
{
    this->blockChance = blockChance;
}


int Fighter::takeDamage(int damage)
{
    float chance = static_cast<float>(rand()) / RAND_MAX;
    if (chance <= blockChance)
    {
        log.push_back(getName() + " blocks the attack.");
        return 0;
    }

    
    return Character::takeDamage(damage);
}

bool Fighter::useSkill(Skill *skill, Unit *target)
{
    if (!skill || !target)
    {
        return false;
    }

    if (Unit::useSkill(skill, target))
    {
        int healAmount = getStat(0) / 2;
        int actualHeal = heal(healAmount);

        log.push_back(getName() + " regains " + to_string(actualHeal) + " health from inner strength!");
        return true;
    }

    return false;
}

void Fighter::levelUp()
{

    this->level += 1;
    setStat(0, getStat(0) + 3);
    setStat(1, getStat(1) + 1);
    setStat(2, getStat(2) + 1);
    int curr = getMaxHealth();
    setMaxHealth(curr + level * 100);
    int currMana = getMaxMana();
    setMaxMana(currMana + level * 50);
    setDefense(0.5 * getStat(0) + 5 * level);
    setAttackDamage(getAttackDamage() + (10 * level));
    log.push_back(getName() + " leveled up to level " + to_string(getLevel()) + "!");
}

void Fighter::initPath()
{
    Skill *shieldBash = new Skill("Shield Bash", 5, 2, 20);
    shieldBash->addEffect(new StunEffect("Shield Stun", "Stuns enemy for 1 turn", 1, 1));

    Skill *counterStance = new Skill("Counter Stance", 7, 3, 30);
    counterStance->addEffect(new StunEffect("Shield Stun", "Stuns enemy for 1 turn", 1, 1));
    counterStance->addEffect(new BurnEffect("Counter Burn", "Burns attacker when hit", 2, 1, 5));

    Skill *ironWill = new Skill("Iron Will", 10, 4, 45);
    ironWill->addEffect(new BurnEffect("Counter Burn", "Burns attacker when hit", 2, 1, 5));
    ironWill->addEffect(new StunEffect("Shield Stun", "Stuns enemy for 1 turn", 1, 1));
    ironWill->addEffect(new HealEffect("Second Wind", "Regenerates HP over time", 2, 1, 5));

    Skill *charge = new Skill("Charge", 6, 3, 25);
    charge->addEffect(new StunEffect("Shield Stun", "Stuns enemy for 1 turn", 1, 1));
    charge->addEffect(new StunEffect("Impact Stun", "Chance to stun", 1, 0.25f));

    Skill *whirlwindSlam = new Skill("Whirlwind Slam", 12, 5, 50);
    whirlwindSlam->addEffect(new StunEffect("Impact Stun", "Chance to stun", 1, 0.25f));
    whirlwindSlam->addEffect(new StunEffect("Shield Stun", "Stuns enemy for 1 turn", 1, 1));
    whirlwindSlam->addEffect(new BurnEffect("Burning Spin", "Burns the enemy each turn", 3, 1, 10));
    whirlwindSlam->addEffect(new SlowEffect("Dizzying Blow", "Reduces enemy speed", 2, 1, 15));

    getSkillTree()->addSkill(shieldBash, "Base");
    getSkillTree()->addSkill(counterStance, "A1");
    getSkillTree()->addSkill(ironWill, "A2");
    getSkillTree()->addSkill(charge, "B1");
    getSkillTree()->addSkill(whirlwindSlam, "B2");
}