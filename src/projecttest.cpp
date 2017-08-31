#include <iostream>
#include "date.h"
#include "project.h"
#include "projecttest.h"
#include "tree.h"
#include "vectorhelper.h"

using namespace std;

ProjectTest::ProjectTest() {}
ProjectTest::~ProjectTest() {}

void ProjectTest::test()
{
    cout << "=== ProjectTest ===" << endl;
    adds_new_project();
    exists_fails_if_project_file_fails();
    fails_adding_a_project_if_projects_file_fails();
    fails_listing_projects_if_projects_file_fails();
    project_does_not_exist();
    project_exists();
    cout << endl;
}

void ProjectTest::adds_new_project()
{
    cout << "TEST " << __FUNCTION__ << endl;
    remove_dir_recursively(Tree::ROOT_DIR);

    string datetime = Date::current_date_with_time();
    Tree().init(datetime);

    char name[] = { "new project" };
    Project p;
    p.add(name, datetime);
    string expected_str = "1 \"" + string(Project::DEFAULT_PROJECT_NAME) + "\" 0 " + datetime + " " + datetime + "\n" +
                          "2 \"" + name + "\" 0 " + datetime + " " + datetime + "\n";
    assert_file_contents_equal(expected_str, Tree::PROJECTS_FILE, MAX_ROW_LENGTH_DEFAULT);
    assert_equal(Project::msg_project_added(name), VectorHelper::at(p.get_messages(), 0));
}

void ProjectTest::fails_adding_a_project_if_projects_file_fails()
{
    cout << "TEST " << __FUNCTION__ << endl;
    remove_dir_recursively(Tree::ROOT_DIR);

    string datetime = Date::current_date_with_time();
    Tree().init(datetime);
    char name[] = { "new project" };

    class FailingProjectsFileProject : public Project
    {
        const char *projects_file()
        {
            return "not*a*file";
        }
    };

    FailingProjectsFileProject fpfp;
    assert_false(fpfp.add(name, datetime), "FailingProjectsFileProject().add()");
    assert_equal(Project::MSG_ERROR_OPENING_PROJECTS_FILE, VectorHelper::at(fpfp.get_messages(), 0));
}

void ProjectTest::project_does_not_exist()
{
    cout << "TEST " << __FUNCTION__ << endl;
    remove_dir_recursively(Tree::ROOT_DIR);

    Tree().init(Date::current_date_with_time());

    int project_id = 0;
    assert_false(Project().exists("Some made up name", project_id), "Made up project by name");
    assert_equal(project_id, -1);
    project_id = 0;
    assert_false(Project().exists("3", project_id), "Made up project by id");
    assert_equal(project_id, -1);
}

void ProjectTest::project_exists()
{
    cout << "TEST " << __FUNCTION__ << endl;
    remove_dir_recursively(Tree::ROOT_DIR);

    Tree().init(Date::current_date_with_time());

    int project_id = 0;
    assert_true(Project().exists(Project::DEFAULT_PROJECT_NAME, project_id), "Default project by name");
    assert_equal(project_id, 1);
    project_id = 0;
    assert_true(Project().exists("1", project_id), "Default project by id");
    assert_equal(project_id, 1);
}

void ProjectTest::exists_fails_if_project_file_fails()
{
    cout << "TEST " << __FUNCTION__ << endl;
    remove_dir_recursively(Tree::ROOT_DIR);

    Tree().init(Date::current_date_with_time());

    class FailingProjectsFileProject : public Project
    {
        const char *projects_file()
        {
            return "not*a*file";
        }
    };

    int project_id;
    FailingProjectsFileProject fpfp;
    assert_false(fpfp.exists("1", project_id), "FailingProjectsFileProject().exists()");
    assert_equal(Project::MSG_ERROR_OPENING_PROJECTS_FILE, VectorHelper::at(fpfp.get_messages(), 0));
}

void ProjectTest::fails_listing_projects_if_projects_file_fails()
{
    cout << "TEST " << __FUNCTION__ << endl;
    remove_dir_recursively(Tree::ROOT_DIR);

    string datetime = Date::current_date_with_time();
    Tree().init(datetime);

    class FailingProjectsFileProject : public Project
    {
        const char *projects_file()
        {
            return "not*a*file";
        }
    };
    FailingProjectsFileProject fpfp;
    assert_false(fpfp.list(1), "FailingProjectsFileProject().list()");
    assert_equal(Project::MSG_ERROR_OPENING_PROJECTS_FILE, VectorHelper::at(fpfp.get_messages(), 0));
}