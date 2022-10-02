#include "ComplexPlane.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>

using namespace sf;
using namespace std;

ComplexPlane::ComplexPlane(float aspectRatio)
{
    m_aspectRatio = aspectRatio;
    m_view.setSize(BASE_WIDTH, BASE_HEIGHT * m_aspectRatio);
    m_view.setCenter(0.0, 0.0);
    m_zoomCount = 0;
}

void ComplexPlane::zoomIn()
{
    m_zoomCount++;
    float x_size, y_size;

    x_size = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
    y_size = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);

    m_view.setSize(x_size, y_size);
}

void ComplexPlane::zoomOut()
{
    m_zoomCount--;
    float x_size, y_size;

    x_size = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
    y_size = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);

    m_view.setSize(x_size, y_size);
}

void ComplexPlane::setCenter(Vector2f coord)
{
    m_view.setCenter(coord);
}

View ComplexPlane::getView()
{
    return m_view;
}

void ComplexPlane::setMouseLocation(Vector2f coord)
{
    m_mouseLocation = coord;
}

void ComplexPlane::loadText(Text &text)
{
    stringstream center, cursor, name, direction_left, direction_right;
    
    name << "Mandelbrot Set";
    center << "Center: (" << m_view.getCenter().x << "," << m_view.getCenter().y << ")";
    cursor << "Cursor: (" << m_mouseLocation.x <<"," << m_mouseLocation.y << ")";
    direction_left << "Left-click to Zoom in";
    direction_right << "Right-click to Zoom out";

    text.setString(name.str());
    text.setString(center.str());
    text.setString(cursor.str());
    text.setString(direction_left.str());
    text.setString(direction_right.str());
}

size_t ComplexPlane::countIterations(Vector2f coord)
{
    
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8 &r, Uint8 &g, Uint8 &b)
{
    
}
