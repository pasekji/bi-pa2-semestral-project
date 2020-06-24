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

        const int getForce() const override
        {
            return m_strength;
        }

        const float getChanceOfCriticalAttack() const override
        {
            return m_chanceOfCriticalAttack;
        }

        void save(ofstream& os) override
        {
            os << getTypeName() << endl;
        }

        virtual string getTypeName()
        {
            return "CPlayerPaladin";
        }

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
        void addForce(int added) override
        {
            m_strength += added;
        }

        void slowTime(int& move);
        std::shared_ptr<CPlayerPaladin> m_sharedDerived;
        bool interactWith() override;
        int m_strength;
        float m_chanceOfCriticalAttack;
        attack_type m_primaryAttackType;
        bool paladinPrimaryAttack(std::shared_ptr<CGameObject> target);
        bool paladinSpecialAbility();                       // knockout the enemy for x rounds ?? 

};

#endif