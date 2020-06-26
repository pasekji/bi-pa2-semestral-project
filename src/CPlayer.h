#ifndef PLAYER_H
#define PLAYER_H

#include "CCharacter.h"
#include "CInventory.h"
#include "CWeapon.fwd.h"
#include "CPrimaryAttack.fwd.h"
#include "CPlayer.fwd.h"
#include "CPickup.fwd.h"
#include "CCoffee.h"
#include "CSword.h"
#include "CWand.h"
#include "CDagger.h"
#include "CApple.h"
#include "CBeer.h"
#include "CTooth.h"
#include <map>
#include <string>
#include <ctype.h>


class CPlayer : public CCharacter
{
    public:
        CPlayer(int posY, int posX);

        void getLabel(std::string & label) const;

        virtual ~CPlayer() = default;

        bool acceptSource(CAttack* attack) override;

        bool acceptTarget(CAttack* attack) override;

        bool acceptSource(CEquip* equip) override;
   
        bool updateSource(CAttack* attack) override;

        bool updateTarget(CAttack* attack) override;

        CPlayer* getPtr();

        friend class CAttack;
        friend class CPickup;
        friend class CCoffee;
        friend class CApple;
        friend class CBeer;
        friend class CWand;
        friend class CSword;
        friend class CDagger;
        
    protected:

        void changeForm(const char & objectForm);
        void defaultStep(int & move);
        bool defaultMove(int move) override;
        void goToInventory();
        virtual void addForce(int added) = 0;

        CPlayer* m_sharedThis;
        bool itemPickup(CGameObject* target);
        bool useItem(CItem* item);
        bool dumpItem(CItem* item);

        CGameObject* directionGetTarget(); 
        int m_posY_real, m_posX_real;
        int m_move;
        bool m_sprint;
        unsigned m_inventorySize;
        int m_currentExp = 0; 
        CInventory* m_inventory;
        CWeapon* m_weaponEquiped = nullptr;

};

#endif