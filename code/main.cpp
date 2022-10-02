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
    text.setCharacterSize(14);

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

    //Begin main loop
    while (window.isOpen())
    {
        //Create event object
        Event event;

        //Handle User Input
        while (window.pollEvent(event))
        {
            //Handle ouput for user input
            if (event.type == Event::KeyPressed)
            {
                //If right clicked: zoom out, set new center,change state to calculating
                if (event.mouseButton.button == Mouse::Right)
                {
                    view.zoomOut();
                    view.setCenter(window.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y), view.getView()));
                    state = States::CALCULATING;
                }
                
                //If left clicked: zoom in, set new center, change state to calculating
                else if(event.mouseButton.button == Mouse::Left)
                {
                    view.zoomIn();
                    view.setCenter(window.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y), view.getView()));
                    state = States::CALCULATING;
                }
            }

            // Tell user the location their mouse is hovering at
            if (event.type == Event::MouseMoved)
            {
                view.setMouseLocation(window.mapPixelToCoords(Mouse::getPosition(window), view.getView()));
            }

            // Close window if user hits escape key
            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                window.close();
            }
        }
        
        //Update Scene

        if (state == States::CALCULATING)
        {
            //Create a double loop
            //j is the height and i is the width
            for (int j = 0; j < view.getView().getSize().y; j++)
            {
                for (int i = 0; i < view.getView().getSize().x; i++)
                {
                    //Set the position variable in the element VertexArray that corresponds with screen coordinate
                    vArray[j + i * width].position = {(float)j,(float)i};
                    
                    //Get iteration count and store them
                    size_t count = view.countIterations(window.mapPixelToCoords(Vector2i(j, i), view.getView()));

                    //Declare three Uint8 variables to store RGB values
                    //Call iterationsToRGB function to assign RGB values by reference
                    //Set the color variable in the element of VertexArray that corresponds with coordinate j and i
                    Uint8 r, g, b;
                    view.iterationsToRGB(count, r, g, b);
                    vArray[j  +  i * width].color = {r, g, b};
                    
                    //Change state to DISPLAYING to begin displaying text
                    //Call loadText function
                    state = States::DISPLAYING;
                    view.loadText(text);
                }
            }
        }

        //Clear everything from last frame
        window.clear();

        //Draw mandelbrot and text again
        window.draw(vArray);
        window.draw(text);

        //Display everything that was drawn
        window.display();
    }
    
    return 0;
}