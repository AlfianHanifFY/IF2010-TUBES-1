
#include "GameState/GameState.hpp"

GameState::GameState() : character(nullptr), io(IO()), inventory(new Inventory()), shop(new Shop()), dungeon(nullptr)
{
    this->isNewGame = false;
}

GameState::~GameState()
{
    if (character != nullptr)
    {
        delete character;
        character = nullptr;
    }
}

void GameState::setCharacter(Character *c)
{
    if (character != nullptr)
    {
        delete character;
    }
    character = c;
}

void GameState::setDungeon(Dungeon *_dungeon)
{
    this->dungeon = _dungeon;
}

Dungeon *GameState::getDungeon()
{
    return this->dungeon;
}

Character *GameState::getCharacter()
{
    return character;
}

vector<Item *> GameState::getItems()
{
    return this->items;
}

Shop *GameState::getShop()
{
    return this->shop;
}

Inventory *GameState::getInventory()
{
    return this->inventory;
}

Item *GameState::findItemByID(const std::string &itemID)
{
    for (auto &item : items)
    {
        if (item->getID() == itemID)
        {
            cout << "ketemu\n";
            return item;
        }
    }
    return nullptr;
}

vector<Item *> GameState::getMobLoot()
{
    vector<Item *> prize;

    map<int, vector<Mob *>> dungeonMob = getDungeon()->getDungeonMob();

    for (const auto &[chamber, mobs] : dungeonMob)
    {
        for (Mob *mob : mobs)
        {
            if (mob->getCurrentHealth() <= 0)
            {
                string mobName = mob->getName();

                if (mobLoot.count(mobName))
                {
                    const auto &lootList = mobLoot[mobName];
                    for (const auto &[itemID, probability] : lootList)
                    {
                        double rng = (rand() % 1000) / 1000.0;
                        if (rng <= probability)
                        {
                            Item *item = findItemByID(itemID);
                            if (item)
                            {
                                prize.push_back(item);
                            }
                        }
                    }
                }
            }
        }
    }

    return prize;
}

void GameState::displayMobloot() const
{

    for (const auto &pair : mobLoot)
    {
        std::cout << "Loot untuk Mob: " << pair.first << "\n";
        for (const auto &loot : pair.second)
        {
            std::cout << "  - Item ID: " << loot.first
                      << ", Probabilitas: " << loot.second * 100 << "%\n";
        }
        std::cout << std::endl;
    }
}

void GameState::loadConfig(string path)
{
    try
    {
        string finalPath = path + string("/player.txt");
        loadPlayer(finalPath);

        finalPath = path + string("/item.txt");
        loadItem(finalPath);

        finalPath = path + string("/shop.txt");
        loadShop(finalPath);

        finalPath = path + string("/backpack.txt");
        loadInventory(finalPath);

        finalPath = path + string("/mobloot.txt");
        loadMobLoot(finalPath);

        finalPath = path + string("/equipment.txt");
        loadEquipment(finalPath);
    }
    catch (const std::exception &e)
    {
        throw string(e.what());
    }
    catch (const string &e)
    {
        throw e;
    }
    catch (...)
    {
        throw string("Unknown error during loadConfig");
    }
}

void GameState::loadItem(string f)
{

    vector<string> lines = io.readFileLine(f);

    for (auto it = lines.begin(); it != lines.end(); it++)
    {
        vector<string> words = io.parseLine(*it);
        vector<Effect *> effects;

        if (words.size() >= 6)
        {
            string id = words.at(0);
            string name = words.at(1);
            string type = words.at(2);
            char rarity = words.at(3).at(0);
            int baseStat = stoi(words.at(4));
            int price = 0;

            for (size_t i = 5; i < words.size(); i++)
            {
                if (words.at(i) != "-")
                {
                    if (words.at(i) == "CrimsonCurse")
                    {
                        effects.push_back(new CrimsonCurseEffect());
                    }
                    else if (words.at(i) == "DamageReduction")
                    {
                        effects.push_back(new DamageReductionEffect());
                    }
                    else if (words.at(i) == "DullingCurse")
                    {
                        effects.push_back(new DullingCurseEffect());
                    }
                    else if (words.at(i) == "HealthRegen")
                    {
                        effects.push_back(new HealthRegenEffect());
                    }
                    else if (words.at(i) == "ManaRegen")
                    {
                        effects.push_back(new ManaRegenEffect());
                    }
                    else if (words.at(i) == "Reflect")
                    {
                        effects.push_back(new ReflectEffect());
                    }
                    else if (words.at(i) == "ShadowFang")
                    {
                        effects.push_back(new ShadowFangEffect());
                    }
                    else if (words.at(i) == "ShatterArmor")
                    {
                        effects.push_back(new ShatterArmorEffect());
                    }
                    else if (words.at(i) == "SpeedBoost")
                    {
                        effects.push_back(new SpeedBoostEffect());
                    }
                    else
                    {
                        cout << "trhoe\n";
                        throw string("Effect tidak dikenal: ");
                    }
                }
            }

            if (type == "Weapon")
            {
                items.push_back(new Weapon(id, name, rarity, baseStat, effects, price));
            }
            else if (type == "Armor_Head")
            {
                items.push_back(new Armor(id, name, rarity, baseStat, effects, price, "Head"));
            }
            else if (type == "Armor_Body")
            {
                items.push_back(new Armor(id, name, rarity, baseStat, effects, price, "Body"));
            }
            else if (type == "Armor_Foot")
            {
                items.push_back(new Armor(id, name, rarity, baseStat, effects, price, "Foot"));
            }
            else if (type == "Potion")
            {
                items.push_back(new Potion(id, name, rarity, baseStat, effects, price));
            }
            else if (type == "Pendant")
            {
                items.push_back(new Pendant(id, name, rarity, baseStat, effects, price));
            }
            else
            {
                throw string("Tipe item tidak valid: ");
            }
        }
        else
        {
            throw string("Jumlah data dalam baris item.txt tidak valid");
        }
    }
}

void GameState::loadPlayer(string f)
{
    vector<string> lines = io.readFileLine(f);

    if (!lines.empty())
    {
        for (auto it = lines.begin(); it != lines.end(); ++it)
        {
            vector<string> words = io.parseLine(*it);

            if (words.size() == 6)
            {
                string name = words[0];
                replace(name.begin(), name.end(), '_', ' ');

                string type = words[1];
                int gold = stoi(words[2]);
                int exp = stoi(words[3]);
                int mastery = stoi(words[4]);
                int level = stoi(words[5]);

                if (type == "Fighter")
                {
                    this->character = new Fighter(name);
                }
                else if (type == "Mage")
                {
                    this->character = new Mage(name);
                }
                else if (type == "Assasin")
                {
                    this->character = new Assasin(name);
                }
                else if (type == "Berserker")
                {
                    this->character = new Berserker(name);
                }
                else if (type == "Necromancer")
                {
                    this->character = new Necromancer(name);
                }
                else
                {
                    throw string("Tipe karakter tidak dikenal: " + type);
                }

                this->character->setGold(gold);
                this->character->setExp(exp);
                this->character->setMastery(mastery);
                this->character->setLevel(level);
            }
            else
            {
                throw string("Konfigurasi player tidak valid: jumlah data tidak sesuai.");
            }
        }
    }
    else
    {
        setNewGame();
    }
}

void GameState::loadEquipment(string f)
{
    vector<string> lines = io.readFileLine(f);

    for (const auto &line : lines)
    {
        vector<string> words = io.parseLine(line);

        if (words.size() > 1)
        {
            const string &itemID = words[1];
            Item *item = findItemByID(itemID);

            if (!item)
            {
                throw std::string("No item like ") + itemID;
            }

            try
            {
                inventory->equipItem(item);
            }
            catch (string &e)
            {
                throw e;
            }
        }
        else if (words.size() == 1)
        {
        }
        else
        {
            throw std::string("Konfigurasi load tidak valid: ") + line;
        }
    }
}

void GameState::loadInventory(string f)
{

    vector<string> lines = io.readFileLine(f);

    for (auto it = lines.begin(); it != lines.end(); it++)
    {
        vector<string> words = io.parseLine(*it);

        if (words.size() == 4)
        {

            int row = stoi(words[0]);
            int col = stoi(words[1]);
            string itemID = words[2];
            int totalStack = stoi(words[3]);

            Item *item = nullptr;
            for (auto &i : items)
            {
                if (i->getID() == itemID)
                {
                    item = i;
                    break;
                }
            }

            if (!item)
            {
                throw string("Item dengan ID tidak ditemukan.");
            }

            for (int i = 0; i < totalStack; ++i)
            {
                if (!inventory->addItemAt(item, row, col))
                {
                    throw string("Gagal menambahkan item ke slot ");
                }
            }
        }
        else
        {
            throw string("Konfigurasi inventory tidak valid");
        }
    }
}

void GameState::loadMobLoot(string f)
{

    vector<string> lines = io.readFileLine(f);

    for (auto it = lines.begin(); it != lines.end(); it++)
    {
        vector<string> words = io.parseLine(*it);

        if (words.size() == 3)
        {
            string mobName = words[0];
            string itemID = words[1];
            double probability = std::stod(words[2]);

            if (probability < 0.0 || probability > 1.0)
            {
                throw std::string("Probabilitas harus antara 0 dan 1.");
            }

            mobLoot[mobName].push_back({itemID, probability});
        }
        else
        {
            throw std::string("Konfigurasi mob loot tidak valid, baris harus memiliki 3 kata.");
        }
    }
}

void GameState::loadShop(string f)
{

    vector<string> lines = io.readFileLine(f);

    for (auto it = lines.begin(); it != lines.end(); it++)
    {
        vector<string> words = io.parseLine(*it);

        if (words.size() == 4)
        {
            string name = words.at(0);
            char rarity = words.at(1)[0];
            int price = stoi(words.at(2));
            int stock = stoi(words.at(3));

            bool found = false;
            for (auto item : items)
            {

                if (item->getName() == name && item->getRarity() == rarity)
                {
                    item->setPrice(price);
                    for (int i = 0; i < stock; i++)
                    {
                        shop->restock({item});
                    }
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                throw string("Item tidak ditemukan di daftar items: ");
            }
        }
        else
        {
            throw string("Konfigurasi shop tidak valid");
        }
    }
}

void GameState::HMIF()
{
    this->character->setGold(9999999);
    this->character->setExp(9999999);
    this->character->setMastery(9999999);
    this->character->setMaxHealth(99999);
    this->character->setMaxMana(99990);
    this->character->setAttackDamage(9999999);
    this->character->setDefense(9999999);
    this->character->setCurrentHealth(9999999);
    this->character->setCurrentMana(9999999);
}

void GameState::saveConfig(string path)
{
    try
    {
        if (!filesystem::exists(path))
        {
            throw string("Folder tidak ditemukan!");
        }

        string finalPath = path + string("/item.txt");
        saveItem(finalPath);

        finalPath = path + string("/shop.txt");
        saveShop(finalPath);

        finalPath = path + string("/backpack.txt");
        saveInventory(finalPath);

        finalPath = path + string("/mobloot.txt");
        saveMobLoot(finalPath);

        finalPath = path + string("/equipment.txt");
        saveEquipment(finalPath);

        finalPath = path + string("/player.txt");
        savePlayer(finalPath);
    }
    catch (const string &e)
    {
        throw e;
    }
}

void GameState::saveItem(string f)
{
    vector<string> lines;

    for (Item *item : items)
    {
        string type = item->getType();

        if (type == "Armor")
        {
            Armor *armor = dynamic_cast<Armor *>(item);
            if (armor)
            {
                string part = armor->getPart();
                type = "Armor_" + part;
            }
        }

        string line = item->getID() + " " + item->getName() + " " + type + " ";
        line += item->getRarity();
        line += " " + to_string(item->getBaseStat());

        vector<Effect *> effects = item->getEffects();
        if (effects.empty())
        {
            line += " -";
        }
        else
        {
            for (Effect *effect : effects)
            {
                line += " " + effect->getName();
            }
        }

        if (effects.size() < 3)
        {
            line += " -";
        }

        lines.push_back(line);
    }

    io.write(f, lines);
}

void GameState::saveEquipment(string f)
{
    vector<string> lines;

    Item *weapon = inventory->getWeapon();
    if (weapon)
        lines.push_back("WEAPON " + weapon->getID());

    Item *armorHead = inventory->getHead();
    if (armorHead)
        lines.push_back("ARMOR_HEAD " + armorHead->getID());

    Item *armorBody = inventory->getBody();
    if (armorBody)
        lines.push_back("ARMOR_BODY " + armorBody->getID());

    Item *armorFoot = inventory->getFoot();
    if (armorFoot)
        lines.push_back("ARMOR_FOOT " + armorFoot->getID());

    Item *pendant = inventory->getPendant();
    if (pendant)
        lines.push_back("PENDANT " + pendant->getID());

    io.write(f, lines);
}

void GameState::saveInventory(string f)
{
    vector<string> lines;

    const int rowCount = 4;
    const int colCount = 8;

    for (int row = 0; row < rowCount; ++row)
    {
        for (int col = 0; col < colCount; ++col)
        {
            Item *item = inventory->getItemAt(row, col);
            int qty = inventory->getQuantityAt(row, col);

            if (item != nullptr && qty > 0)
            {
                string line = to_string(row) + " " + to_string(col) + " " +
                              item->getID() + " " + to_string(qty);
                lines.push_back(line);
            }
        }
    }

    io.write(f, lines);
}

void GameState::saveShop(string f)
{
    vector<string> lines;

    vector<string> types = {"Weapon", "Armor", "Potion"};

    for (const string &type : types)
    {
        vector<ShopItem> itemsOfType = shop->getItemsByType(type);

        for (const ShopItem &shopItem : itemsOfType)
        {
            Item *item = shopItem.getItem();

            string line = item->getName() + " " +
                          string(1, item->getRarity()) + " " +
                          to_string(item->getPrice()) + " " +
                          to_string(shopItem.getQuantity());

            lines.push_back(line);
        }
    }
    io.write(f, lines);
}

void GameState::savePlayer(string f)
{
    vector<string> lines;

    if (this->character != nullptr)
    {
        string name = this->character->getName();
        replace(name.begin(), name.end(), ' ', '_');

        string line = name + " " +
                      this->character->getCharType() + " " +
                      to_string(this->character->getGold()) + " " +
                      to_string(this->character->getExp()) + " " +
                      to_string(this->character->getMastery()) + " " +
                      to_string(this->character->getLevel());

        lines.push_back(line);
    }
    else
    {
        throw string("Tidak ada karakter yang bisa disimpan.");
    }

    io.write(f, lines);
}

void GameState::saveMobLoot(string f)
{
    vector<string> lines;

    for (const auto &entry : mobLoot)
    {
        string mobName = entry.first;
        const vector<pair<string, double>> &lootList = entry.second;

        for (const auto &loot : lootList)
        {
            string itemID = loot.first;
            double probability = loot.second;

            string line = mobName + " " + itemID + " " + to_string(probability);
            lines.push_back(line);
        }
    }

    io.write(f, lines);
}

void GameState::setNewGame()
{
    this->isNewGame = true;
}

bool GameState::getNewGame()
{
    return this->isNewGame;
}

string GameState::getConfigPath()
{
    return this->config;
}

void GameState::setConfigPath(string s)
{
    this->config = s;
}

void GameState::reset()
{
    delete character;
    character = nullptr;
    delete dungeon;
    dungeon = nullptr;
    delete shop;
    shop = nullptr;
    delete inventory;
    inventory = nullptr;

    for (auto item : items)
        delete item;
    items.clear();

    shop = new Shop();

    mobLoot.clear();
    config.clear();
    isNewGame = true;
}
