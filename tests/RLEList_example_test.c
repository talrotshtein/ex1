#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "RLEList.h"
#include "test_utilities.h"

typedef bool (*testFunc)(void);

bool basicTest();

#define TESTS_NAMES             \
    X(basicTest)               \

testFunc tests[] = {
#define X(name) name,
    TESTS_NAMES
#undef X
};

const char *tests_names[] = {
#define X(name) #name,
    TESTS_NAMES
#undef X
};

static int number_of_tests = sizeof(tests) / sizeof(tests[0]);

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        for (int test_idx = 0; test_idx < number_of_tests; test_idx++)
        {
            RUN_TEST(tests[test_idx], tests_names[test_idx]);
        }
        return 0;
    }
    if (argc != 2)
    {
        fprintf(stdout, "Usage: tests <test index>\n");
        return 0;
    }

    int test_idx = strtol(argv[1], NULL, 10);
    if (test_idx < 1 || test_idx > number_of_tests)
    {
        fprintf(stderr, "Invalid test index %d\n", test_idx);
        return 0;
    }

    RUN_TEST(tests[test_idx - 1], tests_names[test_idx - 1]);
    return 0;
}

char mapFunc1(char letter)
{
    char let = letter;
    if(letter == 'd')
    {
        let= 'c';
    }

    return let;
}

bool basicTest(){
    RLEList list = RLEListCreate();
    bool result=true;
    ASSERT_TEST(list != NULL, destroy);


    //adding elements to the list
    ASSERT_TEST(RLEListAppend(list, 'A') == RLE_LIST_SUCCESS, destroy);    // a
    ASSERT_TEST(RLEListAppend(list, 'B') == RLE_LIST_SUCCESS, destroy);    // ac
    ASSERT_TEST(RLEListAppend(list, 'B') == RLE_LIST_SUCCESS, destroy);    // acb
    ASSERT_TEST(RLEListAppend(list, 'a') == RLE_LIST_SUCCESS, destroy);    // acba
    ASSERT_TEST(RLEListAppend(list, 'b') == RLE_LIST_SUCCESS, destroy);    // acbab
    ASSERT_TEST(RLEListAppend(list, 'b') == RLE_LIST_SUCCESS, destroy);    // acbaba
    ASSERT_TEST(RLEListAppend(list, '-') == RLE_LIST_SUCCESS, destroy);    // acbabab
    ASSERT_TEST(RLEListAppend(list, '-') == RLE_LIST_SUCCESS, destroy);    // acbababa
    ASSERT_TEST(RLEListAppend(list, '-') == RLE_LIST_SUCCESS, destroy);    // acbababaa
    ASSERT_TEST(RLEListAppend(list, '-') == RLE_LIST_SUCCESS, destroy);    // acbababaaa
    ASSERT_TEST(RLEListAppend(list, '-') == RLE_LIST_SUCCESS, destroy);    // acbababaaa
    ASSERT_TEST(RLEListAppend(list, '-') == RLE_LIST_SUCCESS, destroy);    // acbababaaa
    ASSERT_TEST(RLEListAppend(list, '-') == RLE_LIST_SUCCESS, destroy);    // acbababaaa
    ASSERT_TEST(RLEListAppend(list, '-') == RLE_LIST_SUCCESS, destroy);    // acbababaaa
    ASSERT_TEST(RLEListAppend(list, '-') == RLE_LIST_SUCCESS, destroy);    // acbababaaa
    ASSERT_TEST(RLEListAppend(list, '-') == RLE_LIST_SUCCESS, destroy);    // acbababaaa
    ASSERT_TEST(RLEListAppend(list, '-') == RLE_LIST_SUCCESS, destroy);    // acbababaaa
    ASSERT_TEST(RLEListAppend(list, '-') == RLE_LIST_SUCCESS, destroy);    // acbababaaa
    ASSERT_TEST(RLEListAppend(list, '\n') == RLE_LIST_SUCCESS, destroy);    // acbababaaa
    ASSERT_TEST(RLEListAppend(list, '\n') == RLE_LIST_SUCCESS, destroy);    // acbababaaa
    ASSERT_TEST(RLEListAppend(list, 'a') == RLE_LIST_SUCCESS, destroy);    // acbababaaa
    RLEListResult res = RLE_LIST_SUCCESS;
    res = RLEListMap( list, mapFunc1);
    // check if the represented string is ""A1\nB2\na1\nb2\n-12\n\n2\na1\n""
    char *expected = "A1\nB2\na1\nb2\n-12\n\n2\na1\n";
    char* string = RLEListExportToString(list,NULL);
    for(int i =0;i<=strlen(string);i++)
    {
        if(string[i]!=expected[i])
            printf("%d", i);
    }
    /*const char *s = "aaaaaaaa";
    char it;
    for(int i=0; i<RLEListSize(list); i++)
    {
        it=RLEListGet(list, i, NULL);
        ASSERT_TEST(it == s[i], destroy);
    }
    //check if the length's are equal
    ASSERT_TEST(RLEListSize(list)==strlen(s), destroy);
     */
    destroy:
    RLEListDestroy(list);
    return result;
}

