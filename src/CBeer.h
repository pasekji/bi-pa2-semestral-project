#ifndef BEER_H
#define BEER_H

#include "CConsumable.h"

class CBeer : public CConsumable
{
    public:
        CBeer();
        virtual ~CBeer() = default;

        std::string getLabel() const override;

        bool itemApply(std::shared_ptr<CPlayer> player) override;

    private:
        int m_energyForStepAdd = 3;
};

#endif