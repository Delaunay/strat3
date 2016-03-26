#ifndef STRAT3_GRAPHICS_SHAPES_HEADER
#define STRAT3_GRAPHICS_SHAPES_HEADER

#include <memory>
#include <vector>

#include "Scale.h"
#include "Painter.h"
#include "utility.h"
#include "item.h"

template<typename T>
std::unique_ptr<GraphicItem> draw_line(const std::vector<T>& v, const sf::FloatRect& rct)
{
    Painter l;
    std::unique_ptr<GraphicItem> it(new GraphicItem);

    auto minmax = std::minmax_element(v.begin(), v.end());

    Bounded2DScale<float> xy((*minmax.first), (*minmax.second),
                              0, v.size(), rct);

    sf::Vector2f p1 = xy(0, v[0]);
    sf::Vector2f p2;

    for(int i = 1, n = v.size(); i < n; i++)
    {
        p2 = xy(i, v[i]);

        it->add_item(l.line(p1, p2));

        p1 = p2;
    }

    return it;
}


template<typename T>
std::unique_ptr<GraphicItem> draw_line(const std::vector<T>& vx,
                                       const std::vector<T>& vy, const sf::FloatRect& rct)
{
    Painter l;
    std::unique_ptr<GraphicItem> it(new GraphicItem);

    auto xminmax = std::minmax_element(vx.begin(), vx.end());
    auto yminmax = std::minmax_element(vy.begin(), vy.end());

    Bounded2DScale<float> xy((*xminmax.first), (*xminmax.second),
                             (*yminmax.first), (*yminmax.second), rct);

    sf::Vector2f p1 = xy(vx[0], vy[0]);
    sf::Vector2f p2;

    for(int i = 1, n = std::min(vx.size(), vy.size()); i < n; i++)
    {
        p2 = xy(vx[i], vy[i]);

        it->add_item(l.line(p1, p2));

        p1 = p2;
    }

    return it;
}


template<typename T>
std::unique_ptr<GraphicItem> draw_points(const std::vector<T>& vx,
                                         const std::vector<T>& vy, const sf::FloatRect& rct)
{
    Painter l;
    std::unique_ptr<GraphicItem> it(new GraphicItem);

    auto xminmax = std::minmax_element(vx.begin(), vx.end());
    auto yminmax = std::minmax_element(vy.begin(), vy.end());

    Bounded2DScale<float> xy((*xminmax.first), (*xminmax.second),
                             (*yminmax.first), (*yminmax.second), rct);

    for(int i = 0, n = std::min(vx.size(), vy.size()); i < n; i++)
    {
        it->add_item(l.point(xy(vx[i], vy[i])));
    }

    return it;
}

#endif
