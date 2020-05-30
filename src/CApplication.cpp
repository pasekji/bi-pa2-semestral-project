#include "CApplication.h"

void CApplication::initApplication()
{
    setlocale(LC_ALL, "");

    // ncurses start and setting
    initscr();
    noecho();
    cbreak();
    curs_set(0);

    // get screen size
    getmaxyx(stdscr, m_yMax, m_xMax);
    m_game.m_yMax = m_yMax;
    m_game.m_xMax = m_xMax;
}

void CApplication::run()
{
    initApplication();
    m_game.run();
}

void CApplication::endGame()
{
    curs_set(0);
    refresh();
    endwin();    
}

CGame & CApplication::getGame()
{
    return m_game;
}

const CGame & CApplication::getGame() const
{
    return m_game;
}

void CApplication::initMainMenu()
{
    //m_mainMenu.m_height = 10;
    //m_mainMenu.m_width = 10;
    //m_mainMenu.m_menuWindow = newwin(m_mainMenu.m_height, m_mainMenu.m_width, (m_yMax - m_mainMenu.m_height) / 2, (m_xMax - m_mainMenu.m_width) / 2);
    //box(m_mainMenu.m_menuWindow, 0, 0);
    //keypad(m_mainMenu.m_menuWindow, true);

}
