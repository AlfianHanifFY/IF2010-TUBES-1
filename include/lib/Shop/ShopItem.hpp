#ifndef SHOPITEM_HPP
#define SHOPITEM_HPP

#include <iostream>
#include "../Item/Item.hpp"

#include <iostream>
using namespace std;

class ShopItem {
private:
    Item* item;
    int quantity;
public:
    ShopItem(Item* item, int quantity);
    Item* getItem() const;
    int getQuantity() const;
    void increaseQuantity(int amount);
    bool decreaseQuantity(int amount);
};

#endif