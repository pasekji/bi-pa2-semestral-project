#ifndef ENEMY_H
#define ENEMY_H

#include "CCharacter.h"
#include "CLoot.h"
#include "enums.h"
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
        void showStats() const override;

        const int getForce() const override
        {
            return m_force;
        }

        void triggerAttack()
        {
            m_triggerAttack = true;
        }

        void getLable(std::string & lable) const override
        {
            switch (m_type)
            {
                case BASILISK:
                    lable = "BASILISK";
                    break;
                case UNDEAD:
                    lable = "UNDEAD";
                    break;
                case GHOUL:
                    lable = "GHOUL";
                    break;
                case HELLHOUND:
                    lable = "HELLHOUND";
                    break;
                case NOONWRAITH:
                    lable = "NOONWRAITH";
                    break;
                case SIREN:
                    lable = "SIREN";
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
            writeString(os, getTypeName());
            os << m_triggerDistance;
            os << m_triggerAttack;
            os << (int)m_type;
            os << m_force;
            os << (int)m_primaryAttackType;
        }

    private:
        int m_triggerDistance;
        bool m_triggerAttack = false;
        enemy_type m_type;
        int m_force;
        attack_type m_primaryAttackType;
        CLoot* m_loot;                            // will generate loot chest after death
        bool interactWith() override;
        bool primaryAttack();
        bool defaultMove(int move) override;

        CGameObject* fetchTarget() const override
        {
            return nullptr;
        }

        void playerNearby(direction & move);
        void die() override
        {
            return;
        }

        const float getDistance(std::pair<int, int> & thisPos, std::pair<int, int> & playerPos) const;
        void findPath(std::pair<int, int> & thisPos, std::pair<int, int> & playerPos, direction & move) const;

};

CGameObject* loadEnemy(ifstream& is);

#endif