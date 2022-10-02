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
    ComplexPlane view(aspect_ratio);

    //Construct Font and Text objects
    Font font;
    Text text;

    //If font is unable to be loaded; print error
    if (!font.loadFromFile("fonts/KOMIKAP_.ttf"))
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
    States state = States::CALCULATING;

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
                    view.zoomOut();
                    view.setCenter(window.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y)));
                    state = States::CALCULATING;
                }
                
                else if(event.mouseButton.button == Mouse::Left)
                {
                    view.zoomIn();
                    view.setCenter(window.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y)));
                    state = States::CALCULATING;
                }
            }

            if (event.type == Event::MouseMoved)
            {
                view.setMouseLocation(window.mapPixelToCoords(Mouse::getPosition(window)));
            }

            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                window.close();
            }
        }
        
        //Update Scene

        if (state == States::CALCULATING)
        {
            for (size_t j = 0; j < height; j++)
            {
                for (size_t i = 0; i < width; i++)
                {
                    vArray[j + i * width].position = {(float)j,(float)i};
                    
                    size_t count = view.countIterations(window.mapPixelToCoords(Vector2i(j, i)));

                    Uint8 r, g, b;
                    view.iterationsToRGB(count, r, g, b);
                    vArray[j  +  i * width].color = {r, g, b};
                    
                    state = States::DISPLAYING;
                    view.loadText(text);
                }
            }
        }

        window.clear();

        window.draw(vArray);
        window.draw(text);

        window.display();
    }
    
    return 0;
}