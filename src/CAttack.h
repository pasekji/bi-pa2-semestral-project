#ifndef ATTACK_H
#define ATTACK_H

#include "CEvent.h"
#include "enums.h"

class CAttack : public CEvent
{
    public:
        CAttack(CGameObject* source, CGameObject* target, attack_type attackType) : CEvent(source, target)
        {}
        ~CAttack()
        {}
        void print() const override;
        void updateObjects() override;

    private:
        attack_type m_attackType;
        int m_force;
        int m_healthLost;
        bool m_hit;
};

#endif