#ifndef CONSUMABLE_H
#define CONSUMABLE_H

#include "CItem.h"
#include <memory>

class CConsumable : public CItem        // could be stackable
{
    public:
        CConsumable() = default;
        virtual ~CConsumable() = default;

    protected:
        int m_healthSource = 0;
        int m_energySource = 0;

};

#endif