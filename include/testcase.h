#ifndef TESTCASE_H
#define TESTCASE_H

#include <string>

class TestCase
{
    public:
        TestCase();
        virtual ~TestCase();

    private:
        void assert_dir_exists(const std::string path);
        void assert_file_exists(const std::string path);
};

#endif // TESTCASE_H
