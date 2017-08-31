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
    cout << "=== TreeTest ===" << endl;
    ensure_year_dir_creates_year_dir_if_needed();
    init_creates_required_folders_and_files();
    init_does_not_continue_when_root_dir_fails();
    init_does_not_continue_when_entries_dir_fails();
    init_does_not_continue_when_projects_dir_fails();
    init_does_not_run_when_already_an_eon_dir();
    init_fails_if_config_file_fails();
    init_fails_if_first_project_fails();
    init_fails_if_projects_file_fails();
    initial_config_string_is_correct();
    is_eon_dir();
    is_not_eon_dir();
    cout << endl;
}

void TreeTest::init_creates_required_folders_and_files()
{
    cout << "TEST " << __FUNCTION__ << endl;
    remove_dir_recursively(Tree::ROOT_DIR);

    string datetime = Date::current_date_with_time();
    assert_true(tree.init(datetime), "Tree::init()");

    assert_dir_exists(Tree::ROOT_DIR);
    assert_dir_exists(Tree::PROJECTS_DIR);
    assert_dir_exists(Tree::ENTRIES_DIR);

    assert_file_exists(Tree::PROJECTS_FILE);
    string project_row = "1 \"" + string(Project::DEFAULT_PROJECT_NAME) + "\" 0 " + datetime + " " + datetime + "\n";
    assert_file_contents_equal(project_row, Tree::PROJECTS_FILE, MAX_ROW_LENGTH_DEFAULT);

    assert_file_exists(Tree::CONFIG_FILE);
    char config_str[30];
    tree.initial_config_str(datetime.substr(0, 10), config_str);
    assert_file_contents_equal(config_str, Tree::CONFIG_FILE, MAX_ROW_LENGTH_DEFAULT);
}

void TreeTest::init_does_not_continue_when_root_dir_fails()
{
    cout << "TEST " << __FUNCTION__ << endl;
    remove_dir_recursively(Tree::ROOT_DIR);

    class FailingRootTree : public Tree
    {
        const char *root_dir()
        {
            return "not*a*valid*dir";
        }
    };
    vector<string> messages_human;
    FailingRootTree frt;
    assert_false(frt.init(Date::current_date_with_time()), "Tree::init()");
    assert_equal(frt.get_messages().at(0), Tree::MSG_ROOT_DIR_FAILURE);
}

void TreeTest::init_does_not_continue_when_entries_dir_fails()
{
    cout << "TEST " << __FUNCTION__ << endl;
    remove_dir_recursively(Tree::ROOT_DIR);

    class FailingEntriesDirTree : public Tree
    {
        const char *entries_dir()
        {
            return "not*a*valid*dir";
        }
    };
    FailingEntriesDirTree fet;
    assert_false(fet.init(Date::current_date_with_time()), "Tree::init()");
    assert_equal(fet.get_messages().at(0), Tree::MSG_ENTRIES_PROJECTS_DIR_FAILURE);
}

void TreeTest::init_does_not_continue_when_projects_dir_fails()
{
    cout << "TEST " << __FUNCTION__ << endl;
    remove_dir_recursively(Tree::ROOT_DIR);

    class FailingProjectsDirTree : public Tree
    {
        const char *projects_dir()
        {
            return "not*a*valid*dir";
        }
    };
    FailingProjectsDirTree fpdt;
    assert_false(fpdt.init(Date::current_date_with_time()), "Tree::init()");
    assert_equal(fpdt.get_messages().at(0), Tree::MSG_ENTRIES_PROJECTS_DIR_FAILURE);
}

void TreeTest::init_does_not_run_when_already_an_eon_dir()
{
    cout << "TEST " << __FUNCTION__ << endl;
    remove_dir_recursively(Tree::ROOT_DIR);

    string datetime = Date::current_date_with_time();
    tree = Tree();
    assert_true(tree.init(datetime), "The first Tree::init()");
    assert_false(tree.init(datetime), "Tree::init() after the first init");
    assert_equal(tree.get_messages().at(1), Tree::MSG_ALREADY_INITIALIZED);
}

void TreeTest::init_fails_if_config_file_fails()
{
    cout << "TEST " << __FUNCTION__ << endl;
    remove_dir_recursively(Tree::ROOT_DIR);

    class FailingConfigFileTree : public Tree
    {
        const char *config_file()
        {
            return "not*a*valid*file";
        }
    };
    FailingConfigFileTree fcft;
    assert_false(fcft.init(Date::current_date_with_time()), "Tree::init()");
    assert_equal(fcft.get_messages().at(0), Tree::MSG_INIT_FAILURE);
}

void TreeTest::init_fails_if_first_project_fails()
{
    cout << "TEST " << __FUNCTION__ << endl;
    remove_dir_recursively(Tree::ROOT_DIR);

    class FailingFirstProjectTree : public Tree
    {
        bool add_default_project(const string datetime)
        {
            return false;
        }
    };
    FailingFirstProjectTree ffpt;
    assert_false(ffpt.init(Date::current_date_with_time()), "Tree::init()");
    assert_equal(ffpt.get_messages().at(0), Tree::MSG_INIT_FAILURE);
}

void TreeTest::init_fails_if_projects_file_fails()
{
    cout << "TEST " << __FUNCTION__ << endl;
    remove_dir_recursively(Tree::ROOT_DIR);

    class FailingProjectsFileTree : public Tree
    {
        const char *projects_file()
        {
            return "not*a*valid*file";
        }
    };
    FailingProjectsFileTree fpft;
    assert_false(fpft.init(Date::current_date_with_time()), "Tree::init()");
    assert_equal(fpft.get_messages().at(0), Tree::MSG_INIT_FAILURE);
}

void TreeTest::initial_config_string_is_correct()
{
    cout << "TEST " << __FUNCTION__ << endl;
    remove_dir_recursively(Tree::ROOT_DIR);

    string datetime = Date::current_date_with_time();
    string dte = Date::current_date();
    char initial_config_str[Tree::INITIAL_CONFIG_LENGTH];
    tree.init(datetime);
    tree.initial_config_str(dte, initial_config_str);
    assert_equal("date=" + dte + "\nproject_id=1\n", string(initial_config_str));
}

void TreeTest::is_eon_dir()
{
    cout << "TEST " << __FUNCTION__ << endl;
    remove_dir_recursively(Tree::ROOT_DIR);

    tree.init(Date::current_date_with_time());
    assert_true(Tree::is_eon_dir(), "Tree::is_eon_dir()");
}

void TreeTest::is_not_eon_dir()
{
    cout << "TEST " << __FUNCTION__ << endl;
    remove_dir_recursively(Tree::ROOT_DIR);

    assert_false(Tree::is_eon_dir(), "Tree::is_eon_dir()");
}

void TreeTest::ensure_year_dir_creates_year_dir_if_needed()
{
    cout << "TEST " << __FUNCTION__ << endl;
    remove_dir_recursively(Tree::ROOT_DIR);

    tree.init(Date::current_date_with_time());
    string year = "2025";
    string test_path = string(Tree::ENTRIES_DIR) + "/" + year;
    assert_dir_not_exists(test_path);
    Tree::ensure_year_dir(year);
    assert_dir_exists(test_path);
}
