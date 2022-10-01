#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "ComplexPlane.h"

//Use Namespace
using namespace std;
using namespace sf;

int main()
{
    float width = VideoMode::getDesktopMode().width;
    float height = VideoMode::getDesktopMode().height;
    float aspect_ratio = height / width;

    Font font;
    Text text;

    if (!font.loadFromFile("KOMIKAP_.ttf"))
    {
        cout << "Error: Font File Not Found" << endl;
    }
    
    text.setFont(font);
    text.setFillColor(Color::White);
    text.setFont(font);

    VertexArray background;
    background.setPrimitiveType(Points);
    background.resize(width * height);

    VideoMode vm(width, height);
    RenderWindow window (vm, "Mandelbrot", Style::Default);

    enum class States
    {
        DISPLAYING, CALCULATING
    };

    States calculating = States::CALCULATING;

    ComplexPlane view1;
    view1.ComplexPlane(aspect_ratio);
    
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyPressed)
            {
                if (event.mouseButton.button == Mouse::Right)
                {
                    view1.zoomOut();

                }
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }


    }
    
}