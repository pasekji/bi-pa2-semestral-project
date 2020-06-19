#ifndef MISC_H
#define MISC_H

#include "CItem.h"

class CMisc : public CItem          // could be stackable
{
    public:
        CMisc(const std::string & name, const std::string & lable, std::size_t price) : CItem(name, lable, price, 0)
        {
        }

        CMisc() = default;
        
        ~CMisc()
        {}
        bool itemApply()            // these items can't be applied f.e. - bone 
        {
            return false;
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
            return false;    
        }

};

#endif