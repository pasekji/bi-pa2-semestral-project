#ifndef INVENTORY_H
#define INVENTORY_H

#include "CItem.fwd.h"
#include "CPlayerPaladin.fwd.h"
#include "CPlayerMage.fwd.h"
#include "CPlayerRogue.fwd.h"
#include "CPickup.fwd.h"
#include <vector>
#include <map>
#include <random>
#include <memory>
#include <algorithm>

class CInventory
{
    public:
        CInventory(unsigned size);
        ~CInventory() = default;
        void incrementSelected();
        void decrementSelected();
        void useItem();
        void dumpItem();
        void saveItems();
        void constructFill();

        unsigned getSize() const;

        CItem* emptyItem = nullptr;
        CItem* getItemAt(unsigned i) const;

        void eraseItemAt(unsigned i);

        bool getItem(CPlayerRogue* rogue, CPickup* pickup);
        bool getItem(CPlayerPaladin* paladin, CPickup* pickup);
        bool getItem(CPlayerMage* mage, CPickup* pickup);

    private:
        unsigned m_size;
        unsigned m_itemCount;
        std::vector<CItem*> m_contents;

};

#endif