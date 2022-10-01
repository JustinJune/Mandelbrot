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
    //Get user's Screen Size
    //Calculate Ratio of their Screen
    float width = VideoMode::getDesktopMode().width;
    float height = VideoMode::getDesktopMode().height;
    float aspect_ratio = height / width;

    //Create a ComplexPlane object
    ComplexPlane view1(aspect_ratio);

    //Construct Font and Text objects
    Font font;
    Text text;

    //If font is unable to be loaded; print error
    if (!font.loadFromFile("KOMIKAP_.ttf"))
    {
        cout << "Error: Font File Not Found" << endl;
    }
    
    //Set font, color, and size
    text.setFont(font);
    text.setFillColor(Color::White);
    text.setCharacterSize(24);

    //Create VertexArray for background
    //Set primitive types to points
    VertexArray vArray;
    vArray.setPrimitiveType(Points);
    vArray.resize(width * height);

    //Create VideoMode object
    VideoMode vm(width, height);
    RenderWindow window (vm, "Mandelbrot", Style::Default);

    //Create enum class with 2 variable states
    enum class States
    {
        DISPLAYING, CALCULATING
    };
    //Initialize state to CALCULATING
    States calculating = States::CALCULATING;
    
    //Beging main loop
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
                    view1.setCenter(window.mapPixelToCoords(Mouse::getPosition(window)));
                    calculating = States::CALCULATING;
                }
                
                else if(event.mouseButton.button == Mouse::Left)
                {
                    view1.zoomIn();
                    view1.setCenter(window.mapPixelToCoords(Mouse::getPosition(window)));
                    calculating = States::CALCULATING;
                }
            }

            if (event.type == Event::MouseMoved)
            {
                view1.setMouseLocation(window.mapPixelToCoords(Mouse::getPosition(window)));
            }

            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
            window.close();
            }
        }
        
        if (calculating == States::CALCULATING)
        {
            for (size_t j = 0; j < height; j++)
            {
                for (size_t i = 0; i < width; i++)
                {
                    vArray[j + i * width].position = {(float)j,(float)i};
                }
            }
        }


    }
    
}