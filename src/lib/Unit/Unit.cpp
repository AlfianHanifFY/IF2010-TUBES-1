#include "Unit/Unit.hpp"

Unit::Unit(string name, int maxHealth, int healthRegen, int maxMana, int manaRegen, int attackDamage)
{
    this->name = name;
    this->maxHealth = maxHealth;
    this->healthRegen = healthRegen;
    this->maxMana = maxMana;
    this->manaRegen = manaRegen;
    this->attackDamage = attackDamage;
    this->currentHealth = maxHealth;
    this->currentMana = maxMana;
    this->stats = {0, 0, 0};
    this->isStunned = false;
    
    this->defense = 0;
}

Unit::~Unit()
{
    for (size_t i = 0; i < skills.size(); i++)
    {
        delete skills[i];
    }
    skills.clear();

    for (size_t i = 0; i < activeEffects.size(); i++)
    {
        delete activeEffects[i];
    }
    activeEffects.clear();
}


string Unit::getName() const
{
    return this->name;
}

int Unit::getCurrentHealth() const
{
    return this->currentHealth;
}

int Unit::getMaxHealth() const
{
    return this->maxHealth;
}

int Unit::getHealthRegen() const
{
    return this->healthRegen;
}

int Unit::getCurrentMana() const
{
    return this->currentMana;
}

int Unit::getMaxMana() const
{
    return this->maxMana;
}

int Unit::getManaRegen() const
{
    return this->manaRegen;
}

int Unit::getAttackDamage() const
{
    return this->attackDamage;
}

int Unit::getDefense() const
{
    return this->defense;
}

const vector<int> &Unit::getStats() const
{
    return this->stats;
}

int Unit::getStat(int idStat) const
{
    if (idStat >= 0 && idStat <= 2)
    {
        return stats[idStat];
    }
    return -1;
}

bool Unit::getStunned() const
{
    return this->isStunned;
}

Skill *Unit::getSkill(const string &skillName) const
{
    for (size_t i = 0; i < skills.size(); i++)
    {
        if (skills[i]->getName() == skillName)
        {
            return skills[i];
        }
    }
    return nullptr;
}

vector<Skill *> Unit::getAllSkill()
{
    return this->skills;
}


void Unit::setName(const string &name)
{
    this->name = name;
}

void Unit::setStat(int idStat, int value)
{
    if (idStat >= 0 && idStat <= 2)
    {
        this->stats[idStat] = value;
    }
}

void Unit::setCurrentHealth(int health)
{
    if (health > this->maxHealth)
    {
        this->currentHealth = this->maxHealth;
    }
    else
    {
        this->currentHealth = health;
    }
}

void Unit::setMaxHealth(int health)
{
    this->maxHealth = health;
}

void Unit::setCurrentMana(int mana)
{
    if (mana > this->maxMana)
    {
        this->currentMana = this->maxMana;
    }
    else
    {
        this->currentMana = mana;
    }
}

void Unit::setMaxMana(int mana)
{
    this->maxMana = mana;
}

void Unit::setAttackDamage(int damage)
{
    this->attackDamage = damage;
}

void Unit::setDefense(int defense)
{
    this->defense = defense;
}

void Unit::setHealthRegen(int regen)
{
    this->healthRegen = regen;
}

void Unit::setManaRegen(int regen)
{
    this->manaRegen = regen;
}

void Unit::setStunned(bool stunned)
{
    this->isStunned = stunned;
}


int Unit::attack(Unit *target)
{
    if (!target)
        return 0;

    
    float LevelFactor = 1 + (getLevel() - target->getLevel()) * 0.05;

    int damage = (attackDamage)*LevelFactor * 1;

    int finalDamage = damage - (defense * 0.1);

    if (finalDamage < 0)
    {
        finalDamage = 0;
        log.push_back(target->getName() + " fully blocked " + getName() + " attack.");
    }

    log.push_back(getName() + " attacks " + target->getName() + " for " + to_string(finalDamage) + " damage.");

    return target->takeDamage(finalDamage);
}

int Unit::takeDamage(int damage)
{
    setCurrentHealth(getCurrentHealth() - damage);
    
    if (currentHealth <= 0)
    {
        log.push_back(getName() + " die. ");
    }

    return damage;
}

int Unit::heal(int amount)
{
    int oldHealth = currentHealth;
    setCurrentHealth(currentHealth + amount);
    int healthAdded = currentHealth - oldHealth;

    log.push_back(getName() + " heals " + to_string(healthAdded) + " health.");

    return healthAdded;
}

int Unit::restoreMana(int amount)
{
    
    setCurrentMana(currentMana + amount);

    log.push_back(getName() + " restores " + to_string(amount) + " mana.");

    return amount;
}

bool Unit::useSkill(Skill *skill, Unit *target)
{
    if (!skill || !target)
        return false;
    if (isStunned)
        return false;

    if (!hasSkill(skill))
    {
        return false;
    }

    if (currentMana < skill->getManaCost())
    {
        return false;
    }

    if (isStunned)
    {
        return false;
    }

    setCurrentMana(currentMana - skill->getManaCost());

    return skill->use(target);
}

bool Unit::hasSkill(Skill *skill) const
{
    for (size_t i = 0; i < skills.size(); ++i)
    {
        if (*skills[i] == *skill)
        {
            return true;
        }
    }
    return false;
}

void Unit::addSkill(Skill *skill)
{
    for (size_t i = 0; i < skills.size(); i++)
    {
        if (*skills[i] == *skill)
        {
            return;
        }
    }
    skills.push_back(skill);
}

void Unit::removeSkill(Skill *skill)
{
    auto it = find(skills.begin(), skills.end(), skill);
    if (it != skills.end())
    {
        skills.erase(it);
    }
}

void Unit::addEffect(Effect *effect)
{
    
    if (auto *statEffect = dynamic_cast<StatReductionEffect *>(effect))
    {
        for (Effect *e : activeEffects)
        {
            if (auto *existingStatEffect = dynamic_cast<StatReductionEffect *>(e))
            {
                
                existingStatEffect->setRemainingDuration(5);
                return;
            }
        }
    }

    
    activeEffects.push_back(effect);
    effect->apply(this);
    log.push_back((effect)->getName() + " applied to " + getName());
}

void Unit::removeEffect(Effect *effect)
{
    auto it = find(activeEffects.begin(), activeEffects.end(), effect);
    if (it != activeEffects.end())
    {
        (*it)->remove(this);
        delete *it;
        activeEffects.erase(it);
    }
}

void Unit::reset()
{

    
    for (auto i = activeEffects.begin(); i != activeEffects.end(); ++i)
    {
        if (*i != nullptr)
        {
            (*i)->remove(this);
            delete *i;
        }
    }

    
    activeEffects.clear();

    
    currentHealth = maxHealth;
    currentMana = maxMana;
}

void Unit::updateEffects()
{
    auto it = activeEffects.begin();
    while (it != activeEffects.end())
    {
        (*it)->tick(this);
        log.push_back(getName() + " got effect from " + (*it)->getName());
        if ((*it)->isExpired())
        {
            log.push_back((*it)->getName() + " removed from " + getName());
            (*it)->remove(this);
            delete *it;
            it = activeEffects.erase(it);
        }
        else
        {
            it++;
        }
    }
}

void Unit::tick()
{
    
    setCurrentHealth(currentHealth + healthRegen);
    setCurrentMana(currentMana + manaRegen);

    
    updateEffects();
}


void Unit::setAssets(string path)
{
    this->assets = path;
}

void Unit::setLevel(int level)
{
    this->level = level;
}

string Unit::getAssets() const
{
    return assets;
}

void Unit::scaleStats(double k)
{
    this->attackDamage *= k;
    this->maxHealth *= k;
    this->maxMana *= k;
    this->currentMana *= k;
    this->currentHealth *= k;

    this->stats[0] *= k;
    this->stats[1] *= k;
    this->stats[2] *= k;

    this->reset();
}

int Unit::getLevel()
{
    return this->level;
}

string Unit::getRank()
{
    if (level <= 10)
    {
        return "E";
    }

    if (level <= 20)
    {
        return "D";
    }

    if (level <= 25)
    {
        return "C";
    }

    if (level <= 35)
    {
        return "B";
    }

    if (level <= 50)
    {
        return "A";
    }

    if (level > 50)
    {
        return "S";
    }

    return "";
}

vector<string> Unit::getLog()
{
    return this->log;
}

void Unit::resetLog()
{
    this->log.clear();
}

vector<Effect *> Unit::getActiveEffects()
{
    return this->activeEffects;
}