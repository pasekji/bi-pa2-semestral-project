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

        void visitSource(CPlayerPaladin* paladin);
        void visitSource(CPlayerMage* mage);
        void visitSource(CPlayerRogue* rogue);
        void visitSource(CEnemy* enemy);

        void visitTarget(CPlayerPaladin* paladin);
        void visitTarget(CPlayerMage* mage);
        void visitTarget(CPlayerRogue* rogue);
        void visitTarget(CEnemy* enemy);

    protected:
        virtual void evaluateAttack() = 0;
        attack_type m_attackType;
        std::string m_sourceLable;
        std::string m_targetLable;
        float m_chanceOfBlockTarget;
        float m_chanceOfCritical;
        int m_forceMax;
        int m_healthTarget;
        int m_energySource;
        int m_energyTarget;

        int m_forceGiven;
        int m_healthLostTarget;
        int m_energyLostTarget;
        int m_energyLostSource;
        int m_expGain;
        bool m_hit;
        bool m_criticalHit;
        bool m_canAttack;       // pokud false v evaluate se vypíše static hláška, "You cant attack that!"
};

#endif