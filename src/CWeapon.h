#ifndef WEAPON_H
#define WEAPON_H

#include "CItem.h"
#include "CWeapon.fwd.h"

class CWeapon : public CItem
{
    public:
    
        CWeapon() = default;
        virtual ~CWeapon() = default;
        
        bool is_equiped = false;

    protected:
        player_class m_compatible;
        int m_damage = 0;
        float m_chance_of_block = 0;
};

#endif