#ifndef PRIMARY_ATTACK_H
#define PRIMARY_ATTACK_H

#include "CAttack.h"
#include "CPrimaryAttack.fwd.h"

class CPrimaryAttack : public CAttack
{
    public:
        CPrimaryAttack(CGameObject* source, CGameObject* target, attack_type attackType);
        virtual ~CPrimaryAttack() = default;

        CPrimaryAttack* getPtr();
        
    protected:
        void updateObjects() override;
        void evaluateAttack() override;
        void print() override;
};

#endif