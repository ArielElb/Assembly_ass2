//
// Created by einat on 19/11/2022.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <setjmp.h>

// redefine assert to set a boolean flag
#ifdef assert
#undef assert
#endif
#define assert(x) (rslt = rslt && (x))

// the function to test
#include "ex1.c"

// main result return code used by redefined assert
static int rslt;

// variables controling stub functions
static int expected_code;
static int should_exit;
static jmp_buf jump_env;

// test suite main variables
static int done;
static int num_tests;
static int tests_passed;

//  utility function
void TestStart(char *name) {
    num_tests++;
    rslt = 1;
    printf("-- Testing %s ... ", name);
}

//  utility function
void TestEnd() {
    if (rslt) tests_passed++;
    printf("%s\n", rslt ? "success" : "fail");
}

// stub function
void exit(int code) {
    if (!done) {
        assert(should_exit == 1);
        assert(expected_code == code);
        longjmp(jump_env, 1);
    } else {
        _exit(code);
    }
}
void test_is_big_endian() {
    int jmp_rval;
    int r;

    TestStart("test_is_big_endian");
    should_exit = 0;
    if (!(jmp_rval = setjmp(jump_env))) {
        r = is_big_endian();
    }
    assert(jmp_rval == 0);
    assert(r == 0);
    TestEnd();
}
// test case
void test_sign_magnitude1() {
    int jmp_rval;
    int r;

    TestStart("test_sign_magnitude1");
    should_exit = 0;
    if (!(jmp_rval = setjmp(jump_env))) {
        bool bitArray[] = {1, 0, 1, 0, 1, 0, 1, 0};
        r = get_sign_magnitude(bitArray);
    }
    assert(jmp_rval == 0);
    assert(r == 85);
    TestEnd();
}

void test_sign_magnitude2() {
    int jmp_rval;
    int r;

    TestStart("test_sign_magnitude2");
    should_exit = 0;
    if (!(jmp_rval = setjmp(jump_env))) {
        bool bitArray[] = {1, 1, 1, 1, 1, 1, 1, 1};
        r = get_sign_magnitude(bitArray);
    }
    assert(jmp_rval == 0);
    assert(r == -127);
    TestEnd();
}

void test_sign_magnitude3() {
    int jmp_rval;
    int r;

    TestStart("test_sign_magnitude3");
    should_exit = 0;
    if (!(jmp_rval = setjmp(jump_env))) {
        bool bitArray[] = {0, 0, 0, 0, 0, 0, 0, 0};
        r = get_sign_magnitude(bitArray);
    }
    assert(jmp_rval == 0);
    assert(r == 0);
    TestEnd();
}

void test_sign_magnitude4() {
    int jmp_rval;
    int r;

    TestStart("test_sign_magnitude4");
    should_exit = 0;
    if (!(jmp_rval = setjmp(jump_env))) {
        bool bitArray[] = {0, 0, 0, 0, 0, 0, 0, 1};
        r = get_sign_magnitude(bitArray);
    }
    assert(jmp_rval == 0);
    assert(r == 0);
    TestEnd();
}

void test_sign_magnitude5() {
    int jmp_rval;
    int r;

    TestStart("test_sign_magnitude5");
    should_exit = 0;
    if (!(jmp_rval = setjmp(jump_env))) {
        bool bitArray[] = {1, 0, 0, 0, 0, 0, 0, 0};
        r = get_sign_magnitude(bitArray);
    }
    assert(jmp_rval == 0);
    assert(r == 1);
    TestEnd();
}

void test_sign_magnitude6() {
    int jmp_rval;
    int r;

    TestStart("test_sign_magnitude6");
    should_exit = 0;
    if (!(jmp_rval = setjmp(jump_env))) {
        bool bitArray[] = {1, 1, 1, 1, 1, 1, 1, 0};
        r = get_sign_magnitude(bitArray);
    }
    assert(jmp_rval == 0);
    assert(r == 127);
    TestEnd();
}

void test_sign_magnitude7() {
    int jmp_rval;
    int r;

    TestStart("test_sign_magnitude7");
    should_exit = 0;
    if (!(jmp_rval = setjmp(jump_env))) {
        bool bitArray[] = {1, 1, 1, 1, 0, 0, 0, 0};
        r = get_sign_magnitude(bitArray);
    }
    assert(jmp_rval == 0);
    assert(r == 15);
    TestEnd();
}

void test_sign_magnitude8() {
    int jmp_rval;
    int r;

    TestStart("test_sign_magnitude8");
    should_exit = 0;
    if (!(jmp_rval = setjmp(jump_env))) {
        bool bitArray[] = {0, 0, 0, 0, 1, 1, 1, 1};
        r = get_sign_magnitude(bitArray);
    }
    assert(jmp_rval == 0);
    assert(r == -112);
    TestEnd();
}

void test_two_comp1() {
    int jmp_rval;
    int r;

    TestStart("test_two_comp1");
    should_exit = 0;
    if (!(jmp_rval = setjmp(jump_env))) {
        bool bitArray[] = {1,0,1,1,0,1,0,1};
        r = get_two_comp(bitArray);
    }
    assert(jmp_rval == 0);
    assert(r == -83);
    TestEnd();
}

void test_two_comp2() {
    int jmp_rval;
    int r;

    TestStart("test_two_comp2");
    should_exit = 0;
    if (!(jmp_rval = setjmp(jump_env))) {
        bool bitArray[] = {1,1,1,1,1,1,1,1};
        r = get_two_comp(bitArray);
    }
    assert(jmp_rval == 0);
    assert(r == -1);
    TestEnd();
}
void test_two_comp3() {
    int jmp_rval;
    int r;

    TestStart("test_two_comp3");
    should_exit = 0;
    if (!(jmp_rval = setjmp(jump_env))) {
        bool bitArray[] = {0,0,0,0,0,0,0,0};
        r = get_two_comp(bitArray);
    }
    assert(jmp_rval == 0);
    assert(r == 0);
    TestEnd();
}

void test_two_comp4() {
    int jmp_rval;
    int r;

    TestStart("test_two_comp4");
    should_exit = 0;
    if (!(jmp_rval = setjmp(jump_env))) {
        bool bitArray[] = {1,0,1,0,1,0,1,0};
        r = get_two_comp(bitArray);
    }
    assert(jmp_rval == 0);
    assert(r == 85);
    TestEnd();
}
void test_two_comp5() {
    int jmp_rval;
    int r;

    TestStart("test_two_comp5");
    should_exit = 0;
    if (!(jmp_rval = setjmp(jump_env))) {
        bool bitArray[] = {0,1,0,1,0,1,0,1};
        r = get_two_comp(bitArray);
    }
    assert(jmp_rval == 0);
    assert(r == -86);
    TestEnd();
}
void test_two_comp6() {
    int jmp_rval;
    int r;

    TestStart("test_two_comp6");
    should_exit = 0;
    if (!(jmp_rval = setjmp(jump_env))) {
        bool bitArray[] = {1,0,0,0,0,0,0,1};
        r = get_two_comp(bitArray);
    }
    assert(jmp_rval == 0);
    assert(r == -127);
    TestEnd();
}
void test_two_comp7() {
    int jmp_rval;
    int r;

    TestStart("test_two_comp7");
    should_exit = 0;
    if (!(jmp_rval = setjmp(jump_env))) {
        bool bitArray[] = {0,1,1,1,1,1,1,0};
        r = get_two_comp(bitArray);
    }
    assert(jmp_rval == 0);
    assert(r == 126);
    TestEnd();
}

void test_two_comp8() {
    int jmp_rval;
    int r;

    TestStart("test_two_comp8");
    should_exit = 0;
    if (!(jmp_rval = setjmp(jump_env))) {
        bool bitArray[] = {0,0,0,0,0,0,0,1};
        r = get_two_comp(bitArray);
    }
    assert(jmp_rval == 0);
    assert(r == -128);
    TestEnd();
}
void test_two_comp9() {
    int jmp_rval;
    int r;

    TestStart("test_two_comp9");
    should_exit = 0;
    if (!(jmp_rval = setjmp(jump_env))) {
        bool bitArray[] = {1,0,0,0,0,0,0,0};
        r = get_two_comp(bitArray);
    }
    assert(jmp_rval == 0);
    assert(r == 1);
    TestEnd();
}



int main() {
    num_tests = 0;
    tests_passed = 0;
    done = 0;
    test_is_big_endian();
    test_sign_magnitude1();
    test_sign_magnitude2();
    test_sign_magnitude3();
    test_sign_magnitude4();
    test_sign_magnitude5();
    test_sign_magnitude6();
    test_sign_magnitude7();
    test_sign_magnitude8();
    test_two_comp1();
    test_two_comp2();
    test_two_comp3();
    test_two_comp4();
    test_two_comp5();
    test_two_comp6();
    test_two_comp7();
    test_two_comp8();
    test_two_comp9();
    printf("Total tests passed: %d/%d\n", tests_passed, num_tests);
    done = 1;
    return !(tests_passed == num_tests);
}