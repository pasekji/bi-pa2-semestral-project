#ifndef ROGUE_H
#define ROGUE_H

#include "CPlayer.h"

class CPlayerRogue : public CPlayer
{
    public:
        int getAction() override;
        bool interactWith() override;
        bool accept(CAttack* attack) override;
        void showStats() const override;
        CPlayerRogue(WINDOW* objectSpace, int posY, int posX);

        ~CPlayerRogue()
        {}
    
    private:
        int m_agility;
        float m_chanceOfDoubleHit;
        attack_type m_primaryAttackType;
        bool roguePrimaryAttack();
        void rogueSpecialAbility();     // jump over x spaces in direction of player
};

#endif