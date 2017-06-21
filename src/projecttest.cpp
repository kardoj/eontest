#include <iostream>
#include <string>
#include "date.h"
#include "project.h"
#include "projecttest.h"
#include "tree.h"

using namespace std;

ProjectTest::ProjectTest() {}
ProjectTest::~ProjectTest() {}

void ProjectTest::test()
{
    cout << "=== ProjectTest ===" << endl;
    adds_new_project();
    cout << endl;
}

void ProjectTest::adds_new_project()
{
    cout << "TEST " << __FUNCTION__ << endl;
    remove_dir_recursively(Tree::ROOT_DIR);

    string datetime = Date::current_date_with_time();
    vector<string> messages_human;
    Tree().init(datetime, messages_human);
    char name[] = { "new project" };
    Project::add(name, datetime);
    string expected_str = "1 \"" + string(Project::DEFAULT_PROJECT_NAME) + "\" " + datetime + " " + datetime + "\n" +
                          "2 \"" + name + "\" " + datetime + " " + datetime + "\n";
    assert_file_contents_equal(expected_str, Tree::PROJECTS_FILE, MAX_ROW_LENGTH_DEFAULT);
}
