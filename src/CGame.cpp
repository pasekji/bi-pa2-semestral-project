#include "CGame.h"

void CGame::run() 
{
    if(!is_init)
    {
        initSpace();
        initBars();
        initMap();
        is_init = true;
        endGame();
    }
    else
    {
        loadGame();
        endGame();
    }

    return;
}

void CGame::initMap()
{
    // load paramets Y,X if box or not and pass to renderSpace for new WINDOW
    m_currentMap->m_mapWindow = m_Window;
    m_currentMap->loadMap();

    return;
}

void CGame::initSpace() 
{
    // create a window for player
    getmaxyx(stdscr, m_yMax, m_xMax);
    m_Window = newwin((int)(m_yMax * 0.99), (int)(m_xMax * 0.633), (int)((m_yMax - (int)(m_yMax * 0.99)) / 2), (int)((m_xMax - (int)(m_xMax * 0.633)) / 2));
    refresh();
    wrefresh(m_Window);

    return;
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

    return;
}

void CGame::endGame()               // not needed
{
    clear();
    refresh();

    return;
}

void CGame::loadGame()
{
    getmaxyx(stdscr, m_yMax, m_xMax);
    mvwin(m_Window, (int)((m_yMax - (int)(m_yMax * 0.99)) / 2), (int)((m_xMax - (int)(m_xMax * 0.633)) / 2));
    mvwin(m_eventWindow, (int)((m_yMax - (int)(m_yMax * 0.98)) / 2) + (int)(m_yMax * 0.54), (int)((m_xMax - (int)(m_xMax * 0.63)) / 2) + (int)(m_xMax * 0.63) + (int)(m_xMax * 0.009));
    mvwin(m_effectWindow, (int)((m_yMax - (int)(m_yMax * 0.98)) / 2) + (int)(m_yMax * 0.45), (int)((m_xMax - (int)(m_xMax * 0.63)) / 2) + (int)(m_xMax * 0.63) + (int)(m_xMax * 0.009));
    mvwin(m_objectWindow, (int)((m_yMax - (int)(m_yMax * 0.99)) / 2), (int)((m_xMax - (int)(m_xMax * 0.63)) / 2) + (int)(m_xMax * 0.63) + (int)(m_xMax * 0.009));
    mvwin(m_inventoryWindow, (int)(m_yMax * 0.46), (int)(m_xMax * 0.009));
    mvwin(m_playerWindow, (int)(m_yMax * 0), (int)(m_xMax * 0.009));
    wresize(m_Window, (int)(m_yMax * 0.99), (int)(m_xMax * 0.633));
    wresize(m_eventWindow, (int)(m_yMax * 0.44), (int)(m_xMax * 0.17));
    wresize(m_effectWindow, (int)(m_yMax * 0.08), (int)(m_xMax * 0.17));
    wresize(m_objectWindow, (int)(m_yMax * 0.44), (int)(m_xMax * 0.17));
    wresize(m_inventoryWindow, (int)(m_yMax * 0.54), (int)(m_xMax * 0.17));
    wresize(m_playerWindow, (int)(m_yMax * 0.44), (int)(m_xMax * 0.17));
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

    m_currentMap->catchPlayer();

    return;

}

CMap* CGame::getMap() const
{
    return m_currentMap;
}

const int & CGame::getYMax() const
{
    return m_yMax;   
}

const int & CGame::getXMax() const
{
    return m_xMax;   
}
