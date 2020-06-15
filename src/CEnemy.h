#ifndef ENEMY_H
#define ENEMY_H

#include "CCharacter.h"
#include "CChest.h"
#include "enums.h"
#include <math.h>

class CEnemy : public CCharacter
{
    public:
        CEnemy(WINDOW* objectSpace, int posY, int posX, enemy_type type);
        ~CEnemy()
        {}
        void enemyDead();
        int getAction() override;
        bool interactWith() override;
        bool accept(CAttack* attack) override;
        void showStats() const override;

    private:
        int m_triggerDistance;
        enemy_type m_type;
        int m_force;
        attack_type m_primaryAttackType;
        CChest* m_loot;                            // will generate loot chest after death
        bool primaryAttack();

        const float getDistance(std::pair<int, int> & thisPos, std::pair<int, int> & playerPos) const;
        void findPath(std::pair<int, int> & thisPos, std::pair<int, int> & playerPos, direction & move) const;

};

#endif