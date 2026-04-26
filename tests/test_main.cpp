#include "test_framework.h"

void test_countFrequency();
void test_buildTree();
void test_buildCodeTable();

int main() {
    RUN_TEST(test_countFrequency);
    RUN_TEST(test_buildTree);
    RUN_TEST(test_buildCodeTable);
    return 0;
}