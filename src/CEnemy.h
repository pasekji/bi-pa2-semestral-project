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
        bool acceptSource(std::shared_ptr<CPickup> pickup) override;
        bool acceptSource(std::shared_ptr<CEquip> equip) override;
        bool acceptTarget(std::shared_ptr<CPickup> pickup) override;
        bool updateSource(std::shared_ptr<CPickup> pickup) override;
        void showStats() const override;
        const float getChanceOfCriticalAttack() const override;
        const int getForce() const override;
        void triggerAttack();
        void getLabel(std::string & label) const override;
        virtual string getTypeName();
        void save(ofstream& os) override;
        std::shared_ptr<CEnemy> getPtr();
        friend class CAttack;

    private:
        int m_triggerDistance;
        bool m_triggerAttack = false;
        int m_force;
        enemy_type m_type;
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