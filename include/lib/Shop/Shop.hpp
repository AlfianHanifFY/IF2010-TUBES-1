#ifndef SHOP_HPP
#define SHOP_HPP

#include <iostream>
#include "../Item/Item.hpp"
#include "ShopItem.hpp"

#include <map>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Shop
{
private:
    
    std::map<std::string, std::vector<ShopItem>> inventory;
    ShopItem *findShopItem(const std::string &id);

public:
    Shop();
    ~Shop();

    void restock(const std::vector<Item *> &items);
    bool buyItem(const std::string &id);
    void sellItem(Item *item);
    void displayInventory() const;
    std::vector<ShopItem> getItemsByType(const std::string &type) const;
};

#endif
