#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <ncurses.h>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include "enums.h"

class CMenu
{
    public:
        CMenu();

        ~CMenu();

        unsigned int getAction();

        void renderMenu();
        void initMenu();
        void loadMenu();
            
        
        unsigned int getSelected();

        bool is_init = false;

        void setOptions(std::vector<std::string> options);
        
    private:
        const std::vector<std::string> m_logo =     
        {
            " _   _ _____   _   _   ___  ___  ___ _____  ____________ _____",
            "| \\ | |  _  | | \\ | | / _ \\ |  \\/  ||  ___| | ___ \\ ___ \\  __ \\",
            "|  \\| | | | | |  \\| |/ /_\\ \\| .  . || |__   | |_/ / |_/ / |  \\/",
            "| . ` | | | | | . ` ||  _  || |\\/| ||  __|  |    /|  __/| | __ ",
            "| |\\  \\ \\_/ / | |\\  || | | || |  | || |___  | |\\ \\| |   | |_\\ \\",
            "\\_| \\_/\\___/  \\_| \\_/\\_| |_/\\_|  |_/\\____/  \\_| \\_\\_|    \\____/"
        };
        
        WINDOW* m_logoWindow = nullptr;
        WINDOW* m_menuWindow = nullptr;

        int m_width, m_height;

        std::vector<std::string>::iterator m_it;
        std::vector<std::string> m_options;
        unsigned int m_selected;
        int m_action;
        
};

#endif