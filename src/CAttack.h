#ifndef ATTACK_H
#define ATTACK_H

#include "CEvent.h"
#include "CAttack.fwd.h"
#include "CPlayerPaladin.h"
#include "CPlayerRogue.h"
#include "CPlayerMage.h"
#include "CEnemy.h"

class CAttack : public CEvent
{
    public:
        CAttack(CGameObject* source, CGameObject* target, attack_type attackType) : CEvent(source, target)
        {}
        ~CAttack()
        {}

        void visit(CPlayerPaladin* paladin);
        void visit(CPlayerMage* mage);
        void visit(CPlayerRogue* rogue);
        void visit(CEnemy* enemy);

    protected:
        virtual void evaluateAttack() = 0;
        attack_type m_attackType;
        int m_force;
        int m_healthLost;
        bool m_hit;
};

#endif