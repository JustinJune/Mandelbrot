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

    Vector2f VertexArray;

    VideoMode vm(width, height);
    RenderWindow window (vm, "Mandelbrot", Style::Default);
    

    while (window.isOpen())
    {

    }
    
}