#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <ncurses.h>
#include <utility>

#define ROOM_HEIGHT 65 
#define ROOM_WIDTH 150  


class CGameObject 
{
    public:
        CGameObject(WINDOW * objectSpace, int posY, int posX);
        CGameObject(WINDOW * objectSpace, int posY, int posX, const char & objectForm);
        virtual ~CGameObject()
        {}

        virtual bool interactWith() = 0;

        void moveUp(int & steps);
        void moveDown(int & steps);
        void moveLeft(int & steps);
        void moveRight(int & steps);
        void objectRender();

        std::pair<int, int> & getPos();
        WINDOW * m_objectSpace;
    
    protected:
        int m_posY, m_posX, m_posX_Max, m_posY_Max;
        char m_objectForm;
        std::pair<int, int> pair;

};

#endif