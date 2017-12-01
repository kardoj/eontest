#include <iostream>
#include <helpers/vectorhelper.h>
#include <project.h>
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
    read_fails_if_config_file_fails();
    read_sets_configuration_values();
    writes_configuration();
    writes_date();
    writes_project_id();
    write_fails_if_config_file_fails();
    cout << endl;
}

void ConfigurationTest::alerts_if_invalid_config_row_found()
{
    cout << "TEST " << __FUNCTION__ << endl;
    remove_dir_recursively(Tree::ROOT_DIR);

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
    reset_eon(__FUNCTION__);

    assert_true(Configuration().read(), "Configuration::read()");
}

void ConfigurationTest::read_fails_if_config_file_fails()
{
    reset_eon(__FUNCTION__);

    class FailingConfigFileConfiguration : public Configuration
    {
        const char *config_file()
        {
            return "not*a*valid*file";
        }
    };

    FailingConfigFileConfiguration fcfc;
    fcfc.read();

    assert_equal(Configuration::MSG_ERROR_OPENING_CONFIG_FILE, VectorHelper::at(fcfc.get_messages(), 0));
}

void ConfigurationTest::read_sets_configuration_values()
{
    reset_eon(__FUNCTION__);

    Configuration conf;
    conf.read();

    assert_equal(Date::current_date(), conf.get_date());
    assert_equal(1, conf.get_project_id());
}

void ConfigurationTest::writes_configuration()
{
    reset_eon(__FUNCTION__);

    Configuration conf;

    assert_true(conf.write(), "Configuration::write()");
}

void ConfigurationTest::writes_date()
{
    reset_eon(__FUNCTION__);

    Configuration conf;
    string date = "2017-12-01";
    conf.set_date(date);
    conf.write();

    assert_file_contents_equal(
        "date=2017-12-01\nproject_id=1\n",
        Tree::CONFIG_FILE,
        Configuration::MAX_CONFIG_ROW_LENGTH
    );
}

void ConfigurationTest::writes_project_id()
{
    reset_eon(__FUNCTION__);

    Configuration conf;
    Project().add("Test", datetime);
    conf.set_project_id("Test");
    conf.write();

    string expected = "date=" + dte + "\nproject_id=2\n";
    assert_file_contents_equal(expected, Tree::CONFIG_FILE, Configuration::MAX_CONFIG_ROW_LENGTH);
}

void ConfigurationTest::write_fails_if_config_file_fails()
{
    reset_eon(__FUNCTION__);

    class FailingConfigFileConfiguration : public Configuration
    {
        const char *config_file()
        {
            return "not*a*valid*file";
        }
    };

    FailingConfigFileConfiguration fcfc;
    fcfc.write();

    assert_equal(Configuration::MSG_ERROR_OPENING_CONFIG_FILE, VectorHelper::at(fcfc.get_messages(), 0));
}


