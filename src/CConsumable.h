#ifndef CONSUMABLE_H
#define CONSUMABLE_H

#include "CItem.h"

class CConsumable : public CItem        // could be stackable
{
    public:
        CConsumable(const std::string & name, const std::string & lable, std::size_t price, std::size_t useability, int healthSource, int energySource, int sideEffect) : CItem(name, lable, price, useability)
        {
            m_healthSource = healthSource;
            m_energySource = energySource;
            m_sideEffect = sideEffect;
        }

        CConsumable() = default;
        ~CConsumable()
        {}

        bool accept(CPlayerPaladin* paladin) override
        {
            return true;
        }
        bool accept(CPlayerMage* mage) override
        {
            return true;
        }
        bool accept(CPlayerRogue* rogue) override
        {
            return true;    
        }

    private:
        int m_healthSource;
        int m_energySource;
        int m_sideEffect;           // item could be toxic -> negative values

};

#endif