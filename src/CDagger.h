#ifndef DAGGER_H
#define DAGGER_H

#include "CWeapon.h"

class CDagger : public CWeapon
{
    public:
        CDagger();
        virtual ~CDagger() = default;

        std::string getLabel() const override;

        bool itemApply(std::shared_ptr<CPlayer> player) override;

    private:
        std::shared_ptr<CDagger> m_sharedThis;
};

#endif