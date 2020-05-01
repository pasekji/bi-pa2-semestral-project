#include <ncurses.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <locale.h>

#define ROOM_HEIGHT 50 
#define ROOM_WIDTH 100

using namespace std;


class CInput
{
    public:
        CInput(WINDOW * window) : m_mainWindow(window)
        {}
        WINDOW* m_mainWindow; 
        int readInput()
        {
            latestInput = wgetch(m_mainWindow);
            return latestInput;
        }
        int latestInput;
};

class CGame
{
    public:
        CGame() = default;
        void run();
        CInput * getInput()
        {
            return m_Input;
        }
        WINDOW* m_Window;

    private:
        void initGame();
        void endGame();
        void renderSpace();
        void spawnPlayer();
        void spawnEnemy();
        CInput* m_Input;
        int m_yMax, m_xMax;
};

CGame game;

class CGameObject 
{
    public:
        CGameObject(WINDOW * objectSpace, int posY, int posX) : m_objectSpace(objectSpace), m_posY(posY), m_posX(posX)
        {
            getmaxyx(m_objectSpace, m_posY_Max, m_posX_Max);
        }
        virtual int getAction() = 0;
        virtual bool interactWith(CGameObject * target) = 0;
        void objectRender();
        WINDOW * m_objectSpace;
        int m_posY, m_posX, m_posX_Max, m_posY_Max;
        char m_objectForm;
    
};

class CCharacter : public CGameObject
{
    public:    
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();

        CCharacter(WINDOW* objectSpace, int posY, int posX) : CGameObject(objectSpace, posY, posX)
        {}

        float m_speed;
        CInput* m_timer;
};

class CPlayer : public CCharacter
{
    public:
        void changeForm(const char& objectForm);
        int getAction() override;
        bool interactWith(CGameObject* target) override;
    
        CPlayer(WINDOW* objectSpace, CInput * input, int posY, int posX) : CCharacter(objectSpace, posY, posX)
        {
            m_playerInput = input;
            m_objectForm = '^';
            m_speed = 1;
            keypad(m_objectSpace, true);
        }

    private:
        CInput * m_playerInput;
        
};

class CEnemy : public CCharacter
{
    public:
        void enemyDead();
        int getAction() override;
        bool interactWith(CGameObject* target) override;

        // enemy demo testing constructor
        CEnemy(WINDOW* objectSpace, int posY, int posX) : CCharacter(objectSpace, posY, posX)
        {
            m_objectForm = '~';
            m_speed = 1;
            m_timer = game.getInput();
            keypad(m_objectSpace, true);
        }
};

int CEnemy::getAction()
{
    if(m_timer->latestInput != 'x')
    {                                   // for testing only
        moveUp();
        objectRender();
        wrefresh(game.m_Window);
        moveDown();
        objectRender();
        wrefresh(game.m_Window);
        moveLeft();
        objectRender();
        wrefresh(game.m_Window);
        moveRight();
        objectRender();
        wrefresh(game.m_Window);
    }
    return 0;
}

void CPlayer::changeForm(const char& objectForm)
{
    m_objectForm = objectForm;
}

void CCharacter::moveUp()
{
    mvwaddch(m_objectSpace, m_posY, m_posX, ' ');
    m_posY -= m_speed;
    if (m_posY < 1)
    {
        m_posY = 1;
    }
}

void CCharacter::moveDown()
{
    mvwaddch(m_objectSpace, m_posY, m_posX, ' ');
    m_posY += m_speed;
    if (m_posY > m_posY_Max - 2)            // because of the border -> border is m_posY_Max - 1, so one spot before the border is m_posY_Max - 2
    {                                   
        m_posY = m_posY_Max - 2;
    }
}

void CCharacter::moveLeft()
{
    mvwaddch(m_objectSpace, m_posY, m_posX, ' ');
    m_posX -= (m_speed + 1);
    if (m_posX < 1)
    {
        m_posX = 1;
    }
}

void CCharacter::moveRight()
{
    mvwaddch(m_objectSpace, m_posY, m_posX, ' ');
    m_posX += (m_speed + 1);
    if (m_posX > m_posX_Max - 2)
    {
        m_posX = m_posX_Max - 2;
    }
}

int CPlayer::getAction()
{
    int move = m_playerInput->readInput();
    switch (move) 
    {
        case KEY_UP:
            moveUp();
            changeForm('^');
            break;
        case KEY_DOWN:
            moveDown();
            changeForm('v');
            break;
        case KEY_LEFT:
            moveLeft();
            changeForm('<');
            break;
        case KEY_RIGHT:
            moveRight();
            changeForm('>');
            break;
        default:
            break;
    }
    return move;
}

void CGameObject::objectRender()
{ 
    mvwaddch(m_objectSpace, m_posY, m_posX, m_objectForm);
}

bool CPlayer::interactWith(CGameObject * targer)
{
    //TODO
    return false;
}

bool CEnemy::interactWith(CGameObject * targer)
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
    halfdelay(20);

    // get screen size
    getmaxyx(stdscr, m_yMax, m_xMax);

}

void CGame::run() 
{
    initGame();
    // TODO : render menu etc etc...

    // just for test 
    renderSpace();
    spawnEnemy();
    spawnPlayer();
}

void CGame::renderSpace() 
{
    // create a window for player
    m_Window = newwin(ROOM_HEIGHT, ROOM_WIDTH, (m_yMax - ROOM_HEIGHT) / 2, (m_xMax - ROOM_WIDTH) / 2);
    m_Input = new CInput(m_Window);
    box(m_Window, 0, 0);
    refresh();
    wrefresh(m_Window);
}

void CGame::spawnPlayer()
{
    CPlayer* p = new CPlayer(m_Window, m_Input, (ROOM_HEIGHT - 2) / 2, (ROOM_WIDTH - 2) / 2);
    wrefresh(m_Window);

    do
    {
        p->objectRender();
        wrefresh(m_Window);
    } while (p->getAction() != 'x');
    
    endGame();
   
}

// udelat tak, že playerinput nebo move spustí getActionForObjects na vektoru včech pohyblivých objektů ve hře a poté zavolá jednoduchý refresh jednou 
// po desetine sekudy bude vracen ERR a akce vyse zmineny se opakuje 
// akce spoustena hned pod wgetch 

void CGame::spawnEnemy()
{
    CEnemy* e = new CEnemy(m_Window, 20, 40);
    wrefresh(m_Window);
    while (true)
        e->getAction();

    
}

void CGame::endGame()
{
    curs_set(0);
    refresh();
    endwin();
}


int main(int argc, char ** argv)
{
    game.run();

    return 0;
}