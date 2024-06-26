/**
 *\file     main.c
 *\note     UTF-8
 *\author   xt
 *\version  1.0.0
 *\date     2024.06.26
 *\brief    单元测试
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "CUnit.h"
#include "Basic.h"
#include "Console.h"
#include "CUCurses.h"
#include "Automated.h"
#include "xt_base64.h"
#include "xt_http.h"
#include "xt_uri.h"
#include "xt_list.h"

#ifdef _WINDOWS
#include <windows.h>
#include "resource.h"
#include "xt_character_set.h"
#include "xt_exe_ico.h"
#endif

static int suite_success_init(void) { return 0; }
static int suite_success_clean(void) { return 0; }

static int suite_failure_init(void) { return 1;}
static int suite_failure_clean(void) { return 1; }

// CU_TEST
// CU_ASSERT
// CU_ASSERT_TRUE
// CU_ASSERT_FALSE
// CU_FAIL("This is a failure.");
// CU_ASSERT_EQUAL(10, 10);
// CU_ASSERT_NOT_EQUAL(10, 11);
// CU_ASSERT_PTR_EQUAL((void*)0x100, (void*)0x100);
// CU_ASSERT_PTR_NOT_EQUAL((void*)0x100, (void*)0x101);
// CU_ASSERT_PTR_NULL((void*)(NULL));
// CU_ASSERT_PTR_NOT_NULL((void*)0x100);
// CU_ASSERT_STRING_EQUAL("test", "test");
// CU_ASSERT_STRING_NOT_EQUAL("test", "123");
// CU_ASSERT_NSTRING_EQUAL(str1, str2, strlen(str1));
// CU_ASSERT_NSTRING_NOT_EQUAL(str1, str2, 3);
// CU_ASSERT_DOUBLE_EQUAL(10, 10.0001, 0.0001);
// CU_ASSERT_DOUBLE_NOT_EQUAL(10, 10.001, 0.0001);
// CU_TEST_FATAL(CU_TRUE); CU_FALSE

static void case_base64_encode(void)
{
    char in[10];
    char out[10];
    unsigned int in_len;
    unsigned int out_len;

    CU_ASSERT(base64_encode(NULL, 1, out, &out_len) != 0);
    CU_ASSERT(base64_encode("123", 3, NULL, &out_len) != 0);

    out_len = 0;
    CU_ASSERT(base64_encode("123", 0, out, &out_len) != 0);

    out_len = 0;
    CU_ASSERT(base64_encode("123", 3, out, &out_len) != 0);

    out_len = 3;
    CU_ASSERT(base64_encode("123", 3, out, &out_len) != 0);

    strcpy_s(in, sizeof(in), "");
    in_len = strlen(in);
    out_len = sizeof(out);
    CU_ASSERT(base64_encode(in, in_len, out, &out_len) == 0);
    CU_ASSERT(out_len == 0);
    CU_ASSERT_STRING_EQUAL(out, "");

    strcpy_s(in, sizeof(in), "1");
    in_len = strlen(in);
    out_len = sizeof(out);
    CU_ASSERT(base64_encode(in, in_len, out, &out_len) == 0);
    CU_ASSERT_STRING_EQUAL(out, "MQ==");

    strcpy_s(in, sizeof(in), "12");
    in_len = strlen(in);
    out_len = sizeof(out);
    CU_ASSERT(base64_encode(in, in_len, out, &out_len) == 0);
    CU_ASSERT_STRING_EQUAL(out, "MTI=");

    strcpy_s(in, sizeof(in), "123");
    in_len = strlen(in);
    out_len = sizeof(out);
    CU_ASSERT(base64_encode(in, in_len, out, &out_len) == 0);
    CU_ASSERT_STRING_EQUAL(out, "MTIz");

    strcpy_s(in, sizeof(in), "1234");
    in_len = strlen(in);
    out_len = sizeof(out);
    CU_ASSERT(base64_encode(in, in_len, out, &out_len) == 0);
    CU_ASSERT_STRING_EQUAL(out, "MTIzNA==");

    strcpy_s(in, sizeof(in), "12345");
    in_len = strlen(in);
    out_len = sizeof(out);
    CU_ASSERT(base64_encode(in, in_len, out, &out_len) == 0);
    CU_ASSERT_STRING_EQUAL(out, "MTIzNDU=");
}

static void case_base64_decode(void)
{
    char in[10];
    char out[10];
    unsigned int in_len;
    unsigned int out_len;

    CU_ASSERT(base64_decode(NULL, 1, out, &out_len) != 0);
    CU_ASSERT(base64_decode("123", 3, NULL, &out_len) != 0);

    out_len = 0;
    CU_ASSERT(base64_decode("123", 0, out, &out_len) != 0);

    out_len = 0;
    CU_ASSERT(base64_decode("123", 3, out, &out_len) != 0);

    out_len = 3;
    CU_ASSERT(base64_decode("123", 3, out, &out_len) == 0);
    CU_ASSERT(out_len == 0);

    strcpy_s(in, sizeof(in), "");
    in_len = strlen(in);
    out_len = sizeof(out);
    CU_ASSERT(base64_decode(in, in_len, out, &out_len) != 0);

    strcpy_s(in, sizeof(in), "MQ==");
    in_len = strlen(in);
    out_len = sizeof(out);
    CU_ASSERT(base64_decode(in, in_len, out, &out_len) == 0);
    CU_ASSERT_STRING_EQUAL(out, "1");

    strcpy_s(in, sizeof(in), "MTI=");
    in_len = strlen(in);
    out_len = sizeof(out);
    CU_ASSERT(base64_decode(in, in_len, out, &out_len) == 0);
    CU_ASSERT_STRING_EQUAL(out, "12");

    strcpy_s(in, sizeof(in), "MTIz");
    in_len = strlen(in);
    out_len = sizeof(out);
    CU_ASSERT(base64_decode(in, in_len, out, &out_len) == 0);
    CU_ASSERT_STRING_EQUAL(out, "123");

    strcpy_s(in, sizeof(in), "MTIzNA==");
    in_len = strlen(in);
    out_len = sizeof(out);
    CU_ASSERT(base64_decode(in, in_len, out, &out_len) == 0);
    CU_ASSERT_STRING_EQUAL(out, "1234");

    strcpy_s(in, sizeof(in), "MTIzNDU=");
    in_len = strlen(in);
    out_len = sizeof(out);
    CU_ASSERT(base64_decode(in, in_len, out, &out_len) == 0);
    CU_ASSERT_STRING_EQUAL(out, "12345");
}

#ifdef _WINDOWS
static void case_utf8_unicode(void)
{
    unsigned short out_short[10];
    unsigned int out_short_len;

    CU_ASSERT(utf8_unicode(NULL, 1, out_short, &out_short_len) != 0);
    CU_ASSERT(utf8_unicode("", 0, out_short, &out_short_len) != 0);
    CU_ASSERT(utf8_unicode("", 1, NULL, &out_short_len) != 0);
    CU_ASSERT(utf8_unicode("", 1, out_short, NULL) != 0);

    out_short_len = sizeof(out_short)/sizeof(out_short[0]);
    CU_ASSERT(utf8_unicode("123", 3, out_short, &out_short_len) == 0);
    CU_ASSERT(out_short_len == 3);
    CU_ASSERT(out_short[0] == L'1');
    CU_ASSERT(out_short[1] == L'2');
    CU_ASSERT(out_short[2] == L'3');
    CU_ASSERT(out_short[3] == L'\0');

    out_short_len = sizeof(out_short)/sizeof(out_short[0]);
    CU_ASSERT(utf8_unicode("测试", 6, out_short, &out_short_len) == 0);
    CU_ASSERT(out_short_len == 2);
    CU_ASSERT(out_short[0] == 27979);
    CU_ASSERT(out_short[1] == 35797);
    CU_ASSERT(out_short[2] == L'\0');
}

static void case_unicode_gbk(void)
{
    unsigned char out[10];
    unsigned int out_len;

    CU_ASSERT(unicode_gbk(NULL, 1, out, &out_len) != 0);
    CU_ASSERT(unicode_gbk(L"", 0, out, &out_len) != 0);
    CU_ASSERT(unicode_gbk(L"", 1, NULL, &out_len) != 0);
    CU_ASSERT(unicode_gbk(L"", 1, out, NULL) != 0);

    CU_ASSERT(unicode_gbk(L"123", 3, out, &out_len) == 0);
    CU_ASSERT(out_len == 3);
    CU_ASSERT(out[0] == '1');
    CU_ASSERT(out[1] == '2');
    CU_ASSERT(out[2] == '3');
    CU_ASSERT(out[3] == '\0');

    out_len = sizeof(out);
    CU_ASSERT(unicode_gbk(L"测试", 2, out, &out_len) == 0);
    CU_ASSERT(out_len == 4);
    CU_ASSERT(out[0] == 0xb2);
    CU_ASSERT(out[1] == 0xe2);
    CU_ASSERT(out[2] == 0xca);
    CU_ASSERT(out[3] == 0xd4);
    CU_ASSERT(out[4] == '\0');
}

static void case_unicode_utf8(void)
{
    unsigned char out[10];
    unsigned int out_len;

    CU_ASSERT(unicode_utf8(NULL, 1, out, &out_len) != 0);
    CU_ASSERT(unicode_utf8(L"", 0, out, &out_len) != 0);
    CU_ASSERT(unicode_utf8(L"", 1, NULL, &out_len) != 0);
    CU_ASSERT(unicode_utf8(L"", 1, out, NULL) != 0);

    CU_ASSERT(unicode_utf8(L"123", 3, out, &out_len) == 0);
    CU_ASSERT(out_len == 3);
    CU_ASSERT(out[0] == '1');
    CU_ASSERT(out[1] == '2');
    CU_ASSERT(out[2] == '3');
    CU_ASSERT(out[3] == '\0');

    out_len = sizeof(out);
    CU_ASSERT(unicode_utf8(L"测试", 2, out, &out_len) == 0);
    CU_ASSERT(out_len == 6);
    CU_ASSERT(strcmp(out, "测试") == 0);
}

static void case_gbk_utf8(void)
{
    unsigned char out[10];
    unsigned int out_len;

    CU_ASSERT(gbk_utf8(NULL, 1, out, &out_len) != 0);
    CU_ASSERT(gbk_utf8("", 0, out, &out_len) != 0);
    CU_ASSERT(gbk_utf8("", 1, NULL, &out_len) != 0);
    CU_ASSERT(gbk_utf8("", 1, out, NULL) != 0);

    CU_ASSERT(gbk_utf8("123", 3, out, &out_len) == 0);
    CU_ASSERT(out_len == 3);
    CU_ASSERT(out[0] == '1');
    CU_ASSERT(out[1] == '2');
    CU_ASSERT(out[2] == '3');
    CU_ASSERT(out[3] == '\0');

    unsigned char in[] = { 0xb2, 0xe2, 0xca, 0xd4 };

    out_len = sizeof(out);
    CU_ASSERT(gbk_utf8(in, 4, out, &out_len) == 0);
    CU_ASSERT(out_len == 6);
    CU_ASSERT(strcmp(out, "测试") == 0);
}

static void case_exe_ico(void)
{
    unsigned char out[1024];
    unsigned int out_len;

    CU_ASSERT(exe_ico_get_data(0, NULL, &out_len) != 0);
    CU_ASSERT(exe_ico_get_data(0, out, NULL) != 0);
    CU_ASSERT(exe_ico_get_data(0, NULL, NULL) != 0);

    out_len = sizeof(out);
    CU_ASSERT(exe_ico_get_data(IDI_GREEN, out, &out_len) == 0);
    CU_ASSERT(out_len == 88413);
}

#endif

int http_callback(const p_xt_http_data data)
{
    return 0;
}

static void case_http_init(void)
{
    xt_http http = { 0 };

    CU_ASSERT(http_init(NULL, 80, http_callback, &http) != 0);
    CU_ASSERT(http_init("192.168.1.1", 0, http_callback, &http) != 0);
    CU_ASSERT(http_init("192.168.1.1", 80, NULL, &http) != 0);
    CU_ASSERT(http_init("192.168.1.1", 80, http_callback, NULL) != 0);

    CU_ASSERT(http_init("0.0.0.0", 80, http_callback, &http) == 0);
    CU_ASSERT_TRUE(http.run);
}

static void case_uri_encode(void)
{
    char out[32];
    unsigned int out_len;
    CU_ASSERT(uri_encode(NULL, 80, out, &out_len) != 0);
    CU_ASSERT(uri_encode("123", 0, out, &out_len) != 0);
    CU_ASSERT(uri_encode("123", 3, NULL, &out_len) != 0);
    CU_ASSERT(uri_encode("123", 3, out, NULL) != 0);

    out_len = sizeof(out);
    CU_ASSERT(uri_encode("123", 3, out, &out_len) == 0);
    CU_ASSERT(out_len == 3);
    CU_ASSERT_STRING_EQUAL(out, "123");

    out_len = sizeof(out);
    CU_ASSERT(uri_encode("测试", 6, out, &out_len) == 0);
    CU_ASSERT_STRING_EQUAL(out, "%E6%B5%8B%E8%AF%95");
}

static void case_uri_decode(void)
{
    unsigned char out[1024];
    unsigned int out_len;
    CU_ASSERT(uri_decode(NULL, 80, out, &out_len) != 0);
    CU_ASSERT(uri_decode("123", 0, out, &out_len) != 0);
    CU_ASSERT(uri_decode("123", 3, NULL, &out_len) != 0);
    CU_ASSERT(uri_decode("123", 3, out, NULL) != 0);

    out_len = sizeof(out);
    CU_ASSERT(uri_decode("123", 3, out, &out_len) == 0);
    CU_ASSERT(out_len == 3);
    CU_ASSERT_STRING_EQUAL(out, "123");

    out_len = sizeof(out);
    CU_ASSERT(uri_decode("%E6%B5%8B%E8%AF%95", 18, out, &out_len) == 0);
    CU_ASSERT(out_len == 6);
    CU_ASSERT_STRING_EQUAL(out, "测试");

    out_len = sizeof(out);
    CU_ASSERT(uri_decode("%E6%B5%8B----------%E8%AF%95", 18, out, &out_len) == 0);
    CU_ASSERT(out_len == 16);
    CU_ASSERT_STRING_EQUAL(out, "测----------试");

    out_len = sizeof(out);
    CU_ASSERT(uri_decode("----%E6%B5%8B%E8%AF%95", 18, out, &out_len) == 0);
    CU_ASSERT(out_len == 10);
    CU_ASSERT_STRING_EQUAL(out, "----测试");

    out_len = sizeof(out);
    CU_ASSERT(uri_decode("%E6%B5%8B%E8%AF%95----", 18, out, &out_len) == 0);
    CU_ASSERT(out_len == 10);
    CU_ASSERT_STRING_EQUAL(out, "测试----");

    out_len = sizeof(out);
    CU_ASSERT(uri_decode("----%E6%B5%8B%E8%AF%95----", 18, out, &out_len) == 0);
    CU_ASSERT(out_len == 14);
    CU_ASSERT_STRING_EQUAL(out, "----测试----");

    out_len = sizeof(out);
    CU_ASSERT(uri_decode("----%E6%B5%8B%-%E8%AF%95----", 18, out, &out_len) == 0);
    CU_ASSERT(out_len == 16);
    CU_ASSERT_STRING_EQUAL(out, "----测%-试----");

    out_len = sizeof(out);
    CU_ASSERT(uri_decode("----%E6%B5%8B++++%E8%AF%95----", 18, out, &out_len) == 0);
    CU_ASSERT(out_len == 18);
    CU_ASSERT_STRING_EQUAL(out, "----测++++试----");

    char *p = "https://www.baidu.com/s?ie=utf-8&f=8&rsv_bp=1&tn=baidu&wd=%E4%BD%A0%E5%A5%BD&oq=strcpy_s&rsv_pq=fd454a1200143e5a&rsv_t=1cc8u%2BqQXUWLNbQHMsuruph7lbiAm7ymo2YA0R1zV4xZsaHPWjGnMGK4nlc&rqlang=cn&rsv_enter=0&rsv_dl=tb&rsv_btype=t&inputT=4637&rsv_sug3=47&rsv_sug1=43&rsv_sug7=101&rsv_sug2=0&rsv_sug4=4637";
    out_len = sizeof(out);
    CU_ASSERT(uri_decode(p, strlen(p), out, &out_len) == 0);
    CU_ASSERT(out_len == 284);
    CU_ASSERT_STRING_EQUAL(out, "https://www.baidu.com/s?ie=utf-8&f=8&rsv_bp=1&tn=baidu&wd=你好&oq=strcpy_s&rsv_pq=fd454a1200143e5a&rsv_t=1cc8u+qQXUWLNbQHMsuruph7lbiAm7ymo2YA0R1zV4xZsaHPWjGnMGK4nlc&rqlang=cn&rsv_enter=0&rsv_dl=tb&rsv_btype=t&inputT=4637&rsv_sug3=47&rsv_sug1=43&rsv_sug7=101&rsv_sug2=0&rsv_sug4=4637");
}

static void case_list_init(void)
{
    CU_ASSERT(list_init(NULL) != 0);
    CU_ASSERT(list_uninit(NULL) != 0);
}

static CU_TestInfo cases[] =
{
    { "case_base64_encode", case_base64_encode },
    { "case_base64_decode", case_base64_decode },
#ifdef _WINDOWS
    { "case_utf8_unicode",  case_utf8_unicode },
    { "case_unicode_gbk",   case_unicode_gbk },
    { "case_unicode_utf8",  case_unicode_utf8 },
    { "case_gbk_utf8",      case_gbk_utf8 },
    { "case_exe_ico",       case_exe_ico },
#endif
    { "case_http_init",     case_http_init },
    { "case_uri_encode",    case_uri_encode },
    { "case_uri_decode",    case_uri_decode },
    { "case_list_init",     case_list_init },
	CU_TEST_INFO_NULL,
};

static CU_SuiteInfo suites[] =
{
    { "utitly",  suite_success_init, suite_success_clean, suite_failure_init, suite_failure_clean, cases},
	CU_SUITE_INFO_NULL,
};


#ifdef _WINDOWS
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
void main()
#endif
{
    CU_initialize_registry();
    assert(NULL != CU_get_registry());
    assert(!CU_is_test_running());

	if (CU_register_suites(suites) != CUE_SUCCESS)
    {
		fprintf(stderr, "suite registration failed - %s\n",	CU_get_error_msg());
		exit(EXIT_FAILURE);
	}

    //CU_set_error_action(CUEA_IGNORE);     // CUEA_IGNORE,CUEA_FAIL,CUEA_ABORT;
    //CU_basic_set_mode(CU_BRM_VERBOSE);    // CU_BRM_SILENT,CU_BRM_NORMAL,CU_BRM_VERBOSE;
    //CU_basic_run_tests();                 // 基础模式
    //CU_console_run_tests();               // 控制台模式

    //输出XML
    CU_set_output_filename("result");
    //CU_list_tests_to_file();
    CU_automated_run_tests();

    CU_cleanup_registry();
}
