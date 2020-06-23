#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <cstdlib>
#include "CItem.fwd.h"
#include "CPlayerPaladin.h"
#include "CPlayerRogue.h"
#include "CPlayerMage.h"
#include "enums.h"


class CItem
{
    public:
        virtual bool accept(CPlayerPaladin* paladin) = 0;
        virtual bool accept(CPlayerMage* mage) = 0;
        virtual bool accept(CPlayerRogue* rogue) = 0;
        virtual std::string getLabel() const = 0;

        CItem() = default;
        virtual ~CItem()
        {}

    protected:
        std::string m_name;
        std::string m_label;
        std::size_t m_price;
        std::size_t m_useability;            // count of possible uses

        virtual bool itemApply() = 0;

};

#endif