#ifndef ENEMY_H
#define ENEMY_H

#include "CCharacter.h"
#include "CLoot.h"
#include "enums.h"
#include "CPrimaryAttack.fwd.h"
#include "CAttack.fwd.h"
#include <math.h>
#include <random>
#include <ctime>
#include <memory>

class CEnemy : public CCharacter
{
    public:
        CEnemy(int posY, int posX, enemy_type type);
        virtual ~CEnemy() = default;

        CEnemy(int posY, int posX);
        int getAction() override;
        bool acceptSource(std::shared_ptr<CAttack> attack) override;
        bool acceptTarget(std::shared_ptr<CAttack> attack) override;
        bool updateSource(std::shared_ptr<CAttack> attack) override;
        bool updateTarget(std::shared_ptr<CAttack> attack) override;
        bool acceptSource(std::shared_ptr<CPickup> pickup) override
        {
            return false;
        }

        bool acceptSource(std::shared_ptr<CEquip> equip) override
        {
            return false;
        }

        bool acceptTarget(std::shared_ptr<CPickup> pickup) override
        {
            return false;
        }
        bool updateSource(std::shared_ptr<CPickup> pickup) override
        {
            return false;
        }
        void showStats() const override;

        const float getChanceOfCriticalAttack() const override
        {
            return m_chanceOfAttack;
        }

        const int getForce() const override
        {
            return m_force;
        }

        void triggerAttack()
        {
            m_triggerAttack = true;
        }

        void getLabel(std::string & label) const override
        {
            switch (m_type)
            {
                case BASILISK:
                    label = "BASILISK";
                    break;
                case UNDEAD:
                    label = "UNDEAD";
                    break;
                case GHOUL:
                    label = "GHOUL";
                    break;
                case HELLHOUND:
                    label = "HELLHOUND";
                    break;
                case NOONWRAITH:
                    label = "NOONWRAITH";
                    break;
                case SIREN:
                    label = "SIREN";
                default:
                    break;
            }
        }

        virtual string getTypeName()
        {
            return "CEnemy";
        }

        void save(ofstream& os) override
        {
            if(isDead())
                 os << "neukladat" << endl;
            os << getTypeName() << " ";
            //os << m_triggerDistance;
            //os << m_triggerAttack;
            os << (int)m_type << " ";
            //os << m_force;
            //os << (int)m_primaryAttackType;
            os << m_posX << " ";
            os << m_posY;
            os << endl;
        }

        std::shared_ptr<CEnemy> getPtr()
        {
            return m_sharedThis;
        }

        friend class CAttack;

    private:
        int m_triggerDistance;
        bool m_triggerAttack = false;
        enemy_type m_type;
        int m_force;
        attack_type m_primaryAttackType;
        std::shared_ptr<CLoot> m_loot = nullptr;                            // will generate loot chest after death
        float m_chanceOfAttack;
        bool interactWith() override;
        bool primaryAttack(std::shared_ptr<CGameObject> target);
        bool defaultMove(int move) override;
        std::shared_ptr<CEnemy> m_sharedThis;

        void playerNearby(direction & move);
        void die();

        const float getDistance(std::pair<int, int> & thisPos, std::pair<int, int> & playerPos) const;
        void findPath(std::pair<int, int> & thisPos, std::pair<int, int> & playerPos, direction & move) const;

};

std::shared_ptr<CCharacter> loadEnemy(ifstream& is);

#endif