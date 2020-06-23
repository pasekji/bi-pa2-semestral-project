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

class CEnemy : public CCharacter
{
    public:
        CEnemy(WINDOW* objectSpace, int posY, int posX, enemy_type type);
        ~CEnemy()
        {}

        CEnemy(WINDOW* objectSpace, int posY, int posX);
        int getAction() override;
        bool acceptSource(CAttack* attack) override;
        bool acceptTarget(CAttack* attack) override;
        bool updateSource(CAttack* attack) override;
        bool updateTarget(CAttack* attack) override;
        bool acceptSource(CPickup* pickup) override
        {
            return false;
        }
        bool acceptTarget(CPickup* pickup) override
        {
            return false;
        }
        bool updateSource(CPickup* pickup) override
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
            os << getTypeName();
            os << m_triggerDistance;
            os << m_triggerAttack;
            os << (int)m_type;
            os << m_force;
            os << (int)m_primaryAttackType;
            os << m_posX;
            os << m_posY;
            os << endl;
        }

        friend class CAttack;

    private:
        int m_triggerDistance;
        bool m_triggerAttack = false;
        enemy_type m_type;
        int m_force;
        attack_type m_primaryAttackType;
        CLoot* m_loot = nullptr;                            // will generate loot chest after death
        float m_chanceOfAttack;
        bool interactWith() override;
        bool primaryAttack(CGameObject* target);
        bool defaultMove(int move) override;

        CGameObject* fetchTarget() const override
        {
            return nullptr;
        }

        void playerNearby(direction & move);
        void die();

        const float getDistance(std::pair<int, int> & thisPos, std::pair<int, int> & playerPos) const;
        void findPath(std::pair<int, int> & thisPos, std::pair<int, int> & playerPos, direction & move) const;

};

CGameObject* loadEnemy(ifstream& is, WINDOW* objectSpace);

#endif