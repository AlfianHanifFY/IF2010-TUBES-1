#ifndef SLOT_HPP
#define SLOT_HPP

#include "../Item/Item.hpp"  

class Slot {
private:
    Item* item;        
    int quantity;    

public:
    Slot(); 
    Slot(Item* newItem, int qty = 1);  

    
    Item* getItem() const;
    int getQuantity() const;
    
    
    void setItem(Item* newItem);
    void setQuantity(int newQuantity);
    
    
    void increaseQuantity(int amount);
    void decreaseQuantity(int amount);
    bool isEmpty() const;
};

#endif
