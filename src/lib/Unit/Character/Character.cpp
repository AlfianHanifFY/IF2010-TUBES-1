#include "Unit/Character/Character.hpp"

Character::Character(string name, int maxHealth, int healthRegen, int maxMana, int manaRegen, int attackDamage, int level, int exp, int mastery, int gold) : Unit(name, maxHealth, healthRegen, maxMana, manaRegen, attackDamage), skillPath(new SkillTree("skillPath"))
{
    this->level = level;
    this->exp = exp;
    this->mastery = mastery;
    this->gold = gold;
    this->inventory = new Inventory();

    weapon = nullptr;
    for (size_t i = 0; i < 3; i++)
    {
        armors[i] = nullptr;
    }

    pendant = nullptr;
}

Character::~Character()
{
    delete inventory;
}

int Character::getLevel() const
{
    return this->level;
}

int Character::getExp() const
{
    return this->exp;
}

int Character::getMastery() const
{
    return this->mastery;
}

int Character::getGold() const
{
    return this->gold;
}

Inventory &Character::getInventory() const
{
    return *inventory;
}

void Character::setExp(int exp)
{

    this->exp = exp;
    int count = this->exp / 100;
    for (int i = 0; i < count; i++)
    {
        levelUp();
    }
}

void Character::setMastery(int mastery)
{
    this->mastery = mastery;
}

void Character::setGold(int gold)
{
    this->gold = gold;
}

void Character::addExp(int amount)
{

    exp += amount;

    if (exp < 0)
    {
        exp = 0;
    }

    int expNeededToNextLevel = 100;

    while (exp >= expNeededToNextLevel)
    {
        exp -= expNeededToNextLevel;
        levelUp();
    }
}

void Character::addMastery(int amount)
{

    mastery += amount;
}

void Character::addGold(int amount)
{

    gold += amount;
    if (gold < 0)
    {
        gold = 0;
    }
}

string Character::getRank()
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

bool Character::learnSkill(Skill *skill)
{
    if (getMastery() >= skill->getMasteryCost())
    {
        if (getSkillTree()->CanMaster(skill))
        {
            getSkillTree()->addLearnedSkill(skill);
            this->mastery -= skill->getMasteryCost();
            getSkillTree()->update();
            this->skills = getSkillTree()->getActiveSkill();
            return true;
        }
        else
        {
            throw string("Cant learn this skill");
            return false;
        }
    }
    else
    {

        throw string("Not enough mastery point");
        return false;
    }
}

Item *Character::getHead()
{
    return this->armors[0];
}
Item *Character::getBody()
{
    return this->armors[1];
}
Item *Character::getFoot()
{
    return this->armors[2];
}
Item *Character::getWeapon()
{
    return this->weapon;
}
Item *Character::getPendant()
{
    return this->pendant;
}

int Character::attack(Unit *target)
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

    int finalDamage = damage - defense;

    if (finalDamage < 0)
    {
        finalDamage = 0;
        log.push_back(target->getName() + " fully blocked " + getName() + " attack.");
    }

    log.push_back(getName() + " attacks " + target->getName() + " for " + to_string(finalDamage) + " damage.");

    return target->takeDamage(finalDamage);
}

bool Character::equipItem(Item *item)
{
    if (item == nullptr)
    {
        throw string("null bang");
    }

    if (item->getType() == "Weapon")
    {
        if (!weapon)
        {
            weapon = item;
            return true;
        }
        else
        {
            throw std::string("Weapon slot sudah terisi.");
        }
    }
    else if (item->getType() == "Armor")
    {
        for (int i = 0; i < 3; ++i)
        {
            if (armors[i] == nullptr)
            {
                armors[i] = item;
                return true;
            }
        }
        throw std::string("Semua slot armor sudah terisi.");
    }
    else if (item->getType() == "Pendant")
    {
        if (!pendant)
        {
            pendant = item;

            return true;
        }
        else
        {
            throw std::string("Slot pendant sudah terisi.");
        }
    }
    throw std::string("Tipe item tidak dikenali.");
}

bool Character::unequipItem(Item *item)
{
    if (!item)
    {
        throw std::string("Item tidak boleh null.");
    }

    std::string type = item->getType();

    if (type == "Weapon")
    {
        if (weapon && weapon->getID() == item->getID())
        {

            this->weapon = nullptr;
            return true;
        }
        else
        {
            throw std::string("Weapon ini tidak sedang di-equip.");
        }
    }
    else if (type == "Armor")
    {
        bool found = false;
        for (int i = 0; i < 3; ++i)
        {
            if (armors[i] && armors[i]->getID() == item->getID())
            {
                armors[i] = nullptr;
                found = true;
                break;
            }
        }
        if (found)
        {
            return true;
        }
        else
        {
            throw std::string("Armor ini tidak sedang di-equip.");
        }
    }
    else if (type == "Pendant")
    {
        if (pendant && pendant->getID() == item->getID())
        {
            pendant = nullptr;
            return true;
        }
        else
        {
            throw std::string("Pendant ini tidak sedang di-equip.");
        }
    }
    else
    {
        throw std::string("Tipe item tidak dikenali untuk unequip.");
    }
}

void Character::printEquipped() const
{

    std::cout << "\n===================[ Equipped Item ]====================\n\n";
    std::cout << "Weapon         : " << (weapon ? weapon->getName() : "-") << "\n";
    std::cout << "Armor (Kepala) : " << (armors[0] ? armors[0]->getName() : "-") << "\n";
    std::cout << "Armor (Badan)  : " << (armors[1] ? armors[1]->getName() : "-") << "\n";
    std::cout << "Armor (Kaki)   : " << (armors[2] ? armors[2]->getName() : "-") << "\n";
    std::cout << "Pendant        : " << (pendant ? pendant->getName() : "-") << "\n\n";
}

void Character::useGold(int n)
{
    this->gold -= n;
}

SkillTree *Character::getSkillTree()
{
    return this->skillPath;
}

void Character::applyItemEffect()
{

    if (pendant)
    {
        vector<Effect *> pendantEffect = pendant->getEffects();
        for (auto i = pendantEffect.begin(); i != pendantEffect.end(); i++)
        {
            Effect *clone = (*i)->clone();
            clone->setPermanent();
            addEffect(clone);
        }
    }

    if (getHead())
    {
        vector<Effect *> headEffects = getHead()->getEffects();
        for (auto i = headEffects.begin(); i != headEffects.end(); i++)
        {
            Effect *clone = (*i)->clone();
            clone->setPermanent();
            addEffect(clone);
        }
    }

    if (getBody())
    {
        vector<Effect *> bodyEffects = getBody()->getEffects();
        for (auto i = bodyEffects.begin(); i != bodyEffects.end(); i++)
        {
            Effect *clone = (*i)->clone();
            clone->setPermanent();
            addEffect(clone);
        }
    }

    if (getFoot())
    {
        vector<Effect *> footEffects = getFoot()->getEffects();
        for (auto i = footEffects.begin(); i != footEffects.end(); i++)
        {
            Effect *clone = (*i)->clone();
            clone->setPermanent();
            addEffect(clone);
        }
    }
}