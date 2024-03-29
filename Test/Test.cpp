// Test
#include "Format.hpp"

#include "Format/ProgressTimer.hpp"

#define TEST_PERFORMANCE_IN_TOOLS 0

using namespace FormatLibrary;

#include <iostream>
#include <vector>
using namespace std;

// simple test...
void TestProfile()
{
    const int TEST_COUNT = 100000;

    {
        Profile::ProgressTimer Timer("FL");

        for (int i = 0; i < TEST_COUNT; ++i)
        {
            string str;
            StandardLibrary::FormatTo(str, "{0}--#--{1,8}--#--{2}", 100, -40.2f, " String ");
            StandardLibrary::FormatTo(str, "{0}--#--{1,8}--#--{1}", 100, -40.2f);
            StandardLibrary::FormatTo(str, "{0}--#--{1,8}--#--{3}", 100, -40.2f, std::string("xxx"));            
        }
    }

#if !FL_COMPILER_MSVC
#define sprintf_s sprintf
#endif

#if !TEST_PERFORMANCE_IN_TOOLS
    {
        Profile::ProgressTimer Timer("CL");

        for (int i = 0; i < TEST_COUNT; ++i)
        {
            string str;
            char szBuf[64];
            sprintf_s(szBuf, "%d--#--%8.2f--#--%s", 100, -40.2f, " String ");
            str = szBuf;
            sprintf_s(szBuf, "%d--#--%8.2f--#--%f", 100, -40.2f, 0.0f);
            str = szBuf;
            sprintf_s(szBuf, "%d--#--%8.2f--#--%%f", 100, -40.2f);
            str = szBuf;
        }
    }
#endif
}

#if FL_COMPILER_WITH_CXX11 && (FL_COMPILER_MSVC||FL_COMPILER_MACOS)
#include <thread>

// simple test...
void TestProfileMultiThread()
{
    std::thread t0( TestProfile );
    std::thread t1( TestProfile );
    std::thread t2( TestProfile );

    t0.join();
    t1.join();
    t2.join();
}
#endif

int main()
{
    StandardLibrary::STLGlobalPatternStorageA Storage;
    Utility::TAutoString<char> TestStr;

    const char* pszTest = "{0},xxxd{1:d2}={2,3:d2} !! {{}} {0,-5:d8}";
    Storage.LookupPatterns(pszTest, strlen(pszTest));

    std::string str;
    StandardLibrary::FormatTo(str, "test{0}", 10);

    StandardLibrary::FormatTo(str, "{0}", char('c'), short(2));

#if FL_COMPILER_MSVC
    StandardLibrary::FormatTo(str, "0x{0:x}", 100, DWORD(100));
#endif

    std::wstring wstr;
    StandardLibrary::FormatTo(wstr, L"Test{1}, {2:f4}, {0}, {0,4}", L" X ", 20, -10.005f);
    StandardLibrary::FormatTo(wstr, L"Test{1}, {2:f4}, {0}, {0,4}");

    // make an compile error
    // StandardLibrary::FormatTo(wstr, L"Test{1}, {2:f4}, {0}, {0,4}", std::make_shared<int>(new int(100)));

#if FL_COMPILER_HAS_VARIADIC_TEMPLATE
    wstr = StandardLibrary::Format(L"MyTest {0}", 1024);
#endif

    cout << str << endl;
    wcout << wstr << endl;

    TestProfile();
    
#if FL_COMPILER_WITH_CXX11 && (FL_COMPILER_MSVC||FL_COMPILER_MACOS)
    TestProfileMultiThread();
#endif

    return 0;
}

