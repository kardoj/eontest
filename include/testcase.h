#ifndef TESTCASE_H
#define TESTCASE_H

#include <string>

class TestCase
{
    public:
        static const unsigned MAX_ROW_LENGTH_DEFAULT = 100;

        TestCase();
        virtual ~TestCase();
        void assert_dir_exists(const std::string path);
        void assert_file_contents_equal(
            const std::string contents,
            const std::string path,
            const unsigned max_row_length
        );
        void assert_file_exists(const std::string path);
        void assert_true(const bool value, const std::string what_is_it);
};

#endif // TESTCASE_H
