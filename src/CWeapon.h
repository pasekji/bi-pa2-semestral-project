#ifndef WEAPON_H
#define WEAPON_H

#include "CItem.h"
#include "CWeapon.fwd.h"

class CWeapon : public CItem
{
    public:
        CWeapon(const std::string & name, const std::string & lable, std::size_t price, std::size_t useability, int damage, int chance_of_hit, player_class compatible) : CItem(name, lable, price, useability)
        {
            m_damage = damage;
            m_chance_of_hit = chance_of_hit;
            m_compatible = compatible;
        }

        CWeapon() = default;
        ~CWeapon()
        {}

        bool itemApply() override
        {
            return false;
        }
        
        bool is_equiped;


    protected:
        player_class m_compatible;
        int m_damage;
        float m_chance_of_hit;
};

#endif