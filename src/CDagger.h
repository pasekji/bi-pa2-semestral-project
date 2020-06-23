#ifndef DAGGER_H
#define DAGGER_H

#include "CWeapon.h"

class CDagger : public CWeapon
{
    public:
        CDagger() = default;
        ~CDagger()
        {}

        std::string getLabel() const override
        {
            return "DAGGER";
        }

        bool accept(CPlayerPaladin* paladin) override
        {
            return false;
        }
        
        bool accept(CPlayerMage* mage) override
        {
            return false;
        }

        bool accept(CPlayerRogue* rogue) override
        {
            return true;    
        }

};

#endif