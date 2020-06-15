#ifndef PLAYER_H
#define PLAYER_H

#include "CCharacter.h"
#include "CInventory.h"
#include "CArmor.h"
#include "CWeapon.h"
#include <map>
#include <string>

class CPlayer : public CCharacter
{
    public:
        void changeForm(const char & objectForm);
        void defaultStep(int & move);
        bool defaultMove(int & move);

        CPlayer(WINDOW* objectSpace, int posY, int posX) : CCharacter(objectSpace, posY, posX)
        {
            m_posY_real = posY;
            m_posX_real = posX;
            m_objectForm = '^';
            m_speed = 1;
            m_sprint = false;
            keypad(m_objectSpace, true);
        }

        ~CPlayer()
        {}

    protected:
        int m_posY_real, m_posX_real;
        int m_move;
        bool m_sprint;
        int m_inventorySize;
        int m_level = 1;
        int m_currentExp = 0; 
        int m_expTarget = 20;
        std::string m_playerName;
        CInventory* m_inventory;
        std::map<body_part, CArmor*> m_armor;
        std::pair<CWeapon*, CWeapon*> m_weapon;

};

#endif