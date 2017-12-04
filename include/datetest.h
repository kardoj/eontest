#ifndef EONTEST_DATETEST_H
#define EONTEST_DATETEST_H

#include "testcase.h"

class DateTest : public TestCase
{
    public:
        DateTest();
        virtual ~DateTest();
        void parses_a_date_from_yyyy_mm_dd_string();
        void parses_a_date_from_dd_mm_yyyy_string();
        void raises_an_exception_on_invalid_string();
        void test();

    private:
        static void create_date_yyyy_mm_dd_no_exception();
        static void create_date_dd_mm_yyyy_no_exception();
        static void create_date_invalid_string();
};

#endif //EONTEST_DATETEST_H
