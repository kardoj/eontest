#include <iostream>
#include <date.h>
#include "datetest.h"

using namespace std;

DateTest::DateTest() {}
DateTest::~DateTest() {}

void DateTest::test()
{
    cout << "=== DateTest ===" << endl;
    parses_a_date_from_yyyy_mm_dd_string();
    cout << endl;
}

void DateTest::parses_a_date_from_yyyy_mm_dd_string()
{
    reset_eon(__FUNCTION__);

    assert_no_exception(&create_date_yyyy_mm_dd_no_exception, "Date(\"2017-12-04\")");
}

void DateTest::create_date_yyyy_mm_dd_no_exception()
{
    Date("2017-12-04");
};


