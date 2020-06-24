#ifndef WAND_H
#define WAND_H

#include "CWeapon.h"

class CWand : public CWeapon
{
    public:
        CWand();
        virtual ~CWand() = default;

        std::string getLabel() const override;

        bool itemApply(std::shared_ptr<CPlayer> player) override;
        
    private:
        std::shared_ptr<CWand> m_sharedThis;
};

#endif