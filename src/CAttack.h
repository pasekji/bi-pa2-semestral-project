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
        CAttack(CGameObject* source, CGameObject* target, attack_type attackType);
        virtual ~CAttack() = default;

        void visitSource(CPlayer* player);
        void visitSource(CEnemy* enemy);

        void visitTarget(CPlayer* player);
        void visitTarget(CEnemy* enemy);

        void updateSource(CPlayer* player);
        void updateSource(CEnemy* enemy);

        void updateTarget(CPlayer* player);
        void updateTarget(CEnemy* enemy);

    protected:
        virtual void evaluateAttack() = 0;
        attack_type m_attackType;
        float m_chanceOfBlockTarget = 0;
        float m_chanceOfCritical = 0;
        int m_forceMax = 0;
        int m_healthTarget = 0;
        int m_energySource = 0;
        int m_energyTarget = 0;
        bool m_targetReachable = false;

        int m_forceGiven = 0;
        int m_healthLostTarget = 0;
        int m_energyLostTarget = 0;
        int m_energyLostSource = 0;
        int m_expGain = 0;
        bool m_hit = false;
        bool m_criticalHit = false;
        bool m_canAttack = false;
        bool m_targetDead = false;
};

#endif