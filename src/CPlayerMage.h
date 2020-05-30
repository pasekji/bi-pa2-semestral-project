#ifndef MAGE_H
#define MAGE_H

#include "CPlayer.h"

class CPlayerMage : public CPlayer
{  
    public:
        int getAction() override;
        bool interactWith() override;
        CPlayerMage(WINDOW* objectSpace, int posY, int posX) : CPlayer(objectSpace, posY, posX)
        {
            m_inventorySize = 15;
            m_inventory = new CInventory(m_inventorySize);
        }

        ~CPlayerMage()
        {}

    private:
        int m_mana;
        float m_chanceOfCriticalAttack;
        attack_type m_primaryAttackType;
        attack_type m_secondaryAttackType;
        bool magePrimaryAttack();
        bool mageSecondaryAttack();
        bool mageSpecialAbility();
};

#endif