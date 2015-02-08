#include <gtest/gtest.h>

#include "../cml/OptionFile.h"

TEST(OptionItem, PrintTest)
{
    OptionItem  data;
    OptionItem  config;
    OptionItem* config2 = new OptionItem();

    data.append_field("starting_date", "1980-01-01");
    data.append_field("ending_date",   "2014-01-01");
    data.append_field("grain",         "daily");

    config.append_field("source",   "blg");
    config.append_field("source1",  "blo1");
    config.append_field("source2",  "brg2");
    config.append_field("source3",  "blog3");

    config2->append_field("source",  "b");
    config2->append_field("source1", "b1");
    config2->append_field("source2", "bl");
    config2->append_field("source3", "b3");

    config.append_items("config3", config2, true);
    data.append_items("config", &config);

    data.print();
}
