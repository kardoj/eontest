#ifndef TREETEST_H
#define TREETEST_H

#include "testcase.h"
#include "tree.h"

class TreeTest : public TestCase
{
    public:
        TreeTest();
        virtual ~TreeTest();

        void init_creates_required_folders_and_files();
        void init_does_not_continue_when_root_dir_fails();
        void init_does_not_run_when_already_an_eon_directory();
        void test();

    private:
        Tree tree;
};

#endif // TREETEST_H
