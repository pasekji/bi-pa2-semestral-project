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

        bool acceptSource(std::shared_ptr<CAttack> attack) override;

        bool acceptTarget(std::shared_ptr<CAttack> attack) override;

        bool acceptSource(std::shared_ptr<CEquip> equip) override;
   
        bool updateSource(std::shared_ptr<CAttack> attack) override;

        bool updateTarget(std::shared_ptr<CAttack> attack) override;

        std::shared_ptr<CPlayer> getPtr();

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

        std::shared_ptr<CPlayer> m_sharedThis;
        bool itemPickup(std::shared_ptr<CGameObject> target);
        bool useItem(std::shared_ptr<CItem> item);
        bool dumpItem(std::shared_ptr<CItem> item);

        std::shared_ptr<CGameObject> directionGetTarget(); 
        int m_posY_real, m_posX_real;
        int m_move;
        bool m_sprint;
        unsigned m_inventorySize;
        int m_currentExp = 0; 
        std::shared_ptr<CInventory> m_inventory;
        std::shared_ptr<CWeapon> m_weaponEquiped = nullptr;

};

#endif