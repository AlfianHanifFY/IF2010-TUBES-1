
#ifndef GameState_HPP
#define GameState_HPP

#include "Unit/Character/Fighter/Fighter.hpp"
#include "Unit/Character/Mage/Mage.hpp"
#include "Unit/Character/Character.hpp"
#include "Unit/Character/Necromancer/Necromancer.hpp"
#include "Unit/Character/Assasin/Assasin.hpp"
#include "Unit/Character/Berserker/Berserker.hpp"
#include "Unit/Unit.hpp"
#include "Unit/Mob/BasicMob/Goblin/Goblin.hpp"
#include "Unit/Mob/BasicMob/Slime/Slime.hpp"
#include "Unit/Mob/BasicMob/BasicMob.hpp"
#include "Unit/Mob/BasicMob/Skeleton/Skeleton.hpp"
#include "Unit/Mob/BasicMob/Orc/Orc.hpp"
#include "Unit/Mob/Mob.hpp"
#include "Unit/Mob/BossMob/Ogre/Ogre.hpp"
#include "Unit/Mob/BossMob/BossMob.hpp"
#include "Unit/Mob/BossMob/Lich/Lich.hpp"
#include "Unit/Mob/BossMob/DarkKnight/DarkKnight.hpp"
#include "Unit/Mob/BossMob/DemonLord/DemonLord.hpp"
#include "Skill/Skill.hpp"
#include "SkillTree/SkillTree.hpp"
#include "Shop/ShopItem.hpp"
#include "Shop/Shop.hpp"
#include "IO/IO.hpp"
#include "Dungeon/DungeonRankB/DungeonRankB.hpp"
#include "Dungeon/DungeonRankE/DungeonRankE.hpp"
#include "Dungeon/DungeonRankD/DungeonRankD.hpp"
#include "Dungeon/DungeonRankC/DungeonRankC.hpp"
#include "Dungeon/DungeonSpecial/DungeonSpecial.hpp"
#include "Dungeon/DungeonRankS/DungeonRankS.hpp"
#include "Dungeon/DungeonRankA/DungeonRankA.hpp"
#include "Dungeon/Dungeon.hpp"
#include "Effect/ItemEffect/ReflectEffect/ReflectEffect.hpp"
#include "Effect/ItemEffect/DamageReductionEffect/DamageReductionEffect.hpp"
#include "Effect/ItemEffect/ShadowFangEffect/ShadowFangEffect.hpp"
#include "Effect/ItemEffect/CrimsonCurseEffect/CrimsonCurseEffect.hpp"
#include "Effect/ItemEffect/ManaRegenEffect/ManaRegenEffect.hpp"
#include "Effect/ItemEffect/HealthRegenEffect/HealthRegenEffect.hpp"
#include "Effect/ItemEffect/ItemEffect.hpp"
#include "Effect/ItemEffect/ShatterArmorEffect/ShatterArmorEffect.hpp"
#include "Effect/ItemEffect/DullingCurseEffect/DullingCurseEffect.hpp"
#include "Effect/ItemEffect/SpeedBoostEffect/SpeedBoostEffect.hpp"
#include "Effect/Effect.hpp"
#include "Effect/SkillEffect/StatReductionEffect/StatReductionEffect.hpp"
#include "Effect/SkillEffect/RageEffect/RageEffect.hpp"
#include "Effect/SkillEffect/SlowEffect/SlowEffect.hpp"
#include "Effect/SkillEffect/BurnEffect/BurnEffect.hpp"
#include "Effect/SkillEffect/StunEffect/StunEffect.hpp"
#include "Effect/SkillEffect/DecayEffect/DecayEffect.hpp"
#include "Effect/SkillEffect/HealthDrainEffect/HealthDrainEffect.hpp"
#include "Effect/SkillEffect/ManaDrainEffect/ManaDrainEffect.hpp"
#include "Effect/SkillEffect/HealEffect/HealEffect.hpp"
#include "Effect/SkillEffect/CriticalDamageEffect/CriticalDamageEffect.hpp"
#include "Effect/SkillEffect/SkillEffect.hpp"
#include "Effect/SkillEffect/WeakenEffect/WeakenEffect.hpp"
#include "Item/Weapon/Weapon.hpp"
#include "Item/Pendant/Pendant.hpp"
#include "Item/Armor/Armor.hpp"
#include "Item/Item.hpp"
#include "Item/Potion/Potion.hpp"
#include "Rarity/Rarity.hpp"
#include "Inventory/Inventory.hpp"
#include "Inventory/Slot.hpp"

#include <iostream>
#include <filesystem>

using namespace std;

class GameState
{
private:
    Character *character;
    IO io;
    string config;
    vector<Item *> items;
    Shop *shop;
    Dungeon *dungeon;
    Inventory *inventory;
    map<string, vector<pair<string, double>>> mobLoot;

    bool isNewGame;

public:
    GameState();
    ~GameState();

    void setNewGame();
    bool getNewGame();

    void setCharacter(Character *newCharacter);
    Character *getCharacter();

    void setDungeon(Dungeon *newDungeon);
    Dungeon *getDungeon();

    vector<Item *> getItems();
    Shop *getShop();

    Inventory *getInventory();

    Item *findItemByID(const std::string &itemID);

    void displayMobloot() const;

    vector<Item *> getMobLoot();

    string getConfigPath();
    void setConfigPath(string);
    void loadConfig(string);
    void loadPlayer(string);
    void loadItem(string);
    void loadShop(string);
    void loadInventory(string);
    void loadMobLoot(string);
    void loadEquipment(string);

    void saveConfig(string);
    void saveItem(string);
    void saveShop(string);
    void saveInventory(string);
    void saveMobLoot(string);
    void saveEquipment(string);
    void savePlayer(string);

    void HMIF();
    void reset();
};

#endif
