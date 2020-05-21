#include "CMap.h"
#include "CGame.h"


extern CGame game;
extern char WALL;

void CMap::loadMap()            
{
    m_xMax = 1000;
    m_yMax = 1000;

    // no predef ROOM_HEIGHT othr. will be used 
    spawnPlayer((ROOM_HEIGHT - 2) / 2, (ROOM_WIDTH - 2) / 2, PALADIN);
}

bool CMap::colisionDetect(int & p_posY, int & p_posX)
{
    for (auto i: m_moveableObjects)
    {
        if(std::make_pair(i->m_posY, i->m_posX) == std::make_pair(p_posY, p_posX))
            return true;
    }

    for (auto i: m_imoveableObjects)
    {
        if(std::make_pair(i->m_posY, i->m_posX) == std::make_pair(p_posY, p_posX))
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
    for(auto i: m_moveableObjects)
    {
        i->getAction();
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
        player->objectRender();
        moveableDoAction();
        renderObjects();
        wrefresh(m_mapWindow);
    } while (player->getAction() != 'x');
    
    game.endGame();

}

void CMap::spawnEnemy(int posY, int posX, enemy_type type)
{
    CEnemy* enemy = new CEnemy(m_mapWindow, posY, posX, type);
    m_moveableObjects.push_back(enemy);
}

void CMap::spawnProp(int posY, int posX, char & objectForm)
{
    CProp* prop = new CProp(m_mapWindow, posY, posX, objectForm);
    m_imoveableObjects.push_back(prop);
}

void CMap::staticCamera(direction & dir)
{
    switch (dir)
    {
        case UP:
            camera_objectsDown();
            renderObjects();
            break;
    
        case DOWN:
            camera_objectsUp();
            renderObjects();
            break;
        
        case LEFT:
            camera_objectsRight();
            renderObjects();
            break;

        case RIGHT:
            camera_objectsLeft();
            renderObjects();
            break;
        
        default:
            break;
    }
}

void CMap::camera_objectsDown()
{
    for(auto i: m_moveableObjects)
    {
        i->cameraDown();
    }

    for(auto i: m_imoveableObjects)
    {
        i->cameraDown();
    }
}

void CMap::camera_objectsUp()
{
    for(auto i: m_moveableObjects)
    {
        i->cameraUp();
    }

    for(auto i: m_imoveableObjects)
    {
        i->cameraUp();
    }
}

void CMap::camera_objectsRight()
{
    for(auto i: m_moveableObjects)
    {
        i->cameraRight();
    }

    for(auto i: m_imoveableObjects)
    {
        i->cameraRight();
    }
}

void CMap::camera_objectsLeft()
{
    for(auto i: m_moveableObjects)
    {
        i->cameraLeft();
    }

    for(auto i: m_imoveableObjects)
    {
        i->cameraLeft();
    }   
}