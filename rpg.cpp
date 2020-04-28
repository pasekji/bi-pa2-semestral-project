﻿#include <ncurses.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <locale.h>

#define ROOM_HEIGHT 50 
#define ROOM_WIDTH 100

using namespace std;

class CGame
{
    public:
        CGame() = default;
        void run();
        friend class CGameMap;
        
    private:
        void initGame();
        void endGame();
        void renderSpace();
        void spawnPlayer();
        WINDOW* m_Window;
        int m_yMax, m_xMax;
};

class CGameObject 
{
    public:
        CGameObject(WINDOW * objectSpace, int posY, int posX) : m_objectSpace(objectSpace), m_posY(posY), m_posX(posX)
        {
            getmaxyx(m_objectSpace, m_posY_Max, m_posX_Max);
        }
        virtual int getAction() = 0;
        virtual bool interactWith(CGameObject * target) = 0; 
        WINDOW * m_objectSpace;
        int m_posY, m_posX, m_posX_Max, m_posY_Max;
        char m_objectForm;
    

};


class CPlayer : public CGameObject
{
    public:
        void playerMoveUp();
        void playerMoveDown();
        void playerMoveLeft();
        void playerMoveRight();
        void playerRender();
        int getAction() override;
        bool interactWith(CGameObject *target) override;
    
        CPlayer(WINDOW* objectSpace, int posY, int posX) : CGameObject(objectSpace, posY, posX)
        {
            m_objectForm = '^';
            keypad(m_objectSpace, true);
        }

    private:
        float m_speed = 1;
};

class CNpc : public CGameObject
{
    
};

void CPlayer::playerMoveUp()
{
    mvwaddch(m_objectSpace, m_posY, m_posX, ' ');
    m_objectForm = '^';
    m_posY -= m_speed;
    if (m_posY < 1)
        m_posY = 1;
}

void CPlayer::playerMoveDown()
{
    mvwaddch(m_objectSpace, m_posY, m_posX, ' ');
    m_objectForm = 'v';
    m_posY += m_speed;
    if (m_posY > m_posY_Max - 2)                // because of the border -> border is m_posY_Max - 1, so one spot before the border is m_posY_Max - 2
        m_posY = m_posY_Max - 2;
}

void CPlayer::playerMoveLeft()
{
    mvwaddch(m_objectSpace, m_posY, m_posX, ' ');
    m_objectForm = '<';
    m_posX -= (m_speed + 1);
    if (m_posX < 1)
        m_posX = 1;
}

void CPlayer::playerMoveRight()
{
    mvwaddch(m_objectSpace, m_posY, m_posX, ' ');
    m_objectForm = '>';
    m_posX += (m_speed + 1);
    if (m_posX > m_posX_Max - 2)
        m_posX = m_posX_Max - 2;
}

int CPlayer::getAction()
{
    int move = wgetch(m_objectSpace);
    switch (move) 
    {
        case KEY_UP:
            playerMoveUp();
            break;
        case KEY_DOWN:
            playerMoveDown();
            break;
        case KEY_LEFT:
            playerMoveLeft();
            break;
        case KEY_RIGHT:
            playerMoveRight();
            break;
        default:
            break;
    }
    return move;
}

void CPlayer::playerRender()
{ 
    mvwaddch(m_objectSpace, m_posY, m_posX, m_objectForm);
}

bool CPlayer::interactWith(CGameObject * targer)
{
    //TODO
    return false;
}

void CGame::initGame() 
{
    setlocale(LC_ALL, "");

    // ncurses start and setting
    initscr();
    noecho();
    cbreak();
    curs_set(0);

    // get screen size
    getmaxyx(stdscr, m_yMax, m_xMax);
}

void CGame::run() 
{
    initGame();
    // TODO : render menu etc etc...

    // just for test 
    renderSpace();
    spawnPlayer();
}

void CGame::renderSpace() 
{
    // create a window for player
    m_Window = newwin(ROOM_HEIGHT, ROOM_WIDTH, (m_yMax - ROOM_HEIGHT) / 2, (m_xMax - ROOM_WIDTH) / 2);
    box(m_Window, 0, 0);
    refresh();
    wrefresh(m_Window);
}

void CGame::spawnPlayer()
{
    CPlayer* p = new CPlayer(m_Window, (ROOM_HEIGHT - 2) / 2, (ROOM_WIDTH - 2) / 2);
    wrefresh(m_Window);

    do
    {
        p->playerRender();
        wrefresh(m_Window);
    } while (p->getAction() != 'x');
    
    endGame();
   
}

void CGame::endGame()
{
    curs_set(0);
    refresh();
    endwin();
}

int main(int argc, char ** argv)
{
    CGame game;
    game.run();

    return 0;
}