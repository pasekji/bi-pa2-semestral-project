#include "CGame.h"


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

void CGame::endGame()
{
    curs_set(0);
    refresh();
    endwin();
}
