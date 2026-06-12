// MIT License
//
// Copyright (c) 2026 Lihanov Daniil
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
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
