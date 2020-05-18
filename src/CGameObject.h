#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <ncurses.h>

#define ROOM_HEIGHT 50 
#define ROOM_WIDTH 100


enum attack_type {SLAIN, KICK, SPELL, BITE};                           // todo 
enum event_type {ATTACK, TALK, ITEM_PICKUP, ITEM_DISCARD, EQUIP, DEQUIP, GOTO};


class CGameObject 
{
    public:
        CGameObject(WINDOW * objectSpace, int posY, int posX) : m_objectSpace(objectSpace), m_posY(posY), m_posX(posX)
        {
            getmaxyx(m_objectSpace, m_posY_Max, m_posX_Max);
        }
        CGameObject(WINDOW * objectSpace, int posY, int posX, char & objectForm) : m_objectSpace(objectSpace), m_posY(posY), m_posX(posX), m_objectForm(objectForm)
        {
            getmaxyx(m_objectSpace, m_posY_Max, m_posX_Max);
        }
        virtual ~CGameObject()
        {}
        virtual int getAction()
        {
            return 0;
        }
        virtual bool interactWith()
        {
            return false;
        }
        void objectRender();
        WINDOW * m_objectSpace;
        int m_posY, m_posX, m_posX_Max, m_posY_Max;
        char m_objectForm;
    
};

#endif