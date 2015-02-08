#ifndef STRAT3_CML_OPTIONFILE_HEADER
#define STRAT3_CML_OPTIONFILE_HEADER

#include "../enum.h"

#include <string>
#include <fstream>

#include <unordered_map>

class OptionItem
{
public:
    typedef std::string string;
    typedef std::unordered_map<string, OptionItem*> MapElement;
    typedef std::unordered_map<string, string     > MapField;

    typedef MapField::iterator   FieldIterator;
    typedef MapElement::iterator ElementIterator;

    OptionItem();

    ~OptionItem();

    Index size_items();
    Index size_options();

    OptionItem* get_item      (string m);
    string      get_item_field(string m, string f);
    string      get_field     (string m);

    void append_field(string f, string o);
    void append_items(string f, OptionItem* o, bool t = false);

    void print       (int depth = 0);
    void print_fields(int depth = 0);
    void print_items (int depth = 0);

    /*  item1:{
     *      option1.1:1.1,
     *  },
     *  item2:{
     *      option2.1:2.1,
     *  },
     */
    MapElement items;

    /*  option1:1,
     *  option2:2,
     *  option3:3,
     */
    MapField   fields;
    bool       owned;
};


//class OptionFile
//{
//public:

//    OptionFile(std::string name)
//    {
//        file.open(name.c_str(), std::ios::in);
//    }

//    ~OptionFile()
//    {
//        file.close();
//    }

//protected:

//    std::ifstream file;
//};



#endif
