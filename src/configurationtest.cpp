#include <iostream>
#include <vectorhelper.h>
#include "configuration.h"
#include "configurationtest.h"
#include "date.h"
#include "tree.h"

using namespace std;

ConfigurationTest::ConfigurationTest() {}
ConfigurationTest::~ConfigurationTest() {}

void ConfigurationTest::test()
{
    cout << "=== ConfigurationTest ===" << endl;
    reads_configuration();
    alerts_if_invalid_config_row_found();
    cout << endl;
}

void ConfigurationTest::alerts_if_invalid_config_row_found()
{
    cout << "TEST " << __FUNCTION__ << endl;
    remove_dir_recursively(Tree::ROOT_DIR);

    string datetime = Date::current_date_with_time();
    class InvalidConfigTree : public Tree
    {
        void initial_config_str(const string dte, char return_str[])
        {
            sprintf(return_str, "date%s\nproject_id=1\n", dte.c_str());
        }
    };
    InvalidConfigTree().init(datetime);

    Configuration conf;
    assert_false(conf.read(), "Configuration::read()");
    assert_equal(Configuration::MSG_INVALID_CONFIG_ROW, VectorHelper::at(conf.get_messages(), 0));
}

void ConfigurationTest::reads_configuration()
{
    cout << "TEST " << __FUNCTION__ << endl;
    remove_dir_recursively(Tree::ROOT_DIR);

    string datetime = Date::current_date_with_time();
    Tree().init(datetime);

    Configuration conf;
    assert_true(conf.read(), "Configuration::read()");
}
