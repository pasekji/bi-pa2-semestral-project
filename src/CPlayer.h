#ifndef PLAYER_H
#define PLAYER_H

#include "CCharacter.h"
#include "CInventory.h"
#include "CWeapon.fwd.h"
#include "CPrimaryAttack.fwd.h"
#include "CPlayer.fwd.h"
#include "CPickup.fwd.h"
#include <map>
#include <string>
#include <ctype.h>


class CPlayer : public CCharacter
{
    public:
        CPlayer(WINDOW* objectSpace, int posY, int posX) : CCharacter(objectSpace, posY, posX)
        {
            m_posY_real = posY;
            m_posX_real = posX;
            m_objectForm = '^';
            m_speed = 1;
            m_sprint = false;
            keypad(m_objectSpace, true);
        }

        void getLabel(std::string & label) const override
        {
            label = "YOU";
            return;
        }

        ~CPlayer()
        {}

        bool acceptSource(CAttack* attack) override;

        bool acceptTarget(CAttack* attack) override;

        bool updateSource(CAttack* attack) override;

        bool updateTarget(CAttack* attack) override;

        friend class CAttack;
        friend class CPickup;
        
    protected:

        void changeForm(const char & objectForm);
        void defaultStep(int & move);
        bool defaultMove(int move) override;
        void goToInventory();

        bool itemPickup(CGameObject* target);

        CGameObject* directionGetTarget(); 

        CGameObject* fetchTarget() const override
        {
            return nullptr;
        }

        int m_posY_real, m_posX_real;
        int m_move;
        bool m_sprint;
        unsigned m_inventorySize;
        int m_currentExp = 0; 
        CInventory* m_inventory;
        CWeapon* m_weaponEquiped;

};

#endif