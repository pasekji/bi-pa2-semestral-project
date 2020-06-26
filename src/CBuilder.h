#ifndef BUILDER_H
#define BUILDER_H

#include "CPlayer.h"

class CBuilder : public CPlayer
{  
    public:
        CBuilder(int posY, int posX);
        int getAction() override;
        bool interactWith() override;
        void showStats() const override;

        virtual ~CBuilder() = default;

        virtual string getTypeName() const;

        bool updateSource(CPickup* pickup) override
        {
            return false;
        }

        bool acceptSource(CPickup* pickup) override
        {
            return false;
        }

        bool acceptTarget(CPickup* pickup) override
        {
            return false;
        }

        const int getForce() const override
        {
            return 0;
        }

        const float getChanceOfCriticalAttack() const override
        {
            return 0;
        }


        void save(ofstream& os) override
        {
            os << getTypeName() << " ";
            os << m_posX << " ";
            os << m_posY;
            os << endl;
        }

    private:
        void addForce(int added) override
        {
            return;
        }

        bool spawnSomething(std::pair<int, int> position);

};

#endif