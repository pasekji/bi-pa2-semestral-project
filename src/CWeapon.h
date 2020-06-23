#ifndef WEAPON_H
#define WEAPON_H

#include "CItem.h"
#include "CWeapon.fwd.h"

class CWeapon : public CItem
{
    public:
    
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