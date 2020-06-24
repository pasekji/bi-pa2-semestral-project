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

        const int getForce() const override
        {
            return m_agility;
        }

        const float getChanceOfCriticalAttack() const override
        {
            return m_chanceOfDoubleHit;
        }

        virtual string getTypeName()
        {
            return "CPlayerRogue";
        }

        void save(ofstream& os) override
        {
            os << getTypeName() << endl;
        }

        bool updateSource(std::shared_ptr<CPickup> pickup) override;
        bool acceptSource(std::shared_ptr<CPickup> pickup) override;
        bool acceptTarget(std::shared_ptr<CPickup> pickup) override;

        friend class CAttack;
        friend class CPickup;
        friend class CCoffee;
        friend class CApple;
        friend class CBeer;
        friend class CDagger;

    private:
        void addForce(int added) override
        {
            m_agility += added;
        }

        void quickJump();
        std::shared_ptr<CPlayerRogue> m_sharedDerived;
        int m_agility;
        float m_chanceOfDoubleHit;
        attack_type m_primaryAttackType;
        bool roguePrimaryAttack(std::shared_ptr<CGameObject> target);
};

#endif