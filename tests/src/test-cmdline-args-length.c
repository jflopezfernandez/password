
#include "password-test.h"

void testLengthParameter(void) {
    for (size_t i = 1; i <= 16; ++i) {
        size_t length = strlen(generateRandomStrings(i, 1)[0]);
        printf("Length: %lu, Expected: %lu\n", length, i);
        CU_ASSERT(length == i);
    }
}

int main(void)
{
    /* Initialize the CUnit test registry */
    if (CU_initialize_registry() != CUE_SUCCESS) {
        return CU_get_error();
    }

    /* Add test suite to the test registry */
    CU_pSuite testSuiteLength = CU_add_suite("Length Parameter Test Suite", NULL, NULL);

    /* Make sure the testSuiteLength was added successfully */
    if (testSuiteLength == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the test suite */
    if ((CU_add_test(testSuiteLength, "Length parameter", testLengthParameter) == NULL)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic Interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}
