#include<sstream>
#include<string>
#include<conio.h>
#include<windows.h>
#include<iostream>
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Window/Mouse.hpp>
#include<SFML/Window/Keyboard.hpp>
using namespace std;
enum dir
{
    STOP = 0,
    LEFT = 1,
    UPLEFT =2,
    DOWNLEFT = 3,
    RIGHT = 4,
    UPRIGHT = 5,
    DOWNRIGHT = 6,
};

class pedal
{
public:    int x0,y0,x1,y1;
};

class myball
{
    int originalx, originaly, originalr;
public:
    int getx(){return originalx;}
    int gety(){return originaly;}
    int getr(){return originalr;}
    myball()
    {
        originalx=350;
        originaly=200;
        originalr=10;
    }
};

string IntToString ( int number )
{
  std::ostringstream oss;

  // Works just like cout
  oss<< number;

  // Return the underlying string
  return oss.str();
}

int main()
{
    int restart=0, repeat=0;
    sf::RenderWindow win(sf::VideoMode(700, 450,32), "PING PONG",sf::Style::Close|sf::Style::Resize);
    sf::SoundBuffer bounce, music;

    if(!bounce.loadFromFile("bounce.wav"))
        return -1;

    if(!music.loadFromFile("Soft Trance - Ather - YouTube(0).wav"))
        return -1;


    sf::Sound bounceobj;
    bounceobj.setBuffer(bounce);
    bounceobj.play();

    sf::Sound musicobj;
    musicobj.setBuffer(music);
    musicobj.play();

    srand(time(NULL));
    dir direction=(dir)((rand()%6)+1);
    myball b1;
    pedal p1,p2;
    p2.x0=680;  p2.y0=150; p2.x1=690;  p2.y1=265;
    p1.x0=10;  p1.y0=150; p1.x1=20;  p1.y1=265;
    int  p1move, p2move, cx=b1.getx(),cy=b1.gety(), cr=b1.getr(); float speed=0.152;
    int sizex=10,sizey=80;     /// padle size///
    char player1=0, player2=0;
    int check=1;
    float angle;
    angle=(float)(rand()%5+1)/10;

    sf::Texture texture, texturepadle, texturetable,texturemenu, texturewall;
    texture.loadFromFile("download (1).png");
    texturepadle.loadFromFile("padle.jpg");
    texturetable.loadFromFile("table1.jpg");
    texturemenu.loadFromFile("apps.25478.9007199266308677.bbad0874-cc12-42c9-9672-a45f822d9018.png");
    texturewall.loadFromFile("e9Ogsbf.png");

    sf::CircleShape circle(15);/// Ball
    circle.setTexture(&texture);
    circle.setPosition(340,190);

    sf::RectangleShape padle1(sf::Vector2f(sizex,sizey));/// paddles
    padle1.setPosition(p1.x0,p1.y0);
    sf::RectangleShape padle2(sf::Vector2f(sizex,sizey));
    padle2.setPosition(p2.x0,p2.y0);
    padle1.setTexture(&texturepadle);
    padle2.setTexture(&texturepadle);


    sf::RectangleShape upside(sf::Vector2f(700, 15));/// Boundaries
    upside.setPosition(0,0);
    sf::RectangleShape downside(sf::Vector2f(700, 15));
    downside.setPosition(0,385);
    downside.setTexture(&texturewall);
    upside.setTexture(&texturewall);

    sf::RectangleShape table(sf::Vector2f(700,370)); /// Table
    table.setPosition(0,15);
    table.setTexture(&texturetable);

    sf::RectangleShape menu(sf::Vector2f(700,400));
    menu.setPosition(0,0);
    menu.setTexture(&texturemenu);



    sf::Font font;
    font.loadFromFile("mymy.ttf");
    sf::Text text;
    text.setFont(font);
    text.setString("HIT E for Easy OR H for Hard");
    text.setCharacterSize(35);
    text.setColor(sf::Color::White);
    text.setPosition(300,405);


    sf::Text text2;
    text2.setFont(font);
    text2.setCharacterSize(35);
    text2.setColor(sf::Color::White);
    text2.setPosition(30,405);

    sf::Text text3;
    text3.setFont(font);
    text3.setCharacterSize(35);
    text3.setColor(sf::Color::White);
    text3.setPosition(600,405);


    string str1;
    string str2;

replay:
    text.setString("HIT E for Easy OR H for Hard");
    while (win.isOpen())
    {
        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                win.close();
            }
            if(event.type==sf::Event::TextEntered)
            {
                if(event.text.unicode<128)
                cout<<(char)event.text.unicode;
            }
        }

        sf::Vector2i mice;
        mice = sf::Mouse::getPosition(win);

        //cout<<" \n check \n" ;
        if(check)
        {
            there:
            win.clear();
            win.draw(menu);
            win.display();
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                cout<<"mouse : "<<mice.x<<" "<<mice.y<<endl;
                if(mice.x>253 && mice.x<439 && mice.y>152 && mice.y<170)
                {
                    while (win.isOpen())
                    {
                        sf::Event event;
                        while (win.pollEvent(event))
                            {
                                if (event.type == sf::Event::Closed)
                                    {
                                        win.close();
                                    }
                            }
                            cout<<" inloop:;'";
                        win.draw(text);
                        win.display();
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)){sizey=130; padle1.setScale(1,1.625); padle2.setScale(1,1.625); break;}
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H)){sizey=80; padle1.setScale(1,1); padle2.setScale(1,1); break;}

                    }

                    text.setString("SCORE");
                    check=0;
                    goto again;
                }



                else if(mice.x>258 && mice.x<418&& mice.y>197&&mice.y<211){check=0; goto quit;}
            }
            else goto there;
        }
    }

    again:
        circle.setPosition(340,190);
        win.draw(circle);
        win.display();
        win.clear();
        win.draw(upside);
        win.draw(downside);
        win.draw(table);
        win.draw(circle);
        win.draw(text);
        win.draw(text2);
        win.draw(text3);
        win.draw(padle1);
        win.draw(padle2);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)){
    direction=(dir)((rand()%6)+1);
    circle.setPosition(340,190); goto uza;
    }
    else goto again;
    uza:
game:
    while (win.isOpen())
    {
            win.draw(text);

        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                win.close();
            }
            if(event.type==sf::Event::TextEntered)
            {
                if(event.text.unicode<128)
                cout<<(char)event.text.unicode;
            }
        }
        sf::Vector2i mice;
        mice = sf::Mouse::getPosition(win);
        sf::Vector2f p1 = padle1.getPosition();
        sf::Vector2f p2 = padle2.getPosition();
        sf::Vector2f pos = circle.getPosition();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))/// down p1
        {
            if(p1.y<=385-sizey)
             {padle1.move(0,0.25);}
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))/// up p1
        {
            if(p1.y >=15)
            {padle1.move(0,-0.25);}
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L))/// down p2
        {
            if(p2.y<=385-sizey)
             {padle2.move(0,0.25);}
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))/// up p2
        {
            if(p2.y >=15)
            {padle2.move(0,-0.25);}
        }
        win.clear();
        win.draw(upside);
        win.draw(downside);
        win.draw(table);
        win.draw(circle);
        win.draw(text);
        win.draw(text2);
        win.draw(text3);
        win.draw(padle1);
        win.draw(padle2);

//        cout<<endl<<"padle 1: "<<p1.x<<" "<<p1.y;
//        cout<<endl<<"padle 2: "<<p2.x<<" "<<p2.y;
//        cout<<endl<<"circle : "<<pos.x<<" "<<pos.y;

        if(pos.x<0||pos.x>700)
        {
            if(player1>=5||player2>=5){check=1; player1=player2=0; restart++; goto replay;}
            if(pos.x>700){player1++; goto again;}
            if(pos.x<-40){player2++; goto again;}
        }


        if(direction==LEFT){circle.move(-speed-angle+0.07,0); } ///moving ball..
        if(direction==UPLEFT){circle.move(-speed-angle,-speed); }
        if(direction==DOWNLEFT){circle.move(-speed-angle,speed); }
        if(direction==RIGHT){circle.move(speed+angle-0.07,0); }
        if(direction==UPRIGHT){circle.move(speed+angle,-speed); }
        if(direction==DOWNRIGHT){circle.move(speed+angle,speed); }

        if(direction==UPLEFT && pos.y<=14){direction=DOWNLEFT; bounceobj.play();} /// bouncing ball from the walls///
        if(direction==UPRIGHT && pos.y<=14){direction=DOWNRIGHT; bounceobj.play();}
        if(direction==DOWNLEFT && pos.y>=360){direction=UPLEFT; bounceobj.play();}
        if(direction==DOWNRIGHT && pos.y>=360){direction=UPRIGHT; bounceobj.play();}

        if(pos.x<=15)/// bouncing ball from the PADLES///
            {
                if(pos.y<=p1.y+sizey-60 && pos.y>=p1.y-15)
                    {
                        direction=UPRIGHT;
                        bounceobj.play();
                        if(pos.y>p1.y+8)
                            {
                                speed+=0.04;
                            }
                    }
                if(pos.y<=p1.y+sizey && pos.y>p1.y+sizey-20)
                    {
                        direction=DOWNRIGHT;
                        bounceobj.play();
                        if(pos.y>p1.y+8)
                            {
                                speed+=0.04;
                            }
                    }

                if(pos.y<=p1.y+sizey-20 && pos.y>p1.y+sizey-60)
                    {
                        if(pos.y>=p1.y+sizey-50&&pos.y<=p1.y+sizey-30){direction=RIGHT;bounceobj.play();speed-=0.02;}
                        else if(direction==UPLEFT){direction=UPRIGHT;bounceobj.play();speed-=0.02;}
                        else if(direction==DOWNLEFT){direction=DOWNRIGHT;bounceobj.play();speed-=0.02;}
                        else {direction=RIGHT;bounceobj.play();}
                    }
                    angle=(float)(rand()%5+1)/10;
            }
        if(pos.x>=660)
            {
                if(pos.y<p2.y+sizey-60 && pos.y>=p2.y-15)
                    {
                        direction=UPLEFT;
                        bounceobj.play();
                        if(pos.y>p1.y+8)
                            {
                                speed+=0.04;
                            }
                    }
                if(pos.y<=p2.y+sizey && pos.y>p2.y+sizey-20)
                    {
                        direction=DOWNLEFT;
                        bounceobj.play();
                        if(pos.y>p1.y+8)
                            {
                                speed+=0.04;
                            }
                    }
                if(pos.y<=p2.y+sizey-20 && pos.y>=p2.y+sizey-60)
                    {
                        if(pos.y>=p2.y+sizey-50&&pos.y<=p2.y+sizey-30){direction=LEFT; bounceobj.play();speed-=0.02;}
                        else if(direction==UPRIGHT){direction=UPLEFT;bounceobj.play(); speed-=0.02;}
                        else if(direction==DOWNRIGHT){direction=DOWNLEFT;bounceobj.play();speed-=0.02;}
                         else {direction=LEFT;bounceobj.play();}
                    }
                    angle=(float)(rand()%5+1)/10;
            }

            if(speed>0.20){speed-=0.05;}
            if(speed<0.17){speed+=0.05;}
            win.display();
            str1=IntToString(player1);
            text2.setString(str1);
            str2=IntToString(player2);
            text3.setString(str2);
            cout<<"\n speed: "<<speed<<endl;
    }
    quit:
    return 0;
}
