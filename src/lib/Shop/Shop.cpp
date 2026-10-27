#include "Shop/Shop.hpp"

Shop::Shop() {}
Shop::~Shop() {}

ShopItem *Shop::findShopItem(const std::string &id)
{
    for (auto &pair : inventory)
    {
        for (auto &shopItem : pair.second)
        {
            if (shopItem.getItem()->getID() == id)
            {
                return &shopItem;
            }
        }
    }
    return nullptr;
}

void Shop::restock(const std::vector<Item *> &items)
{
    for (Item *item : items)
    {
        int quantityPotion;
        std::string type = item->getType();
        if (type == "Potion")
        {
            quantityPotion = 5;
        }
        else
        {
            quantityPotion = 1;
        }
        bool added = false;

        for (auto &shopItem : inventory[type])
        {
            if (shopItem.getItem()->getID() == item->getID())
            {
                shopItem.increaseQuantity(quantityPotion);
                added = true;
                break;
            }
        }

        if (!added)
        {
            inventory[type].emplace_back(item, quantityPotion);
        }
    }
}

bool Shop::buyItem(const std::string &id)
{
    try
    {
        ShopItem *shopItem = findShopItem(id);
        if (!shopItem)
        {
            throw std::invalid_argument("Item dengan ID '" + id + "' tidak ditemukan di shop.");
        }

        if (!shopItem->decreaseQuantity(1))
        {
            throw std::out_of_range("Stok item '" + shopItem->getItem()->getName() + "' habis.");
        }

        std::cout << "Item " << shopItem->getItem()->getName() << " dibeli.\n";
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Gagal membeli item: " << e.what() << std::endl;
        return false;
    }
}

void Shop::sellItem(Item *item)
{
    std::string type = item->getType();
    bool added = false;
    for (auto &shopItem : inventory[type])
    {
        if (shopItem.getItem()->getID() == item->getID())
        {
            shopItem.increaseQuantity(1);
            added = true;
            break;
        }
    }
    if (!added)
    {
        inventory[type].emplace_back(item, 1);
    }
    std::cout << "Item " << item->getName() << " dijual ke toko.\n";
}


void Shop::displayInventory() const
{
    for (const auto &pair : inventory)
    {
        std::cout << "=== " << pair.first << " ===\n";
        for (const auto &shopItem : pair.second)
        {
            std::cout << "- " << shopItem.getItem()->getName()
                      << " [x" << shopItem.getQuantity() << "]"
                      << " - Harga Beli: " << shopItem.getItem()->getBuyPrice() << "\n";
        }
    }
}

std::vector<ShopItem> Shop::getItemsByType(const std::string &type) const
{
    auto it = inventory.find(type);
    if (it != inventory.end())
    {
        return it->second;
    }
    return {};
}
