/*** GRAPHIC LIBRARY (CMD OUTPUT) ***/

#ifndef GRAPHICD3_H_INCLUDED
#define GRAPHICD3_H_INCLUDED

#ifndef IOSTREAM_INCLUDED
#define IOSTREAM_INCLUDED
#include <iostream>
#endif // IOSTREAM_INCLUDED

#ifndef WINDOWS_H_INCLUDED
#define WINDOWS_H_INCLUDED
#include <windows.h>
#endif // WINDOWS_H_INCLUDED

#ifndef CONIO_H_INCLUDED
#define CONIO_H_INCLUDED
#include <conio.h>
#endif // CONIO_H_INCLUDED

/*** S T A R T ***/

#define getMax(a,b) a>b?a:b
#define getMin(a,b) a<b?a:b


//#define GenericEntity1 Point

namespace grph
{
	const short ESC=27,TAB=9,BACKSPACE=8;
	const short F1=59,F2=60,F3=61,F4=62,F5=63,F6=64,F7=65,F8=66,F9=67,F10=68,F11=-123,F12=-122,ENTER=13;
	const short LEFT_ARROW=75,UP_ARROW=72,RIGHT_ARROW=77,DOWN_ARROW=80;

    class  GenericEntity1;
    class  GenericEntity2;

    class  Console;
    class  Grid;
    class  Point;
    class  Pixel;
    class  Entity;
    class  Object;
    struct Dialogue;
    struct Page;
    struct Line;
}

/***    LINE    ***/

struct grph::Line
{
    short wait;
    short color;
    std::string txt;
};

/***    PAGE    ***/

struct grph::Page
{
    grph::Line lines[4];
};

/***    DIALOGUE    ***/

struct grph::Dialogue
{
    grph::Page pages[5];
    short numOfPages;
};

/***    GENERIC ENTITY 1    ***/

class grph::GenericEntity1
{
public:
    GenericEntity1 (short x = 0,short y = 0) {this->x = x; this->y = y;}

    virtual void  set  (grph::GenericEntity1 ge) {this->x = ge.getX(); this->y = ge.getY();}
    virtual void  setX (short x = 0) {this->x = x;}
    virtual void  setY (short y = 0) {this->y = y;}

    virtual grph::GenericEntity1 get () {return grph::GenericEntity1(this->x,this->y);}
    virtual short getX         () {return this->x;}
    virtual short getY         () {return this->y;}

    virtual void incrsX (short n = 1) {this->x += n;}
    virtual void incrsY (short n = 1) {this->y += n;}
    virtual void decrsX (short n = 1) {this->x -= n;}
    virtual void decrsY (short n = 1) {this->y -= n;}

protected:
    short x,y;
};

/***    GENERIC ENTITY 2    ***/

class grph::GenericEntity2 : public grph::GenericEntity1
{
public:
    GenericEntity2(short x = 0,short y = 0,short color = 0,char txt = ' ');

    virtual void setColor (short color = 0) {this->color = color;}
    virtual void setTxt   (char txt = ' ')  {this->txt = txt;}

    virtual short getColor () {return this->color;}
    virtual char  getTxt   () {return this->txt;}

    virtual bool  nextPxlIs (grph::Grid grid,char mode,short color,char txt);

protected:
    short color;
    char txt;
};

/***    POINT    ***/

class grph::Point : public grph::GenericEntity1
{
public:
    Point (short x = 0,short y = 0);

    operator = (grph::GenericEntity1 ge1);
};

/***    PIXEL    ***/

class grph::Pixel
{
public:
    friend class grph::Grid;

    Pixel(short color = 0,char txt = ' ') {this->color = color; this->txt = txt;}

    void  setColor (short color) {this->color = color;}
    void  setTxt   (char txt)    {this->txt = txt;}

    short getColor () {return this->color;}
    char  getTxt   () {return this->txt;}

private:
    short color;
    char txt;
};

/***    ENTITY    ***/

class grph::Entity : public grph::GenericEntity2
{
public:
    Entity(short x = 0,short y = 0,short color = 0,char txt = ' ',char facing = '0');

    void setFacing (char facing) {this->facing = facing;}

    char getFacing () {return this->facing;}


protected:
    char facing;
};

/***    CONSOLE    ***/

class grph::Console
{
public:
    static void cls         () {system("cls");}
    static void pause       () {getch();}
    static void setOutColor (short color);
};

/***    GRID    ***/

class grph::Grid
{
public:
    Grid(short x=1,short y=1) {this->x = x; this->y = y;}

    void set(short x,short y) {this->x = x; this->y = y;}

    void setX(short x) {this->x = x;}
    void setY(short y) {this->y = y;}

    short getX() {return x;}
    short getY() {return y;}

    short getPxlClr(short x,short y) {return pixels[x][y].color;}
    char  getPxlTxt(short x,short y) {return pixels[x][y].txt;}

    void setup(short color,char txt);
    void paint();

    void drawpnt(grph::GenericEntity1 p,short color,char txt);
    void drawnty(grph::Entity e);
    void drawobj(grph::Object o);

    void fill(grph::Point p1,grph::Point p2,short color,char txt);
    void line(grph::Point p1,grph::Point p2,short color,char txt);
    void square(grph::Point p1,grph::Point p2,short color,char txt);


private:
    grph::Pixel pixels[100][100];
    short x,y;
};

/***    OBJECT    ***/

class grph::Object : public grph::Entity
{
public:
    Object(short x = 0,short y = 0,short color = 0,char txt = ' ',char facing = '0');

    void addDialogue(short dialogue,short numOfPages) {dialogues[dialogue].numOfPages = numOfPages;}

    void setDialogue(short dialogue,short numOfPage,const std::string lines[4],short wait = 50,short color = 07);

    void tellDialogue(short dialogue,grph::Grid grid);

    short getDialogueColor(short dialogue,short page,short line) {return dialogues[dialogue].pages[page].lines[line].color;}

    std::string getDialogueTxt(short dialogue,short page,short line) {return dialogues[dialogue].pages[page].lines[line].txt;}

    short getDialogueWait(short dialogue,short page) {return dialogues[dialogue].pages[page].lines[0].wait;}

private:
    grph::Dialogue dialogues[3];
    short defDiaColor;
};

/***  ***/

grph::GenericEntity2::GenericEntity2 (short x,short y,short color,char txt)
:
    grph::GenericEntity1(x,y),
    color(color),
    txt(txt)
{

}

bool grph::GenericEntity2::nextPxlIs (grph::Grid grid,char mode,short color,char txt)
{
    short xx = this->x, yy = this->y;

    if(mode=='w')
    {
        yy--;
    }

    if(mode=='a')
    {
        xx--;
    }
    if(mode=='s')
    {
        yy++;
    }
    if(mode=='d')
    {
        xx++;
    }



    if(grid.getPxlClr(xx,yy) == color && grid.getPxlTxt(xx,yy) == txt) return true;

    return false;
}

/***  ***/

inline grph::Point::Point (short x,short y)
:
    grph::GenericEntity1(x,y)
{

}

grph::Point::operator = (grph::GenericEntity1 ge1)
{
    this->x = ge1.getX();
    this->y = ge1.getY();
}

/***  ***/

grph::Entity::Entity (short x,short y,short color,char txt,char facing)
:
    GenericEntity2(x,y,color,txt),
    facing(facing)
{

}

/***  ***/

void grph::Console::setOutColor (short color)
{
    using namespace std;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
}

/***  ***/

void grph::Grid::setup (short color,char txt)
{
    for(short j = 0; j < y; j++)
    {
        for(short i = 0; i < x; i++)
        {
            this->pixels[i][j].color=color;
            this->pixels[i][j].txt=txt;
        }
    }
}

void grph::Grid::paint ()
{
    short i,j,lastcolor;
    for(j=0;j<y;j++)
    {
        for(i=0;i<x;i++)
        {
            if(pixels[i][j].color != lastcolor) {Console::setOutColor(pixels[i][j].color); lastcolor = pixels[i][j].color;}

            std::cout << pixels[i][j].txt;
        }
        std::cout<<'\n';
    }
}

void grph::Grid::drawpnt (grph::GenericEntity1 p,short color,char txt)
{
    pixels[p.getX()][p.getY()].color = color;
    pixels[p.getX()][p.getY()].txt = txt;
}

void grph::Grid::drawnty (grph::Entity e)
{
    pixels[e.getX()][e.getY()].color = e.getColor();
    pixels[e.getX()][e.getY()].txt = e.getTxt();
}

void grph::Grid::drawobj (grph::Object o)
{
    pixels[o.getX()][o.getY()].color = o.getColor();
    pixels[o.getX()][o.getY()].txt = o.getColor();
}

void grph::Grid::fill (grph::Point p1,grph::Point p2,short color,char txt)
{
    short x1 = p1.getX();
    short y1 = p1.getY();
    short x2 = p2.getX();
    short y2 = p2.getY();

    for(short j = y1; j <= y2; j++)
    {
        for(short i = x1; i <= x2; i++)
        {
            pixels[i][j].color = color;
            pixels[i][j].txt = txt;
        }
    }
}

void grph::Grid::line (grph::Point p1,grph::Point p2,short color,char txt)
{
    using std::cout;

    short x1 = p1.getX();
    short y1 = p1.getY();
    short x2 = p2.getX();
    short y2 = p2.getY();

    short X = (x2 - x1) + 1;
    short Y = ((getMax(y1,y2)) - (getMin(y1,y2))) + 1;

    if(y1 == y2)
    {
        for(x1; x1 <= x2; x1++)
        {
            //cout << x1 << " ; " << y1 << endl;
            this->pixels[x1][y1].color = color;
            this->pixels[x1][y1].txt = txt;
        }
    }
    else
    {
        if(x1 == x2)
        {
            for(y1; y1 <= y2; y1++)
            {
                //cout << x1 << " ; " << y1 << endl;
                this->pixels[x1][y1].color = color;
                this->pixels[x1][y1].txt = txt;
            }
        }
        else
        {
            if(X >= Y)
            {
                if(y2 > y1)
                {
                    for(x1; x1 <= x2;)
                    {
                        for(short i = 0; i < X / Y; i++)
                        {
                            //cout << x1 << " ; " << y1 << endl;
                            this->pixels[x1][y1].color = color;
                            this->pixels[x1][y1].txt = txt;

                            x1++;
                        }

                        y1++;
                    }
                }
                else
                {
                    if(y1 > y2)
                    {
                        for(x1; x1 <= x2;)
                        {
                            for(short i = 0; i < X / Y; i++)
                            {
                                //cout << x1 << " ; " << y1 << endl;
                                this->pixels[x1][y1].color = color;
                                this->pixels[x1][y1].txt = txt;

                                x1++;
                            }

                            y1--;
                        }
                    }
                }
            }
            else
            {
                if(Y > X)
                {
                    if(y2 > y1)
                    {
                        for(x1; x1 <= x2;)
                        {
                            for(short i = 0; i < Y / X; i++)
                            {
                                //cout << x1 << " ; " << y1 << endl;
                                this->pixels[x1][y1].color = color;
                                this->pixels[x1][y1].txt = txt;

                                y1++;
                            }

                            x1++;
                        }
                    }
                    else
                    {
                        if(y1 > y2)
                        {
                            for(x1; x1 <= x2;)
                            {
                                for(short i = 0; i < Y / X; i++)
                                {
                                    //cout << x1 << " ; " << y1 << endl;
                                    this->pixels[x1][y1].color = color;
                                    this->pixels[x1][y1].txt = txt;

                                    y1--;
                                }

                                x1++;
                            }
                        }
                    }
                }
            }
        }
    }
}

void grph::Grid::square (grph::Point p1,grph::Point p2,short color,char txt)
{
    short x1 = p1.getX();
    short y1 = p1.getY();
    short x2 = p2.getX();
    short y2 = p2.getY();

    line(Point(x1,y1),Point(x2,y1),color,txt);
    line(Point(x1,y1),Point(x1,y2),color,txt);
    line(Point(x2,y1),Point(x2,y2),color,txt);
    line(Point(x1,y2),Point(x2,y2),color,txt);
}


/***  ***/

grph::Object::Object (short x,short y,short color,char txt,char facing)
:
    grph::Entity(x,y,color,txt,facing)
{

}

void grph::Object::setDialogue (short dialogue,short numOfPage,const std::string lines[4],short wait,short color)
{
    for(short i=0;i<4;i++)
    {
        this->dialogues[dialogue].pages[numOfPage].lines[i].txt = lines[i];
        this->dialogues[dialogue].pages[numOfPage].lines[i].color = color;
        this->dialogues[dialogue].pages[numOfPage].lines[i].wait = wait;
    }
}

void grph::Object::tellDialogue (short dialogue,grph::Grid grid)
{
    short i,j;
    for(j=0;j<dialogues[dialogue].numOfPages;i++)
    {
        for(i=0;i<4;i++)
        {
            grph::Console::setOutColor(dialogues[dialogue].pages[j].lines[i].color);
            std::cout << dialogues[dialogue].pages[j].lines[i].txt << std::endl;
            Sleep(dialogues[dialogue].pages[j].lines[i].wait);
        }
        if(GetAsyncKeyState(grph::ESC))
            break;
        grph::Console::cls();
        grid.paint();
    }
}



/*** E N D ***/

#endif // GRAPHICD3_H_INCLUDED
