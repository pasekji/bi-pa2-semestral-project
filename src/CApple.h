#ifndef APPLE_H
#define APPLE_H

#include "CConsumable.h"

class CApple : public CConsumable
{
    public:
        CApple() = default;
        ~CApple()
        {}

        std::string getLabel() const override
        {
            return "APPLE";
        }

        bool itemApply() override
        {
            return false;
        }

};

#endif