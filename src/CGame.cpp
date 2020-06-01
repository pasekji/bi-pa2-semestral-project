#include "CGame.h"
#include "CApplication.h"

extern CApplication application;

void CGame::run() 
{
    // TODO : render menu etc etc...

    // just for test
    initSpace();
    initBars();
    initMap();

}

void CGame::initMap()
{
    // load paramets Y,X if box or not and pass to renderSpace for new WINDOW
    m_currentMap->m_mapWindow = m_Window;
    m_currentMap->loadMap();
}

void CGame::initSpace() 
{
    // create a window for player
    m_Window = newwin((int)(m_yMax * 0.99), (int)(m_xMax * 0.633), (int)((m_yMax - (int)(m_yMax * 0.99)) / 2), (int)((m_xMax - (int)(m_xMax * 0.633)) / 2));
    refresh();
    wrefresh(m_Window);
}

void CGame::initBars()
{
    // create action window
    m_eventWindow = newwin((int)(m_yMax * 0.44), (int)(m_xMax * 0.17), (int)((m_yMax - (int)(m_yMax * 0.98)) / 2) + (int)(m_yMax * 0.54), (int)((m_xMax - (int)(m_xMax * 0.63)) / 2) + (int)(m_xMax * 0.63) + (int)(m_xMax * 0.009));
    m_effectWindow = newwin((int)(m_yMax * 0.08), (int)(m_xMax * 0.17), (int)((m_yMax - (int)(m_yMax * 0.98)) / 2) + (int)(m_yMax * 0.45), (int)((m_xMax - (int)(m_xMax * 0.63)) / 2) + (int)(m_xMax * 0.63) + (int)(m_xMax * 0.009));
    m_objectWindow = newwin((int)(m_yMax * 0.44), (int)(m_xMax * 0.17), (int)((m_yMax - (int)(m_yMax * 0.99)) / 2), (int)((m_xMax - (int)(m_xMax * 0.63)) / 2) + (int)(m_xMax * 0.63) + (int)(m_xMax * 0.009));
    m_inventoryWindow = newwin((int)(m_yMax * 0.54), (int)(m_xMax * 0.17), (int)(m_yMax * 0.46), (int)(m_xMax * 0.009));
    m_playerWindow = newwin((int)(m_yMax * 0.44), (int)(m_xMax * 0.17), (int)(m_yMax * 0), (int)(m_xMax * 0.009));
    box(m_eventWindow, 0, 0);
    box(m_effectWindow, 0, 0);
    box(m_objectWindow, 0, 0);
    box(m_inventoryWindow, 0, 0);
    box(m_playerWindow, 0, 0);
    refresh();
    wrefresh(m_eventWindow);
    wrefresh(m_effectWindow);
    wrefresh(m_objectWindow);
    wrefresh(m_inventoryWindow);
    wrefresh(m_playerWindow);
}

void CGame::endGame()
{
    clear();
    application.initMainMenu();
}

CMap* CGame::getMap()
{
    return m_currentMap;
}
