#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <iostream>

int main()
{
    // creating window
    sf::RenderWindow window(sf::VideoMode(800,600),"Pong Game");
    
    // setting the frame rate limit
    window.setFramerateLimit(60);

    std::cout << "Game started" << std::endl;

    //Font file
    sf::Font font;
    if(font.loadFromFile("Data/arial.ttf") == false)
    {
        // code failing msg
        return 1;
    }

    sf::Text score;
    score.setFont(font);
    score.setCharacterSize(30);
    score.setFillColor(sf::Color(255,0,0));
    score.setPosition(380,10);
    score.setString("0 : 0");

    // Images
    sf::Texture text_pad;
    sf::Texture text_ball;
    sf::Texture background;

    if(text_pad.loadFromFile("Data/pad.png") == false)
    {
        return 1;
    }

    if(text_ball.loadFromFile("Data/ball.png") == false)
    {
        return 1;
    }

    if(background.loadFromFile("Data/background.png") == false)
    {
        return 1;
    }

    //Sound
    sf::SoundBuffer buf;
    if(buf.loadFromFile("Data/hit.wav") == false)
    {
        return 1;
    }
    sf::Sound hit;
    hit.setBuffer(buf);

    //states
    bool up=false,down=false;

    //variables
    int yvelp1=0,yvelp2=0;
    int xvelBall = -4,yvelBall = -4;
    int pad1Score = 0,pad2Score=0;

    //shape
    // Background
    sf::RectangleShape back(sf::Vector2f(800,600));
    back.setPosition(0,0);
    back.setTexture(&background);

    //pad1
    sf::RectangleShape pad1(sf::Vector2f(50,100));
    pad1.setPosition(50,200);
    pad1.setTexture(&text_pad);

    //pad2
    sf::RectangleShape pad2(sf::Vector2f(50,100));
    pad2.setPosition(700,200);
    pad2.setTexture(&text_pad);

    //ball
    sf::RectangleShape ball(sf::Vector2f(50,50));
    ball.setPosition(400,200);
    ball.setTexture(&text_ball);

    while(window.isOpen())
    {
        // Event part on the main game loop
        sf::Event event;
        while(window.pollEvent(event))
        {
            //Process events
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }

            //Key Pressed
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
            {
                up = true;
            }
            
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
            {
                down = true;
            }

            //Key Released
            if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Up) 
            {
                up = false;
            }

            if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Down)
            {
                down = false;
            }
        }

        //Logic
        //Pad1
        if(up == true) 
        {
            yvelp1= -5;
        }
        
        if(down == true) 
        {
            yvelp1=5;
        }
        
        if(up == true && down==true) 
        {
            yvelp1=0;
        }
        
        if(up == false && down==false)
        {
            yvelp1=0;
        }

        pad1.move(0,yvelp1);

        //Out of bounds check
        if(pad1.getPosition().y < 0)
        {
            pad1.setPosition(50,0);
        }

        if(pad1.getPosition().y > 500)
        {
            pad1.setPosition(50,500);
        }

        //Pad2
        if(ball.getPosition().y < pad2.getPosition().y)
        {
            yvelp2 = -3;
        }
        
        if(ball.getPosition().y > pad2.getPosition().y)
        {
            yvelp2 = 3;
        }

        pad2.move(0,yvelp2);

        //Ball
        ball.move(xvelBall,yvelBall);

        //Out of bounds check
        if(ball.getPosition().y < 0)
        {
            yvelBall *= -1;
        }

        if(ball.getPosition().y > 550)
        {
            yvelBall *= -1;
        }

        if(ball.getPosition().x < -50)
        {
            pad2Score++;
            ball.setPosition(300,200);
        }

        if(ball.getPosition().x > 800)
        {
            pad1Score++;
            ball.setPosition(300,200);
        }

        //Collision with pad1
        if(ball.getGlobalBounds().intersects(pad1.getGlobalBounds()) == true)
        {
            xvelBall *= -1;
            hit.play();
        }

        //Collision with pad2
        if(ball.getGlobalBounds().intersects(pad2.getGlobalBounds()) == true)
        {
            xvelBall *= -1;
            hit.play();
        }

        // Rendering
        window.clear();


        //Draw things
        window.draw(back);
        window.draw(pad1);
        window.draw(pad2);
        window.draw(ball);
        window.draw(score);
        
        //Score
        std::stringstream text;
        text << pad1Score << " : " << pad2Score;
        score.setString(text.str());

        window.draw(score);
        window.display();
    }
return 0;
}