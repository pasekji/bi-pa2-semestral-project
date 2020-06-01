#include "CMainMenu.h"

CMainMenu::CMainMenu() : CMenu()
{
    m_height = 10;
    m_width = 14;
    m_lable = "Main menu";
    m_logo = 
    {
            " _   _ _____   _   _   ___  ___  ___ _____  ____________ _____",
            "| \\ | |  _  | | \\ | | / _ \\ |  \\/  ||  ___| | ___ \\ ___ \\  __ \\",
            "|  \\| | | | | |  \\| |/ /_\\ \\| .  . || |__   | |_/ / |_/ / |  \\/",
            "| . ` | | | | | . ` ||  _  || |\\/| ||  __|  |    /|  __/| | __ ",
            "| |\\  \\ \\_/ / | |\\  || | | || |  | || |___  | |\\ \\| |   | |_\\ \\",
            "\\_| \\_/\\___/  \\_| \\_/\\_| |_/\\_|  |_/\\____/  \\_| \\_\\_|    \\____/"
    };
    m_options.push_back("New Game");
    m_options.push_back("Load Game");
    m_options.push_back("Quit");
    m_selected = 0;

}

void CMainMenu::initMenu()
{
    int tmpY, tmpX;
    getmaxyx(stdscr, tmpY, tmpX);
    m_menuWindow = newwin(m_height, m_width, (tmpY - m_height) / 2, (tmpX - m_width) / 2);
    box(m_menuWindow, 0, 0);
    keypad(m_menuWindow, true);
    m_logoWindow = newwin(8, 65, ((tmpY - m_height) / 2) - 8, ((tmpX - m_width) / 2) - ((65 - m_width) / 2));
    
    for(std::size_t i = 0; i < m_logo.size(); ++i)
        mvwprintw(m_logoWindow, i + 1, 1, m_logo.at(i).c_str());

    for(std::size_t i = 0; i < m_options.size(); ++i)
        mvwprintw(m_menuWindow, (i + 1) * 2, (m_width - m_options.at(i).size()) / 2, m_options.at(i).c_str());

    renderMenu();

}

unsigned int CMainMenu::getAction()
{
    m_action = wgetch(m_menuWindow);

    switch (m_action)
    {
        case KEY_UP:
            if(m_selected != 0)
                m_selected--;
        break;
    
        case KEY_DOWN:
            m_selected++;
            if(m_selected == m_options.size())
                m_selected = m_options.size() - 1;
        break;

        default:
            break;
    }

    renderMenu();
    
    if(m_action == 10)
        return m_action;
    else
        return 0;

}

void CMainMenu::renderMenu()
{
    refresh();
    wrefresh(m_logoWindow);
    wrefresh(m_menuWindow);
    for(std::size_t i = 0; i < m_options.size(); ++i)
    {
        if(i == m_selected)
            wattron(m_menuWindow, A_REVERSE);
        mvwprintw(m_menuWindow, (i + 1) * 2, (m_width - m_options.at(i).size()) / 2, m_options.at(i).c_str());
        wattroff(m_menuWindow, A_REVERSE);
    }
}

