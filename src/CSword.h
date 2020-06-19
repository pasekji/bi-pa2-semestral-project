#ifndef SWORD_H
#define SWORD_H

#include "CWeapon.h"

class CSword : public CWeapon
{
    public:
        CSword() : CWeapon()
        {
        }
        ~CSword()
        {}

        bool accept(CPlayerPaladin* paladin) override
        {
            return true;
        }
        
        bool accept(CPlayerMage* mage) override
        {
            return false;
        }

        bool accept(CPlayerRogue* rogue) override
        {
            return false;    
        }

};

#endif