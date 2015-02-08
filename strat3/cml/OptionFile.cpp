#include "OptionFile.h"

#include <iostream>

OptionItem::OptionItem():
    owned(false)
{}

OptionItem::~OptionItem()
{
    ElementIterator it;
    ElementIterator n = items.end();

    for(it = items.begin(); it != n; ++it)
        if ((*it).second->owned)
            delete (*it).second;
}

Index OptionItem::size_items()      {   return items.size();    }
Index OptionItem::size_options()    {   return fields.size();  }

OptionItem* OptionItem::get_item  (string m)
{
    return items[m];
}

OptionItem::string OptionItem::get_item_field  (string m, string f)
{
    return items[m]->fields[f];
}

OptionItem::string OptionItem::get_field(string m)
{
    return fields[m];
}

void OptionItem::append_field(string f, string o)     {   fields[f] = o;  }
void OptionItem::append_items(string f, OptionItem* o, bool t)
{
    o->owned = t;
    items[f]  = o;
}

void OptionItem::print(int depth)
{
    printf("{\n");

    this->print_items(depth + 1);
    this->print_fields(depth + 1);

    for(int i = 0; i < depth; i++)
        printf("    ");

    printf("},\n");
}

void OptionItem::print_fields(int depth)
{
    FieldIterator it;
    FieldIterator n = fields.end();

    for(it = fields.begin(); it != n; ++it)
    {
        for(int i = 0; i < depth; i++)
            printf("    ");

        std::cout << (*it).first << ": " << (*it).second << ",\n";
    }
}

void OptionItem::print_items(int depth)
{
    ElementIterator it;
    ElementIterator n = items.end();

    for(it = items.begin(); it != n; ++it)
    {
        for(int i = 0; i < depth; i++)
            printf("    ");

        std::cout << (*it).first << ": ";

        (*it).second->print(depth);
    }
}
