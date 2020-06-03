#ifndef ROGUE_H
#define ROGUE_H

#include "CPlayer.h"

class CPlayerRogue : public CPlayer
{
    public:
        int getAction() override;
        bool interactWith() override;
        CPlayerRogue(WINDOW* objectSpace, int posY, int posX) : CPlayer(objectSpace, posY, posX)
        {
            m_inventorySize = 10;
            m_inventory = new CInventory(m_inventorySize);
        }

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