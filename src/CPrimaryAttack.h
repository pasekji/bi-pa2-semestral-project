#ifndef PRIMARY_ATTACK_H
#define PRIMARY_ATTACK_H

#include "CAttack.h"
#include "CPrimaryAttack.fwd.h"

class CPrimaryAttack : public CAttack
{
    public:
        CPrimaryAttack(std::shared_ptr<CGameObject> source, std::shared_ptr<CGameObject> target, attack_type attackType);
        virtual ~CPrimaryAttack() = default;

        std::shared_ptr<CPrimaryAttack> getPtr();
        
    protected:
        std::shared_ptr<CPrimaryAttack> m_sharedThis;
        void updateObjects() override;
        void evaluateAttack() override;
        void print() override;
};

#endif