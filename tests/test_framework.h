#pragma once
#include <iostream>

extern int g_testsPassed;
extern int g_testsFailed;

#define CHECK(expr) \
    if(expr) { g_testsPassed++; } \
    else { g_testsFailed++; std::cerr << "[FAILED] " << __FILE__<< ":" <<__LINE__<< " CHECK(" << #expr << ")\n"; }

#define CHECK_EQ(a, b) \
    if ((a) == (b)) { g_testsPassed++; } \
    else { g_testsFailed++; std::cerr << "[FAILED]" << __FILE__<< ":" <<__LINE__<< " CHECK(" << #a << " == " << #b << ")\n"; }

#define RUN_TEST(func) \
    { \
        std::cout << "[Running test] " << #func << "\n"; \
        int failedBefore = g_testsFailed; \
        int passedBefore = g_testsPassed;\
        func(); \
        if(g_testsFailed == failedBefore) { std::cout << "[OK] " << #func << "\n"; } \
        else { std::cout << "[FAILED] " << #func << "\n"; } \
    }