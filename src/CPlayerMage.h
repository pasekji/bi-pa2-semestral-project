#ifndef MAGE_H
#define MAGE_H

#include "CPlayer.h"
#include "CPrimaryAttack.fwd.h"
#include "CAttack.fwd.h"
#include "CPlayerMage.fwd.h"

class CPlayerMage : public CPlayer
{  
    public:
        int getAction() override;
        bool interactWith() override;
        void showStats() const override;
        CPlayerMage(int posY, int posX);

        virtual ~CPlayerMage() = default;

        const int getForce() const override
        {
            return m_wisdom;
        }

        const float getChanceOfCriticalAttack() const override
        {
            return m_chanceOfCriticalAttack;
        }

        virtual string getTypeName()
        {
            return "CPlayerMage";
        }

        void save(ofstream& os) override
        {
            os << getTypeName() << " ";
            os << m_posX << " ";
            os << m_posY;
            os << endl;
        }

        bool updateSource(std::shared_ptr<CPickup> pickup) override;
        bool acceptSource(std::shared_ptr<CPickup> pickup) override;
        bool acceptTarget(std::shared_ptr<CPickup> pickup) override;
        
        friend class CAttack;
        friend class CPickup;
        friend class CCoffee;
        friend class CApple;
        friend class CBeer;
        friend class CWand;


    private:

        void addForce(int added) override;
        void meditation();
        bool m_meditation = false;
        std::shared_ptr<CPlayerMage> m_sharedDerived;
        int m_wisdom;
        float m_chanceOfCriticalAttack;
        attack_type m_primaryAttackType;
        bool magePrimaryAttack(std::shared_ptr<CGameObject> target);

};

std::shared_ptr<CCharacter> loadPlayerMage(ifstream& is);

#endif