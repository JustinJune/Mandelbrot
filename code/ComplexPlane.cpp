#include "ComplexPlane.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>
#include <complex>

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
    stringstream display;
    
    display << "  Mandelbrot Set" << endl << "  Center: (" << (m_view.getCenter().x)<< "," << (m_view.getCenter().y) << ")" << endl 
    << "  Cursor: (" << m_mouseLocation.x <<"," << m_mouseLocation.y << ")" << endl<< "  Left-click to Zoom in" << endl << "  Right-click to Zoom out" << endl;
    
    //display << name << center << cursor << direction_left << direction_right;
    
    text.setString(display.str());
}

size_t ComplexPlane::countIterations(Vector2f coord)
{
    double re = coord.x;
    double im = coord.y;
    complex<double> z (0, 0);
    complex<double> c (re, im);

    size_t i;

    for (i = 0; i < MAX_ITER && abs(z) <= 2.0; i++)
    {
        z = pow(z, 2) + c;
    }
    
    return i;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8 &r, Uint8 &g, Uint8 &b)
{
    if (count < 13)
    {
        r = 102;
        g = 0;
        b = 255;
    }

    else if (count >= 13 && count < 26)
    {
        r = 0;
        g = 190;
        b = 255;
    }

    else if (count >= 26 && count < 39)
    {
        r = 0;
        g = 255;
        b = 90;
    }

    else if (count >= 39 && count < 52)
    {
        r = 250;
        g = 255;
        b = 0;
    }

    else if( count >= 52 && count < 64)
    {
        r = 255;
        g = 25;
        b = 0;
    }

    else
    {
        r = 0;
        g = 0;
        b = 0;
    }
}
