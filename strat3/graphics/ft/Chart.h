#ifndef STRAT3_GRAPHICS_CHART_HEADER
#define STRAT3_GRAPHICS_CHART_HEADER

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

// Global Font
sf::Font& font()
{
    static sf::Font f;
    return f;
}

enum Location
{
    Bottom = 1,
    Top    = 2,
    Left   = 4,
    Right  = 7,
};

enum Align
{
    AlignRight  = 1,
    AlignLeft   = 2,
    AlignTop    = 7,
    AlignBottom = 15,
    AlignLeftTop = AlignLeft | AlignTop,         // default
    AlignHCenter = AlignRight | AlignLeft,
    AlignVCenter = AlignTop | AlignBottom,
    AlignCenter = AlignHCenter | AlignVCenter,
    CustomAlign = 20
};

class ChartElement
{
public:

    ChartElement(ChartElement* p = nullptr):
        _parent(p), margin(0, 0, 0, 0), size(0, 0, 0, 0)
    {}

    ~ChartElement() = default;

    void set_parent(ChartElement* p)    {   _parent = p; }
    ChartElement& parent()              {   return *_parent; }

    virtual float width()  { return margin.left + margin.width;   }
    virtual float height() { return margin.top + margin.height;   }

    // Symetrical Margin right = left && bottom = top
    void set_sym_margin(float x_left, float y_top) {    return set_margin(x_left, y_top, x_left, y_top);}

    // Quick Constructor
    inline void set_margin(float left, float top, float right, float bottom)
    {
        margin.left = left;
        margin.top = top;
        margin.width = right;
        margin.height = bottom;
    }

    // Margin Shortcut
    inline float& right()  {   return margin.width;    }
    inline float& top()    {   return margin.top;      }
    inline float& left()   {   return margin.left;     }
    inline float& bottom() {   return margin.height;   }

    virtual inline void set_postion(float x, float y)   {   size.left = x; size.top = y;    }

    virtual void draw(sf::RenderWindow& rw){}

    virtual const sf::FloatRect& get_size()
    {
        size.height = height();
        size.width = width();
        return size;
    }

    sf::FloatRect margin;

protected:

    sf::FloatRect size;
    ChartElement* _parent{nullptr};
};



class ChartText : public ChartElement
{
public:

    ChartText(std::string txt, ChartElement* p = nullptr):
        ChartElement(p), text(txt, font())
    {}

    float width() override
    {
        return margin.left + margin.width + text.getGlobalBounds().width;
    }

    float height() override
    {
        return margin.top + margin.height + text.getGlobalBounds().height;
    }

    void draw(sf::RenderWindow& rw) override
    {
        float x = (margin.left + margin.width) / 2.f;
              y = (margin.top + margin.height) / 2.f;

         text.setPosition(size.left + x, size.top + y);
         rw.draw(text);
    }

    sf::Text text;
    Align    alignment;
};


class Chart: public ChartElement
{
public:
    Chart(ChartElement* p = nullptr):
        ChartElement(p)
    {}

    ~Chart()
    {
        delete title;
        delete legend;
    }

    void set_title(const std::string& title_, Location loc = Top)
    {
        title = new ChartText(title_, this);
        title->set_postion(0, 0);
    }

    // maximum 4 = most of time 2
    std::vector<ScaleLabel*> scale_label;
    Legend   * legend{nullptr};
    ChartText* title{nullptr};
};

class Scale;

class ScaleLabel: public ChartElement
{
public:

    ScaleLabel(Location scale_loc, Scale* s, ChartElement* p = nullptr):
        ChartElement(p), scale_location(scale_loc), scale(s)
    {
        if (is_y())
        {
            name.setRotation(90);
        }
    }

    inline bool is_x() {    return (scale_location == Bottom || scale_location == Top); }
    inline bool is_y() {    return (scale_location == Right || scale_location == Left); }

    float width() override
    {
        float sum = margin.left + margin.width;

        if (is_y())
            sum += name.getGlobalBounds().width;

        return sum;
    }

    float height() override
    {
        float sum = margin.top + margin.height;

        if (is_y())
            sum += name.getGlobalBounds().height;

        return sum;
    }

    void draw(sf::RenderWindow& rw)
    {

    }

    sf::Text name;
    sf::RectangleShape line;
    sf::RectangleShape tick_line;
    Scale* scale;
    Location scale_location;
    Location text_location; // BB BT TB TT
                            // LL LR RL RR
};


class Legend: public ChartElement
{
public:
    Legend(ChartElement* p = nullptr):
        ChartElement(p)
    {}



private:
    std::vector<std::string>* labels;
};

#endif
