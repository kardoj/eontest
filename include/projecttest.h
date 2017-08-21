#ifndef PROJECTTEST_H
#define PROJECTTEST_H

#include "testcase.h"

class ProjectTest : public TestCase
{
    public:
        ProjectTest();
        virtual ~ProjectTest();

        void adds_new_project();
        void fails_adding_a_project_if_projects_file_fails();
        void project_does_not_exist();
        void project_exists();
        void test();
};

#endif // PROJECTTEST_H
