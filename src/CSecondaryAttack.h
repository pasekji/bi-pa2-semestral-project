#ifndef SECONDARY_ATTACK_H
#define SECONDARY_ATTACK_H

#include "CAttack.h"

class CSecondaryAttack : public CAttack
{
    public:
        CSecondaryAttack(CGameObject* source, CGameObject* target, attack_type attackType) : CAttack(source, target, attackType)
        {}
        ~CSecondaryAttack()
        {}

        void print() const override;
        
    protected:
        void updateObjects() override;
        void evaluateAttack() override;

        
};

#endif