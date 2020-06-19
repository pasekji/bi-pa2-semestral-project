#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <ncurses.h>
#include "CAttack.fwd.h"
#include "CItem.fwd.h"
#include "enums.h"
#include <utility>
#include <string>
#include <fstream>

#define ROOM_HEIGHT 65 
#define ROOM_WIDTH 150  

using namespace std;

class CGameObject 
{
    public:
        CGameObject(WINDOW * objectSpace, int posY, int posX);
        CGameObject(WINDOW * objectSpace, int posY, int posX, const char & objectForm);
        virtual ~CGameObject()
        {}

        virtual void showStats() const = 0;

        void moveUp(int & steps);
        void moveDown(int & steps);
        void moveLeft(int & steps);
        void moveRight(int & steps);
        void objectRender();

        virtual bool acceptSource(CAttack* attack) = 0;
        virtual bool acceptTarget(CAttack* attack) = 0;
        virtual void getLable(std::string & lable) const = 0;
        std::pair<int, int> & getPos();
        WINDOW * m_objectSpace;
        virtual void save(std::ofstream & os) = 0;
        virtual string getTypeName() = 0;
    
    protected:
        int m_posY, m_posX;
        char m_objectForm;
        std::pair<int, int> pair;

};

CGameObject* loadGameObject(ifstream& is);

#endif