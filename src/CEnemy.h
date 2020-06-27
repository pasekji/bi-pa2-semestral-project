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
        bool acceptSource(CAttack* attack) override;
        bool acceptTarget(CAttack* attack) override;
        bool updateSource(CAttack* attack) override;
        bool updateTarget(CAttack* attack) override;
        bool acceptSource(CPickup* pickup) override;
        bool acceptSource(CEquip* equip) override;
        bool acceptTarget(CPickup* pickup) override;
        bool updateSource(CPickup* pickup) override;
        void showStats() const override;
        const float getChanceOfCriticalAttack() const override;
        const int getForce() const override;
        void triggerAttack();
        void getLabel(std::string & label) const override;
        virtual string getTypeName();
        void save(ofstream& os) override;
        CEnemy* getPtr();
        friend class CAttack;

    private:
        int m_triggerDistance;
        bool m_triggerAttack = false;
        int m_force;
        enemy_type m_type;
        attack_type m_primaryAttackType;
        CLoot* m_loot = nullptr;                            // will generate loot chest after death
        float m_chanceOfAttack;
        bool interactWith() override;
        bool primaryAttack(CGameObject* target);
        bool defaultMove(int move) override;

        void playerNearby(direction & move);
        void die();

        const float getDistance(std::pair<int, int> & thisPos, std::pair<int, int> & playerPos) const;
        void findPath(std::pair<int, int> & thisPos, std::pair<int, int> & playerPos, direction & move) const;

};

CCharacter* loadEnemy(ifstream& is);

#endif