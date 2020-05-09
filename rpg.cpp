#include <ncurses.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <locale.h>
#include <vector>
#include <map>


#define ROOM_HEIGHT 50 
#define ROOM_WIDTH 100

char WALL = '#';
char VOID = '+';

using namespace std;

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

        int m_speed;
};

class CDoor;

class CMap
{
    public:
        CMap() = default;
        void loadMap();
        void demo_loadMap();                    // run spawning all objects - loadMap sub
        bool loadMapFromFile(const string & pathToFile);
        bool openDoor(CDoor*);
        bool goToMap(CMap*);
        bool colisionDetect(int & p_posY, int & p_posX);
        int m_width, m_height;
        int m_yMax, m_xMax;
        WINDOW* m_mapWindow;

    private:
        string m_pathToFile;
        CDoor* m_upperLayer;
        vector<CCharacter*> m_moveableObjects;
        vector<CGameObject*> m_imoveableObjects;
        map<pair<int, int>, CGameObject*> m_targets;
        map<CDoor, CMap*> m_layers;                     // current layer must be included too
        void spawnPlayer(int posY, int posX);           // (int posY, int posX)
        void spawnEnemy(int posY, int posX);
        void spawnProp(int posY, int posX, char & objectForm);
        void renderObjects();                           // samotne znovu vykresleni
        void moveableDoAction();                        // vyvolej nahodnou akci, ktera zmeni vlastnosti instance napr. posX++ (jednu)
    
};

void CMap::loadMap()
{
    spawnPlayer((ROOM_HEIGHT - 2) / 2, (ROOM_WIDTH - 2) / 2);
}

class CGame
{
    public:
        CGame() = default;
        int m_yMax, m_xMax;
        WINDOW* m_Window;
        CMap* m_currentMap = new CMap;
        void run();
        void endGame();

    private:
        void initGame();
        void renderSpace();
        void initMap();

};

class CProp : public CGameObject
{
    public:
        CProp(WINDOW* objectSpace, int posY, int posX, char & objectForm) : CGameObject(objectSpace, posY, posX)
        {
            m_objectForm = objectForm;
        }

        int getAction() { return 0; };
        bool interactWith(CGameObject * target){ return false; };

};

class CDoor : public CGameObject
{
    public:
        int getAction() { return 0; };
        bool interactWith(CGameObject * target){ return false; };
};


CGame game;

bool CMap::colisionDetect(int & p_posY, int & p_posX)
{
    for (auto i: m_moveableObjects)
    {
        if(pair(i->m_posY, i->m_posX) == pair(p_posY, p_posX))
            return true;
    }

    for (auto i: m_imoveableObjects)
    {
        if(pair(i->m_posY, i->m_posX) == pair(p_posY, p_posX))
            return true;
    }

    return false;
}

void CMap::demo_loadMap()
{
    spawnEnemy(20, (ROOM_WIDTH - 2) / 2);
    spawnProp(25, 95, WALL);
    spawnProp(25, 94, WALL);
    spawnProp(25, 93, WALL);

}

void CMap::renderObjects()
{
    for(auto i: m_moveableObjects)
    {
        i->objectRender();
    }

    for(auto i: m_imoveableObjects)
    {
        i->objectRender();
    }
}

void CMap::moveableDoAction()
{
    for(auto i: m_moveableObjects)
    {
        i->getAction();
    }
}

class CPlayer : public CCharacter
{
    public:
        void changeForm(const char& objectForm);
        int getAction() override;
        bool interactWith(CGameObject* target) override;
    
        CPlayer(WINDOW* objectSpace, int posY, int posX) : CCharacter(objectSpace, posY, posX)
        {
            m_objectForm = '^';
            m_speed = 1;
            keypad(m_objectSpace, true);
        }

    private:
        
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
        }
};

int CEnemy::getAction()     // just demo testing
{
    int action = rand() % 5;
    int tmppos;
    switch (action) 
    {
        case 0:
            break;
        case 1:
            if(!game.m_currentMap->colisionDetect(tmppos = m_posY - m_speed, m_posX))
                moveUp();
            break;
        case 2:
            if(!game.m_currentMap->colisionDetect(tmppos = m_posY + m_speed, m_posX))
                moveDown();
            break;
        case 3:
            if(!game.m_currentMap->colisionDetect(m_posY, tmppos = m_posX - (m_speed + 1)))
                moveLeft();
            break;
        case 4:
            if(!game.m_currentMap->colisionDetect(m_posY, tmppos = m_posX + (m_speed + 1)))
                moveRight();
        default:
            break;
    }

    return action;
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
    int move = wgetch(m_objectSpace);
    int tmppos;
    switch (move) 
    {
        case KEY_UP:
            if(!game.m_currentMap->colisionDetect(tmppos = m_posY - m_speed, m_posX))
                moveUp();
            changeForm('^');
            break;
        case KEY_DOWN:
            if(!game.m_currentMap->colisionDetect(tmppos = m_posY + m_speed, m_posX))
                moveDown();
            changeForm('v');
            break;
        case KEY_LEFT:
            if(!game.m_currentMap->colisionDetect(m_posY, tmppos = m_posX - (m_speed + 1)))
                moveLeft();
            changeForm('<');
            break;
        case KEY_RIGHT:
            if(!game.m_currentMap->colisionDetect(m_posY, tmppos = m_posX + (m_speed + 1)))
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

bool CPlayer::interactWith(CGameObject * target)
{
    //TODO
    return false;
}

bool CEnemy::interactWith(CGameObject * target)
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
    halfdelay(1);

    // get screen size
    getmaxyx(stdscr, m_yMax, m_xMax);

}

void CGame::run() 
{
    initGame();
    // TODO : render menu etc etc...

    // just for test
    initMap();

}

void CGame::initMap()
{
    // load paramets Y,X if box or not and pass to renderSpace for new WINDOW
    renderSpace();
    m_currentMap->m_mapWindow = m_Window;
    m_currentMap->loadMap();
}

void CGame::renderSpace() 
{
    // create a window for player
    m_Window = newwin(ROOM_HEIGHT, ROOM_WIDTH, (m_yMax - ROOM_HEIGHT) / 2, (m_xMax - ROOM_WIDTH) / 2);
    box(m_Window, 0, 0);
    refresh();
    wrefresh(m_Window);
}

void CMap::spawnPlayer(int posY, int posX)
{
    CPlayer* player = new CPlayer(m_mapWindow, posY, posX);
    m_moveableObjects.push_back(player);
    demo_loadMap();
    wrefresh(m_mapWindow);

    do
    {
        player->objectRender();
        moveableDoAction();
        renderObjects();
        wrefresh(m_mapWindow);
    } while (player->getAction() != 'x');
    
    game.endGame();

}

void CMap::spawnEnemy(int posY, int posX)
{
    CEnemy* enemy = new CEnemy(m_mapWindow, posY, posX);
    m_moveableObjects.push_back(enemy);
}

void CMap::spawnProp(int posY, int posX, char & objectForm)
{
    CProp* prop = new CProp(m_mapWindow, posY, posX, objectForm);
    m_imoveableObjects.push_back(prop);
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