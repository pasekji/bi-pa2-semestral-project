#include "CMap.h"
#include "CApplication.h"

extern CApplication application;
const char WALL = '#';
const char VOID = '+';

void CMap::loadMap()            
{
    // no predef ROOM_HEIGHT othr. will be used 
    spawnPlayer(((int)(application.getGame().m_yMax * 0.99) - 2) / 2, ((int)(application.getGame().m_xMax * 0.633) - 2) / 2, PALADIN);
}

bool CMap::colisionDetect(std::pair<int, int> & pair)
{
    for (auto i: m_moveableObjects)
    {
        if(i->getPos() == pair)
            return true;
    }

    for (auto i: m_imoveableObjects)
    {
        if(i->getPos() == pair)
            return true;
    }

    return false;
}

void CMap::demo_loadMap()
{

    // no predef ROOM_HEIGHT or othr. will be used 
    spawnEnemy(((ROOM_HEIGHT - (ROOM_HEIGHT/5))/2), (ROOM_WIDTH - 2) / 2, BASILISK);
    spawnProp((ROOM_HEIGHT/2), (ROOM_WIDTH - (ROOM_WIDTH/20)), WALL);
    spawnProp((ROOM_HEIGHT/2), (ROOM_WIDTH - (ROOM_WIDTH/20) - 1), WALL);
    spawnProp((ROOM_HEIGHT/2), (ROOM_WIDTH - (ROOM_WIDTH/20) - 2), WALL);

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
    for(auto i = ++m_moveableObjects.begin(); i != m_moveableObjects.end(); ++i)
    {
        (*i)->getAction();
    }
}

void CMap::spawnPlayer(int posY, int posX, player_class playerClass)
{
    CPlayer* player;
    switch (playerClass)
    {
        case PALADIN:
            player = new CPlayerPaladin(m_mapWindow, posY, posX);
            break;
        case MAGE:
            break;
        case ROGUE:
            break;
        default:
            break;
    }
    m_moveableObjects.push_back(player);
    demo_loadMap();
    wrefresh(m_mapWindow);

    do
    {
        moveableDoAction();
        renderObjects();
        wrefresh(m_mapWindow);

    } while (player->getAction() != 'x');
    
    application.getGame().endGame();

}

void CMap::spawnEnemy(int posY, int posX, enemy_type type)
{
    CEnemy* enemy = new CEnemy(m_mapWindow, posY, posX, type);
    m_moveableObjects.push_back(enemy);
}

void CMap::spawnProp(int posY, int posX, const char & objectForm)
{
    CProp* prop = new CProp(m_mapWindow, posY, posX, objectForm);
    m_imoveableObjects.push_back(prop);
}

void CMap::staticCamera(direction & dir, int & steps)
{
    switch (dir)
    {
        case UP:
            camera_objectsDown(steps);
            renderObjects();
            break;
    
        case DOWN:
            camera_objectsUp(steps);
            renderObjects();
            break;
        
        case LEFT:
            camera_objectsRight(steps);
            renderObjects();
            break;

        case RIGHT:
            camera_objectsLeft(steps);
            renderObjects();
            break;
        
        default:
            break;
    }
}

void CMap::camera_objectsDown(int & steps)
{
    for(auto i: m_moveableObjects)
    {
        i->moveDown(steps);
    }

    for(auto i: m_imoveableObjects)
    {
        i->moveDown(steps);
    }
}

void CMap::camera_objectsUp(int & steps)
{
    for(auto i: m_moveableObjects)
    {
        i->moveUp(steps);
    }

    for(auto i: m_imoveableObjects)
    {
        i->moveUp(steps);
    }
}

void CMap::camera_objectsRight(int & steps)
{
    for(auto i: m_moveableObjects)
    {
        i->moveRight(steps);
    }

    for(auto i: m_imoveableObjects)
    {
        i->moveRight(steps);
    }
}

void CMap::camera_objectsLeft(int & steps)
{
    for(auto i: m_moveableObjects)
    {
        i->moveLeft(steps);
    }
    for(auto i: m_imoveableObjects)
    {
        i->moveLeft(steps);
    }   
}