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

        std::shared_ptr<CItem> emptyItem = nullptr;
        std::shared_ptr<CItem> getItemAt(unsigned i) const;

        void eraseItemAt(unsigned i);

        bool getItem(std::shared_ptr<CPlayerRogue> rogue, std::shared_ptr<CPickup> pickup);
        bool getItem(std::shared_ptr<CPlayerPaladin> paladin, std::shared_ptr<CPickup> pickup);
        bool getItem(std::shared_ptr<CPlayerMage> mage, std::shared_ptr<CPickup> pickup);

    private:
        unsigned m_size;
        unsigned m_itemCount;
        std::vector<std::shared_ptr<CItem>> m_contents;

};

#endif