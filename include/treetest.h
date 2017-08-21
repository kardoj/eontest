#ifndef TREETEST_H
#define TREETEST_H

#include "testcase.h"
#include "tree.h"

class TreeTest : public TestCase
{
    public:
        TreeTest();
        virtual ~TreeTest();

        void ensure_year_dir_creates_year_dir_if_needed();
        void init_creates_required_folders_and_files();
        void init_does_not_continue_when_root_dir_fails();
        void init_does_not_continue_when_entries_dir_fails();
        void init_does_not_continue_when_projects_dir_fails();
        void init_does_not_run_when_already_an_eon_dir();
        void init_fails_if_config_file_fails();
        void init_fails_if_first_project_fails();
        void init_fails_if_projects_file_fails();
        void initial_config_string_is_correct();
        void is_eon_dir();
        void is_not_eon_dir();
        void test();

    private:
        Tree tree;
};

#endif // TREETEST_H
