#ifndef MISC_H
#define MISC_H

#include "CItem.h"

class CMisc : public CItem          // could be stackable
{
    public:

        CMisc() = default;
        
        virtual ~CMisc() = default;
        
        bool itemApply(std::shared_ptr<CPlayer> player);
};

#endif