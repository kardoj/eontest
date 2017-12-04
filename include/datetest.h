#ifndef EONTEST_DATETEST_H
#define EONTEST_DATETEST_H

#include "testcase.h"

class DateTest : public TestCase
{
    public:
        DateTest();
        virtual ~DateTest();
        void parses_a_date_from_yyyy_mm_dd_string();
        void test();

    private:
        static void create_date_yyyy_mm_dd_no_exception();
};

#endif //EONTEST_DATETEST_H
