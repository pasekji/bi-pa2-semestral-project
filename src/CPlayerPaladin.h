#ifndef PALADIN_H
#define PALADIN_H

#include "CPlayer.h"

class CPlayerPaladin : public CPlayer
{  
    public:
        int getAction() override;
        bool interactWith() override;
        CPlayerPaladin(WINDOW* objectSpace, int posY, int posX) : CPlayer(objectSpace, posY, posX, PALADIN)
        {}

        ~CPlayerPaladin()
        {}

    private:
        int m_strength;
        float m_chanceOfCriticalAttack;
        attack_type m_primaryAttackType;
        bool paladinPrimaryAttack();
        bool paladinSpecialAbility();           // knockout the enemy for x rounds ?? 

};

#endif