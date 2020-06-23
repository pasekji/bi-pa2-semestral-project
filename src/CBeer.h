#ifndef BEER_H
#define BEER_H

#include "CConsumable.h"

class CBeer : public CConsumable
{
    public:
        CBeer() = default;
        ~CBeer()
        {}

        std::string getLabel() const override
        {
            return "BEER";
        }

        bool itemApply() override
        {
            return false;
        }

};

#endif