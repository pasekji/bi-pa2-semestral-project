#ifndef SWORD_H
#define SWORD_H

#include "CWeapon.h"

class CSword : public CWeapon
{
    public:
        CSword();
        virtual ~CSword() = default;

        std::string getLabel() const override;

        bool itemApply(std::shared_ptr<CPlayer> player) override;

    private:
        std::shared_ptr<CSword> m_sharedThis;

};

#endif