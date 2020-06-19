#ifndef PLAYER_H
#define PLAYER_H

#include "CCharacter.h"
#include "CInventory.h"
#include "CWeapon.fwd.h"
#include <map>
#include <string>

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
            m_playerName = "jirik";
            keypad(m_objectSpace, true);
        }

        void getLable(std::string & lable) const override
        {
            lable = "you";
            return;
        }

        ~CPlayer()
        {}

        virtual const float getChanceOfCriticalAttack() const = 0;

    protected:

        void changeForm(const char & objectForm);
        void defaultStep(int & move);
        bool defaultMove(int move) override;
        void goToInventory();

        CGameObject* fetchTarget() const override
        {
            return nullptr;
        }

        void die() override
        {
            return;
        }

        int m_posY_real, m_posX_real;
        int m_move;
        bool m_sprint;
        int m_inventorySize;
        int m_level = 1;
        int m_currentExp = 0; 
        int m_expTarget = 20;
        std::string m_playerName;
        CInventory* m_inventory;
        CWeapon* m_weaponEquiped;

};

#endif