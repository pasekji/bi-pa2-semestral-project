#ifndef WAND_H
#define WAND_H

#include "CWeapon.h"

class CWand : public CWeapon
{
    public:
        CWand();
        virtual ~CWand() = default;

        std::string getLabel() const override;

        bool itemApply(CPlayer* player) override;
        
    private:
        CWand* m_sharedThis;
};

#endif