#ifndef WAND_H
#define WAND_H

#include "CWeapon.h"

class CWand : public CWeapon
{
    public:
        CWand() = default;
        ~CWand()
        {}

        std::string getLabel() const override
        {
            return "WAND";
        }

        bool accept(CPlayerPaladin* paladin) override
        {
            return false;
        }
        
        bool accept(CPlayerMage* mage) override
        {
            return true;
        }

        bool accept(CPlayerRogue* rogue) override
        {
            return false;    
        }

};

#endif