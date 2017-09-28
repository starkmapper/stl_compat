#pragma hdrstop
#pragma argsused

#ifdef _WIN32
#include <tchar.h>
#else
typedef char _TCHAR;
#define _tmain main
#endif

#define xstr(s) str(s)
#define str(s) #s
#define TEST_MODULE_NAME xstr(TEST_TARGET)

#include "TestBase.h"

#include <stdio.h>
#include <conio.h>

int _tmain(int argc, _TCHAR* argv[])
{
  // Set project title
  TDOG_SET_PROJECT_NAME("Orbit " TEST_MODULE_NAME);
  //TDOG_SET_PROJECT_VERSION(TDOG_LIB_VERSION);
  //TDOG_SET_PROJECT_DESC("Something something Orbit stuff");

  // Define the report style
  TDOG_SET_DEFAULT_REPORT(tdog::RS_TEXT_SUMMARY);

  // Additional reports
  TDOG_ADD_REPORT(tdog::RS_TEXT_VERBOSE, "./" TEST_MODULE_NAME ".report.txt");
  TDOG_ADD_REPORT(tdog::RS_HTML_SUMMARY, "./" TEST_MODULE_NAME ".summary.html");
  TDOG_ADD_REPORT(tdog::RS_HTML_VERBOSE, "./" TEST_MODULE_NAME ".report.html");
  TDOG_ADD_REPORT(tdog::RS_XML, "./" TEST_MODULE_NAME ".report.xml");

  // Run the tests
  // Returns zero on success
  return TDOG_RUN_CMD(argc, argv, true);
}
