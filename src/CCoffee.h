#ifndef COFFEE_H
#define COFFEE_H

#include "CConsumable.h"

class CCoffee : public CConsumable
{
    public:
        CCoffee() = default;
        ~CCoffee()
        {}

        std::string getLabel() const override
        {
            return "COFFEE";
        }

        bool itemApply() override
        {
            return false;
        }

};

#endif