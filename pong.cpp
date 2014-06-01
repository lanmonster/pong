#include "pong.h"
#include <fstream>

const int MAX_Y = 33;
const int MIN_Y = 11;

using namespace std;

void pong::changeColor()
{
    color = (ink)(((int)color + 1) % 16);
    if( color == black )
		color = (ink)(((int)color + 1) % 16);
	p.setColor(color);

	drawFrame();
}

void paddle::resetPad(int a, int b)
{
    x = a;
    y = b;
}

paddle::paddle()
{
    x = 2;
    y = 15;
}

void pong::drawPaddle1()
{
    p.plot(p1.getx(), p1.gety() - 2, SQUARE);
    p.plot(p1.getx(), p1.gety() - 1, SQUARE);
    p.plot(p1.getx(), p1.gety()    , SQUARE);
    p.plot(p1.getx(), p1.gety() + 1, SQUARE);
    p.plot(p1.getx(), p1.gety() + 2, SQUARE);

    p.setColor(black);
    p.plot(p1.getx(), p1.gety() - 3, SQUARE);
    p.plot(p1.getx(), p1.gety() + 3, SQUARE);

}

void pong::drawPaddle2()
{
    p.plot(p2.getx(), p2.gety() - 2, SQUARE);
    p.plot(p2.getx(), p2.gety() - 1, SQUARE);
    p.plot(p2.getx(), p2.gety()    , SQUARE);
    p.plot(p2.getx(), p2.gety() + 1, SQUARE);
    p.plot(p2.getx(), p2.gety() + 2, SQUARE);

    p.setColor(black);
    p.plot(p2.getx(), p2.gety() - 3, SQUARE);
    p.plot(p2.getx(), p2.gety() + 3, SQUARE);
}

int paddle::getx()
{
    return x;
}

int paddle::gety()
{
    return y;
}

void pong::drawFrame()
{
    Plotter frame, score;

    frame.setColor(color);

    for(int i = 0; i < 79; i++)
    {
        //top lines
        frame.plot(i, 0, TOP);
        frame.plot(i, 8, BOTTOM);
        //bottom
        frame.plot(i + 1, 35, BOTTOM);

        if (i < 36)
        {
            //left
            frame.plot(0, i, LEFT);
            //right
            frame.plot(79, i, RIGHT);
            //mid
            if(i % 2 == 0 && i > 8)
            {
                frame.plot(39, i, LEFT);
            }
        }
    }

    scoreArt.open("score.txt");
    while(scoreArt.get(s))
    {
        scoreTop += s;
    }
    score.move(42, 1);
    cout << scoreTop;

    doomPong.open("doomPong.txt");
    while(doomPong.get(c))
    {
        doom += c;
    }
    frame.move(0, 1);
    cout << doom;

    score.plot(75, 2, getP1Score());
    score.plot(75, 6, getP2Score());

    p.setColor((ink)(((int)color + 1) % 16));
    if(color == black)
        p.setColor((ink)(((int)color + 1) % 16));
    drawPaddle1();

    p.setColor((ink)(((int)color + 1) % 16));
    if(color == black)
        p.setColor((ink)(((int)color + 1) % 16));
    drawPaddle2();
}


void paddle::up()
{
    if( y > MIN_Y )
		y--;
}

void paddle::down()
{
    if( y < MAX_Y - 1 )
		y++;
}

char pong::getP1Score()
{
    return p1Score;
}

char pong::getP2Score()
{
    return p2Score;
}

void pong::resetScore()
{
    p1Score = '0';
    p2Score = '0';
}

void pong::p1Goal()
{
    //incrememnting score
    p1Score++;

    //PlaySound(TEXT("boop.mp3"), NULL, SND_FILENAME);

    //resetting location of the paddles and ball
    p1.resetPad(2, 20);
    p2.resetPad(77, 20);
    changeColor();
    drawFrame();
    moveBall();
    goal = true;

}

void pong::p2Goal()
{
    //incrememnting score
    p2Score++;

    //PlaySound(TEXT("boop.mp3"), NULL, SND_FILENAME);

    //resetting location of the paddles and ball
    p1.resetPad(2, 20);
    p2.resetPad(77, 20);
    changeColor();
    drawFrame();
    moveBall();
    goal = true;
}

void pong::newGame()
{
    p.clear();
    p1.resetPad(2, 20);
    p2.resetPad(77, 20);
    p1Score = '0';
    p2Score = '0';

    changeColor();
    drawFrame();

    moveBall();
}

void pong::update(char a)
{
    Plotter frame;
    frame.setColor(color);
    switch( a )
    {
        case 'w':
        case 'W':
            p1.up();
            break;
        case 's':
        case 'S':
            p1.down();
            break;
        case vk_up:
			p2.up();
			break;
		case vk_down:
			p2.down();
			break;
        case 'n':
        case 'N':
            newGame();
            break;
        case 'c':
            changeColor();
            break;
    }

    for(int i = 8; i < 35; i++)
    {
        frame.setColor(color);
        if(i % 2 == 0 && i > 8)
        {
            frame.plot(39, i, LEFT);
        }
    }

    if ((p1.gety() - 2 == 10 || p2.gety() - 2 == 10) || (p1.gety() + 2 == 33 ||p2.gety() + 2 == 33))
    {
        for(int i = 0; i < 79; i++)
        {

            frame.plot(i, 8, BOTTOM);
            frame.plot(i, 35, BOTTOM);
        }
    }

    p.setColor((ink)(((int)color + 1) % 16));
    if(color == black)
        p.setColor((ink)(((int)color + 1) % 16));
    drawPaddle1();
    p.setColor((ink)(((int)color + 1) % 16));
    if(color == black)
        p.setColor((ink)(((int)color + 1) % 16));
    drawPaddle2();
}

void pong::moveBall()
{
    int x = 39, y = 20, xChange = 1, yChange = 1;
    char ch;

    while(!goal)
    {

        if((x == p1.getx() + 1 && (y == p1.gety() || y == p1.gety() - 1 || y == p1.gety() - 2 || y == p1.gety() + 1 || y == p1.gety() + 2)) || (x == p2.getx() - 1 && (y == p2.gety() || y == p2.gety() - 1 || y == p2.gety() - 2 || y == p2.gety() + 1 || y == p2.gety() + 2)))
        {
            xChange *= -1;
        }
        if(y == 34 || y == 9)
        {
            yChange *= -1;
        }
        p.setColor(color);
        p.plot(x, y, '*');
        Sleep(60);
        p.setColor(black);
        p.plot(x, y, '*');

        if (x == 77)
        {
            p.setColor(black);
            drawPaddle1();
            drawPaddle2();
            p1Goal();
        }
        if (x == 0)
        {
            p.setColor(black);
            drawPaddle1();
            drawPaddle2();
            p2Goal();
        }
        x += xChange;
        y += yChange;

        update( ch );

        if( _kbhit() )
        {
            ch = _getch();

            update( ch );
        }
    }
}

void pong::startGame()
{
    pong game;

    game.resetScore();
    game.newGame();
    game.moveBall();
}

void pong::consoleSize(int columns, int rows)
{
    _COORD coord;
    coord.X = columns;
    coord.Y = rows;

    _SMALL_RECT rect;
    rect.Top = 0;
    rect.Left = 0;
    rect.Bottom = rows - 1;
    rect.Right = columns - 1;

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleScreenBufferSize(handle, coord);
    SetConsoleWindowInfo(handle, TRUE, &rect);
}
