#include <iostream>
#include <vector>
#include "date.h"
#include "project.h"
#include "tree.h"
#include "treetest.h"

using namespace std;

TreeTest::TreeTest() {}
TreeTest::~TreeTest() {}

void TreeTest::test()
{
    // All the tests should be called here
    init_creates_required_folders_and_files();
    init_does_not_continue_when_root_dir_fails();
    init_does_not_run_when_already_an_eon_directory();
}

void TreeTest::init_creates_required_folders_and_files()
{
    cout << "TEST " << __FUNCTION__ << endl;
    remove_dir_recursively(Tree::ROOT_DIR);

    string datetime = Date::current_date_with_time();
    vector<string> messages_human;
    assert_true(Tree::init(datetime, messages_human), "Tree::init()");

    assert_dir_exists(Tree::ROOT_DIR);
    assert_dir_exists(Tree::PROJECTS_DIR);
    assert_dir_exists(Tree::ENTRIES_DIR);

    assert_file_exists(Tree::PROJECTS_ID_FILE);
    assert_file_contents_equal("2", Tree::PROJECTS_ID_FILE, MAX_ROW_LENGTH_DEFAULT);
    assert_file_exists(Tree::PROJECTS_FILE);
    string project_row = "1 \"" + string(Project::DEFAULT_PROJECT_NAME) + "\" " + datetime + " " + datetime + "\n";
    assert_file_contents_equal(project_row, Tree::PROJECTS_FILE, MAX_ROW_LENGTH_DEFAULT);

    assert_file_contents_equal("1", Tree::ENTRIES_ID_FILE, MAX_ROW_LENGTH_DEFAULT);

    assert_file_exists(Tree::CONFIG_FILE);
    char config_str[30];
    Tree::initial_config_str(datetime.substr(0, 11), config_str);
    assert_file_contents_equal(config_str, Tree::CONFIG_FILE, MAX_ROW_LENGTH_DEFAULT);
}

void TreeTest::init_does_not_continue_when_root_dir_fails()
{
    cout << "TEST " << __FUNCTION__ << endl;
    remove_dir_recursively(Tree::ROOT_DIR);

    string datetime = Date::current_date_with_time();
    vector<string> messages_human;
    assert_false(Tree::init(datetime, messages_human), "Tree::init()");
    assert_equal(messages_human.at(0), Tree::MSG_ROOT_DIR_FAILURE);
}

void TreeTest::init_does_not_run_when_already_an_eon_directory()
{
    cout << "TEST " << __FUNCTION__ << endl;
    remove_dir_recursively(Tree::ROOT_DIR);

    string datetime = Date::current_date_with_time();
    vector<string> messages_human;
    assert_true(Tree::init(datetime, messages_human), "The first Tree::init()");
    assert_false(Tree::init(datetime, messages_human), "Tree::init() after the first init");
    assert_equal(messages_human.at(0), Tree::MSG_ALREADY_INITIALIZED);
}
