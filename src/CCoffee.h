#ifndef COFFEE_H
#define COFFEE_H

#include "CConsumable.h"

class CCoffee : public CConsumable
{
    public:
        CCoffee();
        virtual ~CCoffee() = default;

        std::string getLabel() const override;

        bool itemApply(std::shared_ptr<CPlayer> player) override;
    
    private:
        int m_energyRegainAdd = 3;

};

#endif