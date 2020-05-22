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
    m_Window = newwin((int)(m_yMax * 0.99), (int)(m_xMax * 0.633), (int)((m_yMax - (int)(m_yMax * 0.99)) / 2), (int)((m_xMax - (int)(m_xMax * 0.633)) / 2));
    refresh();
    wrefresh(m_Window);
}

void CGame::renderBars()
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
    mvwprintw(m_playerWindow, 1, 1, "yMax : %d, xMax : %d", m_yMax, m_xMax);          // yMax = 66, xMax = 237
    mvwprintw(m_playerWindow, 2, 1, "eventWin : %d, %d, %d, %d", (int)(m_yMax * 0.44), (int)(m_xMax * 0.17), (int)((m_yMax - (int)(m_yMax * 0.98)) / 2) + (int)(m_yMax * 0.54), (int)((m_xMax - (int)(m_xMax * 0.63)) / 2) + (int)(m_xMax * 0.63) + (int)(m_xMax * 0.009));
    mvwprintw(m_playerWindow, 3, 1, "eventWin : %d, %d, %d, %d", 29, 40, ((m_yMax - ROOM_HEIGHT) / 2) + 36, ((m_xMax - ROOM_WIDTH) / 2) + ROOM_WIDTH + 2);
    mvwprintw(m_playerWindow, 4, 1, "effectWin : %d, %d, %d, %d",  (int)(m_yMax * 0.08), (int)(m_xMax * 0.17), (int)((m_yMax - (int)(m_yMax * 0.98)) / 2) + (int)(m_yMax * 0.45), (int)((m_xMax - (int)(m_xMax * 0.63)) / 2) + (int)(m_xMax * 0.63) + (int)(m_xMax * 0.009));
    mvwprintw(m_playerWindow, 5, 1, "effectWin : %d, %d, %d, %d",  5, 40, ((m_yMax - ROOM_HEIGHT) / 2) + 30, ((m_xMax - ROOM_WIDTH) / 2) + ROOM_WIDTH + 2);
    mvwprintw(m_playerWindow, 6, 1, "objectWin : %d, %d, %d, %d", (int)(m_yMax * 0.44), (int)(m_xMax * 0.17), (int)((m_yMax - (int)(m_yMax * 0.99)) / 2), (int)((m_xMax - (int)(m_xMax * 0.63)) / 2) + (int)(m_xMax * 0.63) + (int)(m_xMax * 0.009));
    mvwprintw(m_playerWindow, 7, 1, "objectWin : %d, %d, %d, %d", 29, 40, ((m_yMax - ROOM_HEIGHT) / 2), ((m_xMax - ROOM_WIDTH) / 2) + ROOM_WIDTH + 2);
    mvwprintw(m_playerWindow, 8, 1, "invWin : %d, %d, %d, %d", (int)(m_yMax * 0.54), (int)(m_xMax * 0.17), (int)(m_yMax * 0.46), (int)(m_xMax * 0.009));
    mvwprintw(m_playerWindow, 9, 1, "playerWin : %d, %d, %d, %d", (int)(m_yMax * 0.44), (int)(m_xMax * 0.17), (int)(m_yMax * 0), (int)(m_xMax * 0.009));
    mvwprintw(m_playerWindow, 10, 1, "mainWin : %d, %d, %d, %d", (int)(m_yMax * 0.99), (int)(m_xMax * 0.633), (int)((m_yMax - (int)(m_yMax * 0.99)) / 2), (int)((m_xMax - (int)(m_xMax * 0.633)) / 2));
    mvwprintw(m_playerWindow, 11, 1, "mainWin : %d, %d, %d, %d", ROOM_HEIGHT, ROOM_WIDTH, (m_yMax - ROOM_HEIGHT) / 2, (m_xMax - ROOM_WIDTH) / 2);





    wrefresh(m_playerWindow);
}

void CGame::endGame()
{
    curs_set(0);
    refresh();
    endwin();
}
