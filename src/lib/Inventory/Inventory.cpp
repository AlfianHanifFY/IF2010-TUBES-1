#include "Inventory/Inventory.hpp"

Inventory::Inventory()
{
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            backpack[i][j].setItem(nullptr);
        }
    }

    
    
    
    

    
    
}

Inventory &Inventory::operator+=(Item *item)
{
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            Slot &slot = backpack[i][j];
            if (slot.getItem() && slot.getItem()->getID() == item->getID() && slot.getQuantity() < MAX_STACK)
            {
                slot.increaseQuantity(1);
                return *this;
            }
        }
    }

    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            Slot &slot = backpack[i][j];
            if (slot.isEmpty())
            {
                slot.setItem(item);
                slot.setQuantity(1);
                return *this;
            }
        }
    }

    throw string("Backpack penuh! Tidak bisa menambah item.");
}


bool Inventory::addItemAt(Item *item, int i, int j)
{

    if (i < 0 || i >= ROWS || j < 0 || j >= COLS)
    {
        throw std::out_of_range("Indeks slot tidak valid.");
    }

    Slot &slot = backpack[i][j];

    if (slot.getItem() && slot.getItem()->getID() == item->getID() && slot.getQuantity() < MAX_STACK)
    {
        slot.increaseQuantity(1);
        return true;
    }

    else if (slot.isEmpty())
    {
        slot.setItem(item);
        slot.setQuantity(1);
        return true;
    }

    throw std::runtime_error("Slot tidak dapat menampung item.");
}

Item *Inventory::removeItem(const std::string &itemID)
{
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            Slot &slot = backpack[i][j];
            if (slot.getItem() && slot.getItem()->getID() == itemID)
            {
                if (slot.getQuantity() == 0)
                {
                    throw std::runtime_error("Tidak bisa mengurangi item karena jumlahnya 0.");
                }
                slot.decreaseQuantity(1);
                Item *item = slot.getItem();
                if (slot.getQuantity() == 0)
                {
                    slot.setItem(nullptr);
                }
                return item;
            }
        }
    }
    throw std::runtime_error("Item tidak ditemukan di backpack.");
}

void Inventory::printBackpack() const
{
    std::cout << "\n=================== [ Backpack ] ===================\n";
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            const Slot &slot = backpack[i][j]; 
            if (slot.getItem())
            {
                
                std::cout << "Slot [" << i << "][" << j << "]: "
                          << slot.getItem()->getName()
                          << " [x" << slot.getQuantity() << "]\n";
            }
            else
            {
                
                std::cout << "Slot [" << i << "][" << j << "]: Empty\n";
            }
        }
    }
    std::cout << "=====================================================\n";
}

Item *Inventory::getItemAt(int row, int col)
{
    if (row < 0 || row >= ROWS || col < 0 || col >= COLS)
    {
        throw std::out_of_range("Indeks baris atau kolom tidak valid.");
    }

    return backpack[row][col].getItem(); 
}


void Inventory::printEquipped() const
{

    std::cout << "\n===================[ Equipped Item ]====================\n\n";
    std::cout << "Weapon         : " << (weapon ? weapon->getName() : "-") << "\n";
    std::cout << "Armor (Kepala) : " << (armors[0] ? armors[0]->getName() : "-") << "\n";
    std::cout << "Armor (Badan)  : " << (armors[1] ? armors[1]->getName() : "-") << "\n";
    std::cout << "Armor (Kaki)   : " << (armors[2] ? armors[2]->getName() : "-") << "\n";
    std::cout << "Pendant        : " << (pendant ? pendant->getName() : "-") << "\n\n";
}

bool Inventory::equipItem(Item *item)
{
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
        Armor *armor = dynamic_cast<Armor *>(item);
        if (!armor)
        {
            throw std::string("Item armor tidak valid.");
        }
        std::string part = armor->getPart();

        if (part == "Head")
        {
            if (!armors[0])
            {
                armors[0] = item;
                return true;
            }
            else
            {
                throw std::string("Armor untuk kepala sudah terisi.");
            }
        }
        else if (part == "Body")
        {
            if (!armors[1])
            {
                armors[1] = item;
                return true;
            }
            else
            {
                throw std::string("Armor untuk badan sudah terisi.");
            }
        }
        else if (part == "Foot")
        {
            if (!armors[2])
            {
                armors[2] = item;
                return true;
            }
            else
            {
                throw std::string("Armor untuk kaki sudah terisi.");
            }
        }
        else
        {
            throw std::string("Bagian armor tidak dikenali: " + part);
        }
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

bool Inventory::unequipItem(Item *item)
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
        Armor *armor = dynamic_cast<Armor *>(item);
        if (!armor)
        {
            throw std::string("Item armor tidak valid.");
        }
        std::string part = armor->getPart();

        if (part == "Head")
        {
            if (armors[0] && armors[0]->getID() == item->getID())
            {
                armors[0] = nullptr;
                return true;
            }
            else
            {
                throw std::string("Armor untuk kepala ini tidak sedang di-equip.");
            }
        }
        else if (part == "Body")
        {
            if (armors[1] && armors[1]->getID() == item->getID())
            {
                armors[1] = nullptr;
                return true;
            }
            else
            {
                throw std::string("Armor untuk badan ini tidak sedang di-equip.");
            }
        }
        else if (part == "Foot")
        {
            if (armors[2] && armors[2]->getID() == item->getID())
            {
                armors[2] = nullptr;
                return true;
            }
            else
            {
                throw std::string("Armor untuk kaki ini tidak sedang di-equip.");
            }
        }
        else
        {
            throw std::string("Bagian armor tidak dikenali: " + part);
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

int Inventory::getQuantityAt(int row, int col)
{
    return this->backpack[row][col].getQuantity();
}

Item *Inventory::getHead()
{
    return this->armors[0];
}
Item *Inventory::getBody()
{
    return this->armors[1];
}
Item *Inventory::getFoot()
{
    return this->armors[2];
}
Item *Inventory::getWeapon()
{
    return this->weapon;
}
Item *Inventory::getPendant()
{
    return this->pendant;
}

vector<Item *> Inventory::getPotion()
{
    vector<Item *> potion;

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            Item *item = backpack[i][j].getItem();
            if (item && item->getType() == "Potion")
            {
                potion.push_back(item);
            }
        }
    }
    return potion;
}

int Inventory::getItemQuantity(string &itemID)
{
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            Slot &slot = backpack[i][j];
            if (slot.getItem() && slot.getItem()->getID() == itemID)
            {
                return getQuantityAt(i, j);
            }
        }
    }
    throw std::runtime_error("Item tidak ditemukan di backpack.");
}