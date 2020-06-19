#ifndef MAGE_H
#define MAGE_H

#include "CPlayer.h"

class CPlayerMage : public CPlayer
{  
    public:
        int getAction() override;
        bool acceptSource(CAttack* attack) override;
        bool acceptTarget(CAttack* attack) override;
        bool interactWith() override;
        void showStats() const override;
        CPlayerMage(WINDOW* objectSpace, int posY, int posX);

        ~CPlayerMage()
        {}

        const int getForce() const override
        {
            return m_wisdom;
        }

        const float getChanceOfCriticalAttack() const override
        {
            return m_chanceOfCriticalAttack;
        }

        virtual string getTypeName()
        {
            return "CPlayerMage";
        }

        void save(ofstream& os) override
        {
            os << getTypeName() << endl;
        }

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