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

        bool updateSource(std::shared_ptr<CPickup> pickup) override;
        bool acceptSource(std::shared_ptr<CPickup> pickup) override;
        bool acceptTarget(std::shared_ptr<CPickup> pickup) override;

        friend class CAttack;
        friend class CPickup;
        friend class CCoffee;
        friend class CApple;
        friend class CBeer;
        friend class CSword;

    private:
        void addForce(int added) override;
        void hide(int& move);
        std::shared_ptr<CPlayerPaladin> m_sharedDerived;
        bool interactWith() override;
        int m_strength;
        float m_chanceOfCriticalAttack;
        attack_type m_primaryAttackType;
        bool paladinPrimaryAttack(std::shared_ptr<CGameObject> target);

};

std::shared_ptr<CCharacter> loadPlayerPaladin(ifstream& is);

#endif