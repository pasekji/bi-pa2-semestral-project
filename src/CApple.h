#ifndef APPLE_H
#define APPLE_H

#include "CConsumable.h"

class CApple : public CConsumable
{
    public:
        CApple();
        
        virtual ~CApple() = default;

        std::string getLabel() const override;

        bool itemApply(std::shared_ptr<CPlayer> player) override;
        
};

#endif