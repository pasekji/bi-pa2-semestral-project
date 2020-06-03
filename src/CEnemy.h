#ifndef ENEMY_H
#define ENEMY_H

#include "CCharacter.h"
#include "CChest.h"


class CEnemy : public CCharacter
{
    public:
        void enemyDead();
        int getAction() override;
        bool interactWith() override;

        CEnemy(WINDOW* objectSpace, int posY, int posX, enemy_type type);

        ~CEnemy()
        {}

    private:
        enemy_type m_type;
        int m_force;
        attack_type m_primaryAttackType;
        CChest * m_loot;                            // will generate loot chest after death
        bool primaryAttack();

};

#endif