#ifndef MAGE_H
#define MAGE_H

#include "CPlayer.h"

class CPlayerMage : public CPlayer
{  
    public:
        int getAction() override;
        bool accept(CAttack* attack) override;
        bool interactWith() override;
        void showStats() const override;
        CPlayerMage(WINDOW* objectSpace, int posY, int posX);

        ~CPlayerMage()
        {}

    private:
        int m_wisdom;
        float m_chanceOfCriticalAttack;
        attack_type m_primaryAttackType;
        attack_type m_secondaryAttackType;
        bool magePrimaryAttack();
        bool mageSecondaryAttack();
        bool mageSpecialAbility();
};

#endif