#ifndef PALADIN_H
#define PALADIN_H

#include "CPlayer.h"
#include "CPrimaryAttack.fwd.h"
#include "CPlayerPaladin.fwd.h"
#include "CAttack.fwd.h"


class CPlayerPaladin : public CPlayer
{  
    public:
        int getAction() override;
        void showStats() const override;
        CPlayerPaladin(int posY, int posX);
        virtual ~CPlayerPaladin() = default;

        const int getForce() const override;

        const float getChanceOfCriticalAttack() const override;

        void save(ofstream& os) override;

        virtual string getTypeName();

        bool updateSource(CPickup* pickup) override;
        bool acceptSource(CPickup* pickup) override;
        bool acceptTarget(CPickup* pickup) override;

        friend class CAttack;
        friend class CPickup;
        friend class CCoffee;
        friend class CApple;
        friend class CBeer;
        friend class CSword;

    private:
        void addForce(int added) override;
        void hide(int& move);
        CPlayerPaladin* m_sharedDerived;
        bool interactWith() override;
        int m_strength;
        float m_chanceOfCriticalAttack;
        attack_type m_primaryAttackType;
        bool paladinPrimaryAttack(CGameObject* target);

};

CCharacter* loadPlayerPaladin(ifstream& is);

#endif