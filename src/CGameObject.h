#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <ncurses.h>

#define ROOM_HEIGHT 65 
#define ROOM_WIDTH 150  

enum attack_type {SLAIN, KICK, SPELL, BITE};                           // todo 
enum event_type {ATTACK, TALK, ITEM_PICKUP, ITEM_DISCARD, EQUIP, DEQUIP, GOTO};


class CGameObject 
{
    public:
        CGameObject(WINDOW * objectSpace, int posY, int posX);
        CGameObject(WINDOW * objectSpace, int posY, int posX, char & objectForm);
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
        void cameraUp();
        void cameraDown();
        void cameraLeft();
        void cameraRight();
        void objectRender();
        WINDOW * m_objectSpace;
        int m_posY, m_posX, m_posX_Max, m_posY_Max;
        char m_objectForm;
    
};

#endif