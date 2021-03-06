#ifndef TESTCASE_H
#define TESTCASE_H

#include <string>
#include "tree.h"

class TestCase
{
    public:
        static const unsigned MAX_ROW_LENGTH_DEFAULT = 100;

        TestCase();
        virtual ~TestCase();
        void assert_dir_exists(const std::string path);
        void assert_dir_not_exists(const std::string path);
        void assert_file_contents_equal(
            const std::string contents,
            const std::string path,
            const unsigned max_row_length
        );
        void assert_false(const bool value, const std::string what_is_it);
        void assert_file_exists(const std::string path);
        void assert_exception(void (*func)(), const std::string what_is_it);
        void assert_no_exception(void (*func)(), const std::string what_is_it);
        void assert_true(const bool value, const std::string what_is_it);
        void assert_equal(const std::string one, const std::string two);
        void assert_equal(const int one, const int two);
        void remove_dir_recursively(const std::string path);
        void reset_eon(const std::string function_name);

    protected:
        std::string datetime; // datetime object for use in the tests
        std::string dte;
        Tree tree;
};

#endif // TESTCASE_H
