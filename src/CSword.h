#ifndef SWORD_H
#define SWORD_H

#include "CWeapon.h"

class CSword : public CWeapon
{
    public:
        CSword();
        virtual ~CSword() = default;

        std::string getLabel() const override;

        bool itemApply(CPlayer* player) override;

    private:
        CSword* m_sharedThis;

};

#endif