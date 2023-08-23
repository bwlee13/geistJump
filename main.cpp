#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>

using namespace sf;

struct point {
    int x,y;
};

int main() {
    RenderWindow app(VideoMode(400, 533), "Geist Jump Game!");
    app.setFramerateLimit(60);

    Texture t1, t2, t3;
    t1.loadFromFile("assets/background.png");
    t2.loadFromFile("assets/platform.png");
    t3.loadFromFile("assets/Geist - Icon-01.png");

    Sprite sBackground(t1), sPlatform(t2), sGeist(t3);
    sGeist.setScale(0.1, 0.1);

    point platform[20];

    for (int i = 0; i < 10; i++) {
        platform[i].x = rand() % 400;
        platform[i].y = rand() % 533;
    }

    int x=100, y=100, h=200;
    float dx=0, dy=0;

    while (app.isOpen()) {
        Event e;
        while (app.pollEvent(e)) {
            if (e.type == Event::Closed){
                app.close();
            }
            if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == 3) {
                    x += 26;
                }
                else if (e.key.code == 0) {
                    x -= 26;
                }
            }
        }
    
        dy += 0.2;
        y += dy;

        if (y>500) dy = -10;

        if (y<h) {
            for (int i=0; i<10; i++) {
                y=h;
                platform[i].y = platform[i].y - dy;
                if (platform[i].y>533) {
                    platform[i].y = 0;
                    platform[i].x = rand() % 400;
                }
            }
        }

        for (int i=0; i<10; i++) {
            if ((x+50>platform[i].x) && (x+20<platform[i].x+68) && (y+70>platform[i].y) && (y+70<platform[i].y+14) && dy>0) {
                dy = -10;
            }
        }

        sGeist.setPosition(x,y);

        app.draw(sBackground);
        app.draw(sGeist);

        for (int i=0; i<10; i++) {
            sPlatform.setPosition(platform[i].x, platform[i].y);
            app.draw(sPlatform);
        }

        app.display();
    }

    return 0;
}