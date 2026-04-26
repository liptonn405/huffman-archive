#include "test_framework.h"

void test_countFrequency();
void test_buildTree();
void test_buildCodeTable();

int main() {
    RUN_TEST(test_countFrequency);
    RUN_TEST(test_buildTree);
    RUN_TEST(test_buildCodeTable);

    std::cout << "\n[PASSED]:" << g_testsPassed << "\n";
    std::cout << "[FAILED]:" << g_testsFailed << "\n";

    return g_testsFailed == 0 ? 0 : 1;
}