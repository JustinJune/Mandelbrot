#ifndef ComplexPlane_H
#define ComplesPlane_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <vector>

using namespace sf;
using namespace std;

class ComplexPlane
{
    public:
    ComplexPlane(float aspectRatio);
    void zoomIn();
    void zoomOut();
    void setCenter(Vector2f coord);
    View getView();
    void setMouseLocation(Vector2f coord);
    void loadText(Text& text);
    size_t countIterations(Vector2f coord);
    void iteratioonsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b);

    private:
    Vector2f m_mouseLocation;
    View m_view;
    int m_zoomCount;
    float m_aspectRatio;


};




#endif