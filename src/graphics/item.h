#ifndef STRAT3_GRAPHICS_ITEM_HEADER
#define STRAT3_GRAPHICS_ITEM_HEADER

#include <vector>

#include <SFML/Graphics.hpp>

//
//  Save a set of shapes
//
class GraphicItem
{
public:
    GraphicItem() = default;

    ~GraphicItem()
    {
        for(auto& i:graphs)
            delete i;
    }

    GraphicItem(const GraphicItem& g) = delete;
    GraphicItem& operator= (const GraphicItem&) = delete;

    template<typename T>
    void add_item(const T& s)
    {
        graphs.push_back(new T(s));
    }

    void set_color(const sf::Color& color)
    {
        for(sf::Shape*& i:graphs)
            i->setFillColor(color);

    }

    std::vector<sf::Shape>::size_type size() {  return graphs.size();   }

    void draw(sf::RenderWindow& rw)
    {
        for(auto& i:graphs)
        {
            rw.draw(*i);
        }
    }

protected:

    std::vector<sf::Shape*> graphs;
};

#endif
