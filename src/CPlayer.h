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
        player_class m_class;
        CInventory* m_inventory;
        std::map<body_part, CArmor*> m_armor;
        std::pair<CWeapon*, CWeapon*> m_weapon;
        void changeForm(const char& objectForm);
        
        CPlayer(WINDOW* objectSpace, int posY, int posX, player_class playerClass) : CCharacter(objectSpace, posY, posX)
        {
            m_objectForm = '^';
            m_speed = 1;
            m_class = playerClass;

            switch (playerClass)
            {
                case PALADIN:
                    m_inventorySize = 20;
                    break;
                case MAGE:
                    m_inventorySize = 15;
                    break;
                case ROGUE:
                    m_inventorySize = 10;
                    break;
                default:
                    break;
            }
            m_inventory = new CInventory(m_inventorySize);
            keypad(m_objectSpace, true);
        }

        ~CPlayer()
        {}

    protected:
        size_t m_inventorySize;
        std::string m_playerName;

};

#endif