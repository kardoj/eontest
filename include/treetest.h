#ifndef TREETEST_H
#define TREETEST_H

#include "testcase.h"

class TreeTest : public TestCase
{
    public:
        TreeTest();
        virtual ~TreeTest();

        void init_creates_required_files_and_folders();
};

#endif // TREETEST_H
