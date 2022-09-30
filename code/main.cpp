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

    font.loadFromFile("KOMIKAP_.ttf");
    text.setFont(font);

    Vector2f VertexArray;




    while (window.isOpen())
    {

    }
    
}