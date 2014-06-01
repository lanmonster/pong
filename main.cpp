/******************************************************************************
Filename:                   main.cpp

Authors:                    Zachary Grumbles
                            Kyle Lanmon
                            Kaylee Reick

Description:                It's Pong!!!

Date Modified:              12/8/2013
******************************************************************************/

#include <iostream>
#include "plotter.h"
#include "pong.h"
#include <string>
#include <fstream>

using namespace std;

int main()
{
    pong game;
    game.consoleSize(101, 37);
    string title;
    Plotter b;
    char a;
    ifstream art("ASCIIart.txt");

    while(art.get(a))
    {
        title += a;
    }

    art.close();

    cout << title << "\n\n                            A  S W A G D A D D I E S  P R O D U C T I O N\n";
    cout << "\n                                         Press ENTER to play\n";

    if(cin.get() == '\n')
    {
        game.consoleSize(80, 37);
        game.startGame();
    }

    return 0;
}
