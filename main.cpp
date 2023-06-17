#include <iostream>
#include "graphicd3.hpp"
#include <time.h>

using namespace std;
using namespace grph;

short bullColor,wallsColor,heartColor,scoreColor,backColor,speed = 200,score = 0;
char  bullTxt,wallsTxt,heartTxt,backTxt,skip;

void menu()
{
    Console::setOutColor(07);

    cout<<"\n\t SKIP? ";
    cin>>skip;
    if(skip=='y')
    {
        srand(time(0));
        bullColor = rand() % 100;
        wallsColor = rand() % 100;
        heartColor = rand() % 100;
        scoreColor = rand() % 100;
        backColor = rand() % 100;
        bullTxt = rand() % 100;
        wallsTxt = rand() % 100;
        heartTxt = rand() % 100;
        backTxt = rand() % 100;

        return;
    }

    cout<<"\n\t COLORE BULLETS  : ";
    cin>>bullColor;
    cout<<"\n\t COLORE MURI     : ";
    cin>>wallsColor;
    cout<<"\n\t COLORE CUORE    : ";
    cin>>heartColor;
    cout<<"\n\t COLORE PUNTEGGIO: ";
    cin>>scoreColor;
    cout<<"\n\t COLORE SFONDO   : ";
    cin>>backColor;

    cout<<"\n\t TESTO  BULLETS  : ";
    cin>>bullTxt;
    cout<<"\n\t TESTO  MURI     : ";
    cin>>wallsTxt;
    cout<<"\n\t TESTO  CUORE    : ";
    cin>>heartTxt;
    cout<<"\n\t TESTO  SFONDO   : ";
    cin>>backTxt;
}
void scorePoint()
{
    if(speed-5 >= 0)
    {
        speed -= 5;
        score++;
    }
    else
    {
        Console::setOutColor(07);
        Console::cls();
        cout<<"\n\t HAI VINTO :DDD\n"<<endl;
        cin >> speed;
        exit(0);
    }
}

int main()
{
    menu();
    srand(time(0));
    Entity bulls[5];

    for(short i=0;i<5;i++)
    {
        //bulls[i].set(Point((rand() % 13)+1,0),bullColor,bullTxt);
        bulls[i].set(Point((rand() % 13) + 1, 0));
    }

    Entity plr(6,9,heartColor,heartTxt,'w');
    system("mode 15,11");
    Grid grid(15,10);

    grid.setup(backColor,backTxt);

    Point p1(0,0),p2(0,9),p3(14,0),p4(14,9);
    grid.line(p1,p2,wallsColor,wallsTxt);
    grid.line(p3,p4,wallsColor,wallsTxt);
    p1.set(Point(0,10));
    p2.set(Point(14,10));
    grid.line(p1,p2,wallsColor,wallsTxt);
    p1.set(Point(0,0));

    while(true)
    {

        //draw

        if(score < 10)
            grid.drawpnt(p1,scoreColor,char(score+48));
        else
        {
            p1.set(Point(0,0));
            grid.drawpnt(p1,scoreColor,char((score/10)+48));
            p1.set(Point(1,0));
            grid.drawpnt(p1,scoreColor,char(score%10+48));
        }

        grid.drawnty(plr);
        for(short i=0;i<5;i++)
        {
            grid.drawnty(bulls[i]);
        }

        /*
        setOutColor(07);
        cout<<"IL TUO"<<endl<<"PUNTEGGIO"<<endl<<"E' DI "<<score<<endl;
        */
        grid.paint();

        for(short i=0;i<5;i++)
        {
            grid.drawpnt(bulls[i],backColor,backTxt);
        }

        //MOVEMENT & collide

        for(short i=0;i<5;i++)
        {
            if(bulls[i].nextPxlIs(grid,'a',heartColor,heartTxt) || bulls[i].nextPxlIs(grid,'d',heartColor,heartTxt))
                scorePoint();

            if(bulls[i].nextPxlIs(grid,'s',heartColor,heartTxt))
            {
                system("cls");
                grph::Console::setOutColor(38);
                cout << "\n\n\t" << score << '\n';
                Sleep(2000);
                exit(0);
            }
            bulls[i].incrsY(1);
            if(bulls[i].getY() == grid.getY())
            {
                bulls[i].set(Point((rand()%13)+1,rand() % 2));
            }
        }
        grid.drawpnt(plr,backColor,backTxt);

        if(GetAsyncKeyState('A') && plr.nextPxlIs(grid,'a',backColor,backTxt)){
            plr.setFacing('a');
            plr.decrsX(1);
        }
        if(GetAsyncKeyState('D') && plr.nextPxlIs(grid,'d',backColor,backTxt)){
            plr.setFacing('d');
            plr.incrsX(1);
        }
        if(GetAsyncKeyState(' '))
            scorePoint();

        Sleep(speed);
        Console::cls();
    }
    grid.paint();
    getch();
}
