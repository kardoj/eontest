#ifndef TREETEST_H
#define TREETEST_H

#include "testcase.h"

class TreeTest : public TestCase
{
    public:
        TreeTest();
        virtual ~TreeTest();

        void init_creates_required_folders_and_files();
        void init_does_not_run_when_already_an_eon_directory();
        void test();
};

#endif // TREETEST_H
