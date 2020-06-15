#ifndef PRIMARY_ATTACK_H
#define PRIMARY_ATTACK_H

#include "CAttack.h"

class CPrimaryAttack : public CAttack
{
    public:
        CPrimaryAttack(CGameObject* source, CGameObject* target, attack_type attackType);
        ~CPrimaryAttack();

        void print() const override;

    protected:
        void updateObjects() override;
        void evaluateAttack() override;
};

#endif