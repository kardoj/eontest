#include <iostream>
#include "date.h"
#include "project.h"
#include "tree.h"
#include "treetest.h"

using namespace std;

TreeTest::TreeTest() {
    init_creates_required_files_and_folders();
}

TreeTest::~TreeTest() {}

void TreeTest::init_creates_required_files_and_folders()
{
    // TODO: Delete all the folders before running this test
    cout << "TEST " << __FUNCTION__ << endl;
    string datetime = Date::current_date_with_time();
    assert_true(Tree::init(datetime), "Tree::init()");

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
