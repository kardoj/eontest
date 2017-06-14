#include <iostream>
#include "tree.h"
#include "treetest.h"

using namespace std;

TreeTest::TreeTest() {
    init_creates_required_files_and_folders();
}

TreeTest::~TreeTest() {}

void TreeTest::init_creates_required_files_and_folders()
{
    cout << "TEST " << __FUNCTION__ << endl;
    Tree::init();
    assert_dir_exists(Tree::ROOT_DIR);
    assert_dir_exists(Tree::PROJECTS_DIR);
    assert_dir_exists(Tree::ENTRIES_DIR);
    assert_dir_exists("./lul");
    cout << "" << endl;
}
