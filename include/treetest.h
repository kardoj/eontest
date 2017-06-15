#ifndef TREETEST_H
#define TREETEST_H

#include "testcase.h"

class TreeTest : public TestCase
{
    public:
        TreeTest();
        virtual ~TreeTest();

        void init_creates_required_files_and_folders();
        void init_does_not_run_when_already_an_eon_directory();
};

#endif // TREETEST_H
