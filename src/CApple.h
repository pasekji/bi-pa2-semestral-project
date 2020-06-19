#ifndef APPLE_H
#define APPLE_H

#include "CConsumable.h"

class CApple : public CConsumable
{
    public:
        CApple() : CConsumable()
        {
        }
        ~CApple()
        {}

        bool itemApply() override
        {
            return false;
        }

};

#endif