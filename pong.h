#include "plotter.h"
#include <fstream>
#include <iostream>
#include <string>
#include <windows.h>
#include <mmsystem.h>

using namespace std;

class paddle
{
    private:
        int x, y;


    public:
        paddle();
        void paddle2();
        void up();
        void down();
        void setPad(int, int);
        void resetPad(int, int);

        int getx();
        int gety();
};

class ball
{
    private:
        int x,y;
        bool hit;
    public:
        ball()
        {
            x = 39;
            y = 15;
        }

        int getx();
        int gety();
        void setx(int);
        void sety(int);
};

class pong
{
    private:
        Plotter p;
        paddle p1, p2;
        ink color;
        char p1Score, p2Score;
        bool goal;

        void drawPaddle1();
        void drawPaddle2();

    public:
        string doom;
        string scoreTop;
        ifstream doomPong;
        ifstream scoreArt;
        char s, c;

        void consoleSize( int, int );

        void startGame();

        void moveBall();

        void changeColor();

        void update(char);
        void newGame();
        void drawFrame();

        void p1Goal();
        void p2Goal();
        void resetScore();
        char getP1Score();
        char getP2Score();
};
