#ifndef STRAT3_GRAPHICS_PAINTER_HEADER
#define STRAT3_GRAPHICS_PAINTER_HEADER

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <cstdio>

//printf("%f %f %f %f\n", b.left, b.top, b.width, b.height);

namespace constant{
    const float& pi();
}

class Painter
{
public:

    sf::Shape& shape(const float& x1, const float& y1, sf::Shape& s)
    {
        const sf::FloatRect b = s.getGlobalBounds();
        s.setPosition(x1 - b.width / 2.f, y1  - b.height / 2.f);
        return s;
    }

    const sf::CircleShape& circle(const sf::Vector2f& x1, const size_t& pts = 30) const
    {
        return circle(x1.x, x1.y, pts);
    }
    const sf::CircleShape& circle(const float& x1, const float& y1, const size_t& pts = 30) const
    {
        const sf::FloatRect b = _CircleBrush.getGlobalBounds();

        _CircleBrush.setPointCount(pts);
        _CircleBrush.setPosition(x1 - b.width / 2.f, y1  - b.height / 2.f);

        return _CircleBrush;
    }

    const sf::RectangleShape& point(const float& x1, const float& y1, const float& r = 0) const
    {
        _RectBrush.setSize({_LineTickness, _LineTickness});
        _RectBrush.setRotation(r);

        const sf::FloatRect b = _RectBrush.getGlobalBounds();
        _RectBrush.setPosition(x1 - b.width * cos(constant::pi() * r * 2.f/ 180.f) / 2.f, y1 - b.height/ 2.f);

        return _RectBrush;
    }

    const sf::RectangleShape& point(const sf::Vector2f& x1,  const float& r = 0) const
    {
        return point(x1.x, x1.y, r);
    }

    sf::RectangleShape& point(const float& x1, const float& y1, const float& r = 0)
    {
        _RectBrush.setSize({_LineTickness, _LineTickness});
        _RectBrush.setRotation(r);

        const sf::FloatRect b = _RectBrush.getGlobalBounds();
        _RectBrush.setPosition(x1 - b.width * cos(constant::pi() * r * 2.f/ 180.f) / 2.f, y1 - b.height/ 2.f);

        return _RectBrush;
    }

    sf::RectangleShape& point(const sf::Vector2f& x1)
    {
        return point(x1.x, x1.y);
    }

    const sf::RectangleShape& line(const float& x1, const float& y1, const float& x2, const float& y2) const
    {
        const float hh = (y2 - y1),
                    length = sqrt(hh * hh + (x2 - x1) * (x2 - x1));

        // I need to compute offset
        _RectBrush.setSize({length, _LineTickness});
        _RectBrush.setRotation(180.0f * asin(hh / length) / constant::pi());
        _RectBrush.setPosition(x1, y1);

        return _RectBrush;
    }

    const sf::RectangleShape& line(const sf::Vector2f& x1, const sf::Vector2f& x2) const
    {
        return line(x1.x, x1.y, x2.x, x2.y);
    }

    sf::RectangleShape& line(const float& x1, const float& y1, const float& x2, const float& y2)
    {
        const float hh = (y2 - y1),
                    length = sqrt(hh * hh + (x2 - x1) * (x2 - x1));

        _RectBrush.setSize({length, _LineTickness});
        _RectBrush.setPosition(x1, y1);
        _RectBrush.setRotation(180.0f * asin(hh / length) / constant::pi());

        return _RectBrush;
    }

    sf::RectangleShape& line(const sf::Vector2f& x1, const sf::Vector2f& x2)
    {
        return line(x1.x, x1.y, x2.x, x2.y);
    }

    void setLineTickness(float t)                                  {   _LineTickness = t;
                                                                       _CircleBrush.setRadius(t);  }
    void setFillColor(sf::Color c)                                 {   _RectBrush.setFillColor(c);
                                                                       _CircleBrush.setFillColor(c); }
    void setOutlineColor(sf::Color c)                              {   _RectBrush.setOutlineColor(c);
                                                                       _CircleBrush.setOutlineColor(c);}
    void setOutlineTickness(float tick)                            {   _RectBrush.setOutlineThickness(tick);
                                                                       _CircleBrush.setOutlineThickness(tick);}
    void setTextures(const sf::Texture* r, bool resetRect = false) {   _RectBrush.setTexture(r, resetRect);
                                                                       _CircleBrush.setTexture(r, resetRect);}
    void setTexturesRect(const sf::IntRect& rect)                  {   _RectBrush.setTextureRect(rect);
                                                                       _CircleBrush.setTextureRect(rect);}

    const float&       getLineTickness   () const {   return _LineTickness;                 }
    const sf::Color&   getFillColor      () const {   return _RectBrush.getFillColor();     }
    const sf::Color&   getOutlineColor   () const {   return _RectBrush.getOutlineColor();  }
    float              getOutlineTickness() const {   return _RectBrush.getOutlineThickness();}
    const sf::Texture* getTextures       () const {   return _RectBrush.getTexture();       }
    const sf::IntRect& getTexturesRect   () const {   return _RectBrush.getTextureRect();   }

    sf::Shape& setBrush(sf::Shape& s)
    {
        s.setFillColor      (getFillColor      ());
        s.setOutlineColor   (getOutlineColor   ());
    }

private:
    mutable sf::ConvexShape    _ConvexBrush;
    mutable sf::CircleShape    _CircleBrush;
    mutable sf::RectangleShape _RectBrush;
    float _LineTickness{1};

};

#endif
