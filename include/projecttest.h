#ifndef PROJECTTEST_H
#define PROJECTTEST_H

#include "testcase.h"

class ProjectTest : public TestCase
{
    public:
        ProjectTest();
        virtual ~ProjectTest();

        void adds_new_project();
        void test();
};

#endif // PROJECTTEST_H
