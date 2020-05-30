#ifndef CONSUMABLE_H
#define CONSUMABLE_H

#include "CItem.h"

class CConsumable : public CItem        // could be stackable
{
    public:
        CConsumable(const std::string & name, const std::string & lable, const std::string & id, std::size_t price, std::size_t useability, int healthSource, int energySource, int sideEffect) : CItem(name, lable, price, useability)
        {
            m_healthSource = healthSource;
            m_energySource = energySource;
            m_sideEffect = sideEffect;
            m_id = id;
        }
        ~CConsumable()
        {}
        bool itemApply();
        std::string m_id;

    private:
        int m_healthSource;
        int m_energySource;
        int m_sideEffect;           // item could be toxic -> negative values

};

#endif