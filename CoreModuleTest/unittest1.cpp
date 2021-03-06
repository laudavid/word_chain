#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Core\Core.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CoreModuleTest
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(TestMethod1)
        {
            char* input[4] = { "END", "OF", "THE", "WORLD" };
            char* result[4] = { 0 };
            /* 调用Core中封装好的函数 */
            int len = gen_chain_word(input, 4, result, 0, 0, false);
            Assert::AreEqual(len, 2);
            for (int i = 0; i < len - 1; i++)
                Assert::AreEqual(tolower(result[i][strlen(result[i]) - 1]), tolower(result[i + 1][0]));
        }
        TEST_METHOD(TestMethod2)
        {
            char* input[11] = { "Algebra", "Apple", "Zoo", "Elephant", "Under", "Fox", "Dog", "Moon", "Leaf",
                                    "Trick", "Pseudopseudohypoparathyroidism" };
            char* result[11] = { 0 };
            /* 调用Core中封装好的函数 */
            int len = gen_chain_word(input, 11, result, 0, 0, false);
            Assert::AreEqual(len, 4);
            for (int i = 0; i < len - 1; i++)
                Assert::AreEqual(tolower(result[i][strlen(result[i]) - 1]), tolower(result[i + 1][0]));
        }
        TEST_METHOD(TestMethod3)
        {
            char* input[11] = { "Algebra", "Apple", "Zoo", "Elephant", "Under", "Fox", "Dog", "Moon", "Leaf",
                                    "Trick", "Pseudopseudohypoparathyroidism" };
            char* result[11] = { 0 };
            /* 调用Core中封装好的函数 */
            int len = gen_chain_char(input, 11, result, 0, 0, false);
            Assert::AreEqual(len, 2);
            for (int i = 0; i < len - 1; i++)
                Assert::AreEqual(tolower(result[i][strlen(result[i]) - 1]), tolower(result[i + 1][0]));
        }
        TEST_METHOD(TestMethod4)
        {
            char* input[7] = { "Algebra", "Zoo", "Under", "Dog", "Moon", "Leaf",
                                    "Trick" };
            char* result[7] = { 0 };
            /* 调用Core中封装好的函数 */
            try {
                int len = gen_chain_word(input, 7, result, 0, 0, false);
                Assert::AreEqual(0, 1);
            }
            catch (const char *error_message) {
                Assert::AreEqual(error_message, "Error: no word chain meets the requirements");
            }
        }
        TEST_METHOD(TestMethod5)
        {
            char* input[7] = { "Algebra", "Zoo", "Under", "Dog", "Moon", "Leaf",
                                    "Trick" };
            char* result[7] = { 0 };
            /* 调用Core中封装好的函数 */
            try {
                int len = gen_chain_char(input, 7, result, 0, 0, false);
                Assert::AreEqual(0, 1);
            }
            catch (const char *error_message) {
                Assert::AreEqual(error_message, "Error: no word chain meets the requirements");
            }
        }
        TEST_METHOD(TestMethod6)
        {
            char* input[5] = { "Algebra", "Applea", "Zooa", "Elephant", "Under" };
            char* result[5] = { 0 };
            /* 调用Core中封装好的函数 */
            int len = gen_chain_word(input, 5, result, 0, 0, true);
            Assert::AreEqual(len, 3);
            for (int i = 0; i < len - 1; i++)
                Assert::AreEqual(tolower(result[i][strlen(result[i]) - 1]), tolower(result[i + 1][0]));
        }
        TEST_METHOD(TestMethod7)
        {
            char* input[5] = { "Algebra", "Applea", "Zooa", "Elephant", "Under" };
            char* result[5] = { 0 };
            /* 调用Core中封装好的函数 */
            int len = gen_chain_char(input, 5, result, 0, 0, true);
            Assert::AreEqual(len, 3);
            for (int i = 0; i < len - 1; i++)
                Assert::AreEqual(tolower(result[i][strlen(result[i]) - 1]), tolower(result[i + 1][0]));
        }
        TEST_METHOD(TestMethod8)
        {
            char* input[5] = { "Algebra", "Applea", "Zooa", "Elephant", "Under" };
            char* result[5] = { 0 };
            /* 调用Core中封装好的函数 */
            try {
                int len = gen_chain_char(input, 5, result, 0, 0, false);
                Assert::AreEqual(0, 1);
            }
            catch (const char *error_message) {
                Assert::AreEqual(error_message, "Error: word text implies word rings");
            }

        }
        TEST_METHOD(TestMethod9)
        {
            char* input[5] = { "Algebra", "Applea", "Zooa", "Elephant", "Under" };
            char* result[5] = { 0 };
            /* 调用Core中封装好的函数 */
            try {
                int len = gen_chain_char(input, 5, result, 0, 0, false);
                Assert::AreEqual(0, 1);
            }
            catch (const char *error_message) {
                Assert::AreEqual(error_message, "Error: word text implies word rings");
            }
        }
        TEST_METHOD(TestMethod10)
        {
            char* input[5] = { "aa", "aaa", "aaaa", "aaaaa", "a" };
            char* result[5] = { 0 };
            /* 调用Core中封装好的函数 */
            int len = gen_chain_word(input, 5, result, 0, 0, true);
            Assert::AreEqual(len, 5);
            for (int i = 0; i < len - 1; i++)
                Assert::AreEqual(tolower(result[i][strlen(result[i]) - 1]), tolower(result[i + 1][0]));
        }
        TEST_METHOD(TestMethod11)
        {
            char* input[5] = { "aa", "aaa", "aaaa", "aaaaa", "a" };
            char* result[5] = { 0 };
            /* 调用Core中封装好的函数 */
            int len = gen_chain_char(input, 5, result, 0, 0, true);
            Assert::AreEqual(len, 5);
            for (int i = 0; i < len - 1; i++)
                Assert::AreEqual(tolower(result[i][strlen(result[i]) - 1]), tolower(result[i + 1][0]));
        }

        TEST_METHOD(TestMethod12)
        {
            char* input[11] = { "Algebra", "Apple", "Zoo", "Elephant", "Under", "Fox", "Dog", "Moon", "Leaf",
                                    "Trick", "Pseudopseudohypoparathyroidism" };
            char* result[11] = { 0 };
            /* 调用Core中封装好的函数 */
            int len = gen_chain_word(input, 11, result, 'a', 0, false);
            Assert::AreEqual(len, 4);
            for (int i = 0; i < len - 1; i++)
                Assert::AreEqual(tolower(result[i][strlen(result[i]) - 1]), tolower(result[i + 1][0]));
        }
        TEST_METHOD(TestMethod13)
        {
            char* input[11] = { "Algebra", "Apple", "Zoo", "Elephant", "Under", "Fox", "Dog", "Moon", "Leaf",
                                    "Trick", "Pseudopseudohypoparathyroidism" };
            char* result[11] = { 0 };
            /* 调用Core中封装好的函数 */
            int len = gen_chain_char(input, 11, result, 'a', 0, false);
            Assert::AreEqual(len, 4);
            for (int i = 0; i < len - 1; i++)
                Assert::AreEqual(tolower(result[i][strlen(result[i]) - 1]), tolower(result[i + 1][0]));
        }
        TEST_METHOD(TestMethod14)
        {
            char* input[11] = { "Algebra", "Apple", "Zoo", "Elephant", "Under", "Fox", "Dog", "Moon", "Leaf",
                                    "Trick", "Pseudopseudohypoparathyroidism" };
            char* result[11] = { 0 };
            /* 调用Core中封装好的函数 */
            try {
                int len = gen_chain_word(input, 11, result, 0, 'm', false);
                Assert::AreEqual(0, 1);
            }
            catch (const char *error_message) {
                Assert::AreEqual(error_message, "Error: no word chain meets the requirements");
            }
        }
        TEST_METHOD(TestMethod15)
        {
            char* input[11] = { "Algebra", "Apple", "Zoo", "Elephant", "Under", "Fox", "Dog", "Moon", "Leaf",
                                    "Trick", "Pseudopseudohypoparathyroidism" };
            char* result[11] = { 0 };
            /* 调用Core中封装好的函数 */
            try {
                int len = gen_chain_char(input, 11, result, 0, 'm', false);
                Assert::AreEqual(0, 1);
            }
            catch (const char *error_message) {
                Assert::AreEqual(error_message, "Error: no word chain meets the requirements");
            }

        }
        TEST_METHOD(TestMethod16)
        {
            char* input[11] = { "Algebra", "Apple", "Zoo", "Elephant", "Under", "Fox", "Dog", "Moon", "Leaf",
                                    "Trick", "Pseudopseudohypoparathyroidism" };
            char* result[11] = { 0 };
            /* 调用Core中封装好的函数 */
            try {
                int len = gen_chain_word(input, 11, result, 'a', 'm', false);
                Assert::AreEqual(0, 1);
            }
            catch (const char *error_message) {
                Assert::AreEqual(error_message, "Error: no word chain meets the requirements");
            }

        }
        TEST_METHOD(TestMethod17)
        {
            char* input[11] = { "Algebra", "Apple", "Zoo", "Elephant", "Under", "Fox", "Dog", "Moon", "Leaf",
                                    "Trick", "Pseudopseudohypoparathyroidism" };
            char* result[11] = { 0 };
            /* 调用Core中封装好的函数 */
            try {
                int len = gen_chain_char(input, 11, result, 'a', 'm', false);
                Assert::AreEqual(0, 1);
            }
            catch (const char *error_message) {
                Assert::AreEqual(error_message, "Error: no word chain meets the requirements");
            }
        }
        TEST_METHOD(TestMethod18)
        {
            char* input[5] = { "Algebra", "Applea", "Zooa", "Elephant", "Under" };
            char* result[5] = { 0 };
            /* 调用Core中封装好的函数 */
            int len = gen_chain_word(input, 5, result, 'a', 0, true);
            Assert::AreEqual(len, 2);
            for (int i = 0; i < len - 1; i++)
                Assert::AreEqual(tolower(result[i][strlen(result[i]) - 1]), tolower(result[i + 1][0]));
        }
        TEST_METHOD(TestMethod19)
        {
            char* input[5] = { "Algebra", "Applea", "Zooa", "Elephant", "Under" };
            char* result[5] = { 0 };
            /* 调用Core中封装好的函数 */
            int len = gen_chain_char(input, 5, result, 'a', 0, true);
            Assert::AreEqual(len, 2);
            for (int i = 0; i < len - 1; i++)
                Assert::AreEqual(tolower(result[i][strlen(result[i]) - 1]), tolower(result[i + 1][0]));
        }
        TEST_METHOD(TestMethod20)
        {
            char* input[11] = { "Algebra", "Apple", "Zop", "Elephant", "Under", "Fox", "Dog", "Moon", "Leaf",
                                    "Trick", "Pseudopseudohypoparathyroidism" };
            char* result[11] = { 0 };
            /* 调用Core中封装好的函数 */
            int len = gen_chain_char(input, 11, result, 0, 'm', false);
            Assert::AreEqual(len, 2);
            for (int i = 0; i < len - 1; i++)
                Assert::AreEqual(tolower(result[i][strlen(result[i]) - 1]), tolower(result[i + 1][0]));
        }
        TEST_METHOD(TestMethod21)
        {
            char* input[11] = { "Algebra", "Apple", "Zop", "Elephant", "Under", "Fox", "Dog", "Moon", "Leaf",
                                    "Trick", "Pseudopseudohypoparathyroidism" };
            char* result[11] = { 0 };
            /* 调用Core中封装好的函数 */
            int len = gen_chain_word(input, 11, result, 0, 'm', false);
            Assert::AreEqual(len, 2);
            for (int i = 0; i < len - 1; i++)
                Assert::AreEqual(tolower(result[i][strlen(result[i]) - 1]), tolower(result[i + 1][0]));
        }

        TEST_METHOD(TestMethod22)
        {
            char* result[11] = { 0 };
            try {
                int len = gen_chain_word(NULL, 11, result, 0, 'm', false);
                Assert::AreEqual(0, 1);
            }
            catch (const char *error_message) {
                Assert::AreEqual(error_message, "Invalid parameter: 'words' or 'result' is null.");
            }
        }
        TEST_METHOD(TestMethod23)
        {
            char* input[11] = { "Algebra", "Apple", "Zop", "Elephant", "Under", "Fox", "Dog", "Moon", "Leaf",
                                    "Trick", "Pseudopseudohypoparathyroidism" };
            try {
                int len = gen_chain_word(input, 11, NULL, 0, 'm', false);
                Assert::AreEqual(0, 1);
            }
            catch (const char *error_message) {
                Assert::AreEqual(error_message, "Invalid parameter: 'words' or 'result' is null.");
            }
        }
        TEST_METHOD(TestMethod24)
        {
            char* input[11] = { "Algebra", "Apple", "Zop", "Elephant", "Under", "Fox", "Dog", "Moon", "Leaf",
                                    "Trick", "Pseudopseudohypoparathyroidism" };
            char* result[11] = { 0 };
            try {
                int len = gen_chain_word(input, 11, result, ' ', 'm', false);
                Assert::AreEqual(0, 1);
            }
            catch (const char *error_message) {
                Assert::AreEqual(error_message, "Invalid parameter: 'head' or 'tail' is not a letter or 0.");
            }
        }

        TEST_METHOD(TestMethod25)
        {
            char* input[11] = { "Algebra", "Apple", "Zop", "Elephant", "Under", "Fox", "Dog", "Moon", "Leaf",
                                    "Trick", "Pseudopseudohypoparathyroidism" };
            char* result[11] = { 0 };
            try {
                int len = gen_chain_word(input, -1, result, 0, 'm', false);
                Assert::AreEqual(0, 1);
            }
            catch (const char *error_message) {
                Assert::AreEqual(error_message, "Invalid parameter: 'len' is less than 0.");
            }
        }
        TEST_METHOD(TestMethod26)
        {
            char* result[11] = { 0 };
            try {
                int len = gen_chain_char(NULL, 11, result, 0, 'm', false);
                Assert::AreEqual(0, 1);
            }
            catch (const char *error_message) {
                Assert::AreEqual(error_message, "Invalid parameter: 'words' or 'result' is null.");
            }
        }
        TEST_METHOD(TestMethod27)
        {
            char* input[11] = { "Algebra", "Apple", "Zop", "Elephant", "Under", "Fox", "Dog", "Moon", "Leaf",
                                    "Trick", "Pseudopseudohypoparathyroidism" };
            try {
                int len = gen_chain_char(input, 11, NULL, 0, 'm', false);
                Assert::AreEqual(0, 1);
            }
            catch (const char *error_message) {
                Assert::AreEqual(error_message, "Invalid parameter: 'words' or 'result' is null.");
            }
        }
        TEST_METHOD(TestMethod28)
        {
            char* input[11] = { "Algebra", "Apple", "Zop", "Elephant", "Under", "Fox", "Dog", "Moon", "Leaf",
                                    "Trick", "Pseudopseudohypoparathyroidism" };
            char* result[11] = { 0 };
            try {
                int len = gen_chain_char(input, 11, result, 'a', '0', false);
                Assert::AreEqual(0, 1);
            }
            catch (const char *error_message) {
                Assert::AreEqual(error_message, "Invalid parameter: 'head' or 'tail' is not a letter or 0.");
            }
        }

        TEST_METHOD(TestMethod29)
        {
            char* input[11] = { "Algebra", "Apple", "Zop", "Elephant", "Under", "Fox", "Dog", "Moon", "Leaf",
                                    "Trick", "Pseudopseudohypoparathyroidism" };
            char* result[11] = { 0 };
            try {
                int len = gen_chain_char(input, -1, result, 0, 'm', false);
                Assert::AreEqual(0, 1);
            }
            catch (const char *error_message) {
                Assert::AreEqual(error_message, "Invalid parameter: 'len' is less than 0.");
            }
        }
    };
}