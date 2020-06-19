#ifndef BEER_H
#define BEER_H

#include "CConsumable.h"

class CBeer : public CConsumable
{
    public:
        CBeer() : CConsumable()
        {
        }
        ~CBeer()
        {}

        bool itemApply() override
        {
            return false;
        }

};

#endif