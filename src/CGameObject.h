#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <ncurses.h>
#include "CAttack.fwd.h"
#include "CItem.fwd.h"
#include "CPickup.fwd.h"
#include "CEquip.fwd.h"   
#include "enums.h"
#include <utility>
#include <string>
#include <fstream>
#include <memory>

#define ROOM_HEIGHT 65 
#define ROOM_WIDTH 150  

using namespace std;

class CGameObject 
{
    public:
        CGameObject(int posY, int posX);
        CGameObject(int posY, int posX, const char & objectForm);
        virtual ~CGameObject() = default;

        virtual void showStats() const = 0;

        void moveUp(int & steps);
        void moveDown(int & steps);
        void moveLeft(int & steps);
        void moveRight(int & steps);
        void objectRender();

        virtual bool acceptSource(std::shared_ptr<CAttack> attack) = 0;
        virtual bool acceptTarget(std::shared_ptr<CAttack> attack) = 0;
        virtual bool updateSource(std::shared_ptr<CAttack> attack) = 0;
        virtual bool updateTarget(std::shared_ptr<CAttack> attack) = 0;

        virtual bool acceptSource(std::shared_ptr<CPickup> pickup) = 0;
        virtual bool acceptTarget(std::shared_ptr<CPickup> pickup) = 0;
        virtual bool updateSource(std::shared_ptr<CPickup> pickup) = 0;

        virtual bool acceptSource(std::shared_ptr<CEquip> equip) = 0;

        virtual bool isDead() const;
        virtual void getLabel(std::string & label) const = 0;
        std::pair<int, int> & getPos();
        virtual void save(std::ofstream & os) = 0;
        virtual string getTypeName() = 0;
    
    protected:

        int m_posY, m_posX;
        char m_objectForm;
        std::pair<int, int> pair;

};

std::shared_ptr<CGameObject> loadGameObject(ifstream& is);

#endif