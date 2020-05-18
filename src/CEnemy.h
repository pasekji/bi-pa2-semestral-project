#ifndef ENEMY_H
#define ENEMY_H

#include "CCharacter.h"
#include "CChest.h"


class CEnemy : public CCharacter
{
    public:
        enemy_type m_type;
        void enemyDead();
        int getAction() override;
        bool interactWith() override;

        // enemy demo testing constructor
        CEnemy(WINDOW* objectSpace, int posY, int posX, enemy_type type) : CCharacter(objectSpace, posY, posX)
        {
            switch (type)
            {
                case BASILISK:
                    m_objectForm = '~';
                    m_type = BASILISK;
                    break;
                case UNDEAD:
                    m_objectForm = 'F';
                    m_type = UNDEAD;
                    break;
                case GHOUL:
                    m_objectForm = 'G';
                    m_type = GHOUL;
                case HELLHOUND:
                    m_objectForm = 'E';
                    m_type = HELLHOUND;
                case DRYAD:
                    m_objectForm = 'Y';
                    m_type = DRYAD;
                case SIREN:
                    m_objectForm = '%';
                    m_type = SIREN;
                default:
                    break;
            }
            m_speed = 1;
        }

        ~CEnemy()
        {}

    private:
        int m_force;
        attack_type m_primaryAttackType;
        CChest * m_loot;                            // will generate loot chest after death
        bool primaryAttack();

};

#endif