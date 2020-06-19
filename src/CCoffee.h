#ifndef COFFEE_H
#define COFFEE_H

#include "CConsumable.h"

class CCoffee : public CConsumable
{
    public:
        CCoffee() : CConsumable()
        {
        }
        ~CCoffee()
        {}

        bool itemApply() override
        {
            return false;
        }

};

#endif