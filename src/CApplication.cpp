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
    initMainMenu();
}

void CApplication::endApplication()
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

CMainMenu & CApplication::getMainMenu()
{
    return m_mainMenu;
}

const CMainMenu & CApplication::getMainMenu() const
{
    return m_mainMenu;
}

void CApplication::initMainMenu()
{
    m_mainMenu.initMenu();

    while(m_mainMenu.getAction() == 0);

    switch(m_mainMenu.getSelected())
    {
        case 0:
            m_game.run();
            break;
        case 1:
            m_game.run();
            break;
        case 2:
            endApplication();
        default:
            break;
    }
}
