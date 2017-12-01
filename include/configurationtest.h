#ifndef EONTEST_CONFIGURATIONTEST_H
#define EONTEST_CONFIGURATIONTEST_H

#include "testcase.h"

class ConfigurationTest : public TestCase
{
    public:
        ConfigurationTest();
        virtual ~ConfigurationTest();

        void alerts_if_invalid_config_row_found();
        void reads_configuration();
        void read_fails_if_config_file_fails();
        void read_sets_configuration_values();
        void writes_configuration();
        void writes_date();
        void writes_project_id();
        void write_fails_if_config_file_fails();
        void set_from_param_sets_project_from_short_key();
        void set_from_param_sets_project_from_key();
        void set_from_param_sets_date_from_short_key();
        void set_from_param_sets_date_from_key();
        void test();
};

#endif //EONTEST_CONFIGURATIONTEST_H
