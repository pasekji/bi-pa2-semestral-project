#include "CGame.h"


void CGame::initGame() 
{
    setlocale(LC_ALL, "");

    // ncurses start and setting
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    halfdelay(1);       // 2 possible as well for less enemy action

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
    renderBars();
    m_currentMap->m_mapWindow = m_Window;
    m_currentMap->loadMap();
}

void CGame::renderSpace() 
{
    // create a window for player
    m_Window = newwin(ROOM_HEIGHT, ROOM_WIDTH, (m_yMax - ROOM_HEIGHT) / 2, (m_xMax - ROOM_WIDTH) / 2);
    refresh();
    wrefresh(m_Window);
}

void CGame::renderBars()
{
    // create action window
    m_eventWindow = newwin(29, 40, ((m_yMax - ROOM_HEIGHT) / 2) + 36, ((m_xMax - ROOM_WIDTH) / 2) + ROOM_WIDTH + 2);
    m_effectWindow = newwin(5, 40, ((m_yMax - ROOM_HEIGHT) / 2) + 30, ((m_xMax - ROOM_WIDTH) / 2) + ROOM_WIDTH + 2);
    m_objectWindow = newwin(29, 40, ((m_yMax - ROOM_HEIGHT) / 2), ((m_xMax - ROOM_WIDTH) / 2) + ROOM_WIDTH + 2);
    m_inventoryWindow = newwin(35, 40, 30, 2);
    m_playerWindow = newwin(29, 40, 0, 2);
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
    mvwprintw(m_playerWindow, 1, 1, "yMax : %d, xMax : %d\n", m_yMax, m_xMax);          // yMax = 66, xMax = 237
    wrefresh(m_playerWindow);
}

void CGame::endGame()
{
    curs_set(0);
    refresh();
    endwin();
}
