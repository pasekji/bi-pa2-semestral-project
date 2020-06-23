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

class CInventory
{
    public:
        CInventory(unsigned size);

        void incrementSelected();
        void decrementSelected();
        void useItem();
        void dumpItem();
        void saveItems();
        void constructFill();

        unsigned getSize() const
        {
            return m_size;
        }

        CItem* getItemAt(unsigned i) const
        {
            return m_contents[i]; 
        }

        bool getItem(CPlayerRogue* rogue, CPickup* pickup);
        bool getItem(CPlayerPaladin* paladin, CPickup* pickup);
        bool getItem(CPlayerMage* mage, CPickup* pickup);

    private:
        unsigned m_size;
        unsigned m_itemCount;
        std::vector<CItem*> m_contents;

};

#endif