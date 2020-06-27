#ifndef ROGUE_H
#define ROGUE_H

#include "CPlayer.h"
#include "CPrimaryAttack.fwd.h"
#include "CAttack.fwd.h"
#include "CPlayerRogue.fwd.h"


class CPlayerRogue : public CPlayer
{
    public:
        int getAction() override;
        bool interactWith() override;
        void showStats() const override;
        CPlayerRogue(int posY, int posX);

        virtual ~CPlayerRogue() = default;

        const int getForce() const override;
        const float getChanceOfCriticalAttack() const override;

        virtual string getTypeName();

        void save(ofstream& os) override;

        bool updateSource(CPickup* pickup) override;
        bool acceptSource(CPickup* pickup) override;
        bool acceptTarget(CPickup* pickup) override;

        friend class CAttack;
        friend class CPickup;
        friend class CCoffee;
        friend class CApple;
        friend class CBeer;
        friend class CDagger;

    private:
        void addForce(int added) override;
        void quickJump();
        int m_agility;
        float m_chanceOfDoubleHit;
        attack_type m_primaryAttackType;
        bool roguePrimaryAttack(CGameObject* target);
};

CCharacter* loadPlayerRogue(ifstream& is);

#endif