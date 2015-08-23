#ifndef STRAT3_GRAPHICS_SCALE_HEADER
#define STRAT3_GRAPHICS_SCALE_HEADER

#include <SFML/Graphics.hpp>

template<typename T/*, typename T1*/>
struct Scale{
    Scale() = default;

    Scale(T min_, T max_):
        min(min_), max(max_)
    {
        if (min > max){
            max = min_;
            min = max_;
        }
    }

    T operator() (const T& val, sf::Uint32 width) { return x(val, width);   }

    T x(const T& val, const sf::Uint32 width) {   return val * (width / (max - min) - min);   }
    T y(const T& val, const sf::Uint32 height){   return height - val * height / (max - min); }

    T x(const T& val, const sf::FloatRect rect)
    {
        return rect.left + val * (rect.width / (max - min) - min);
    }

    T y(const T& val, const sf::FloatRect& rect)
    {
        return rect.top + rect.height - val * rect.height / (max - min);
    }

    T min{0};
    T max{1};
};

template<typename T>
struct BoundedScale
{
public:
    BoundedScale(const T& min_, const T& max_, const sf::FloatRect& rect_):
        min(min_), max(max_), rect(rect_)
    {
        if (min > max){
            max = min_;
            min = max_;
        }
    }

    T x(const T& val)
    {
        return rect.left + val * (rect.width / (max - min) - min);
    }

    T y(const T& val)
    {
        return rect.top + rect.height - val * rect.height / (max - min);
    }

    T min{0};
    T max{1};

    sf::FloatRect rect;
};


template<typename T>
struct Bounded2DScale
{
public:
    Bounded2DScale(const T& xmin_, const T& xmax_,
                   const T& ymin_, const T& ymax_,
                   const sf::FloatRect& rect_):
        xmin(xmin_), xmax(xmax_),
        ymin(ymin_), ymax(ymax_),rect(rect_)
    {
        if (xmin > xmax){
            xmax = xmin_;
            xmin = xmax_;
        }

        if (ymin > ymax){
            ymax = ymin_;
            ymin = ymax_;
        }
    }

    sf::Vector2f operator() (const T& xx, const T& yy)
    {
        return sf::Vector2f({x(xx), y(yy)});
    }

    sf::Vector2f operator() (const sf::Vector2f& pts)
    {
        return  sf::Vector2f({x(pts.x), y(pts.y)});
    }

    T x(const T& val)
    {
        return rect.left + val * (rect.width / (xmax - xmin) - xmin);
    }

    T y(const T& val)
    {
        return rect.top + rect.height - val * rect.height / (ymax - ymin);
    }

    T xmin{0};
    T xmax{1};
    T ymin{0};
    T ymax{1};

    sf::FloatRect rect;
};

#endif
