#include <Format/Common/Build.hpp>

#if FL_PLATFORM_WINDOWS
#pragma warning(push)
#pragma warning(disable:4616)
#endif
#include <gtest/gtest.h>
#if FL_PLATFORM_WINDOWS
#pragma warning(pop)
#endif

#include <Format/Format.hpp>
#include <Format/StandardLibraryAdapter.hpp>

using namespace FormatLibrary;

TEST(Format, STL_Char_Format)
{
    const std::string i0 = "Hello CppMiniToolkit";
    std::string r0 = StandardLibrary::Format(i0.c_str());
    EXPECT_EQ(r0, i0);

    const std::string i1 = "Hello CppMiniToolkit {0}";
    std::string r1 = StandardLibrary::Format(i1.c_str(), 1024);
    EXPECT_EQ(r1, "Hello CppMiniToolkit 1024");

    const std::string r2 = StandardLibrary::Format("{0}--#--{1,8}--#--{2}", 100, -40.2f, " String ");
    EXPECT_EQ(r2, "100--#--  -40.20--#-- String ");

    const std::string r3 = StandardLibrary::Format("{0}--#--{1,8}--#--{1}", 100, -40.2f);
    EXPECT_EQ(r3, "100--#--  -40.20--#---40.20");

    const std::string r4 = StandardLibrary::Format("{0}--#--{1,8}--#--{3}", 100, -40.2f, std::string("xxx"));
    EXPECT_EQ(r4, "100--#--  -40.20--#--{3}");

    const std::string r5 = StandardLibrary::Format("{0}", char('c'), short(2));
    EXPECT_EQ(r5, "c");

    const std::string r6 = StandardLibrary::Format("0x{0:x}", 100, (unsigned long)(100));
    EXPECT_EQ(r6, "0x64");

    // gen compile error
    //StandardLibrary::Format("{0}", std::wstring(L"x"));
}

TEST(Format, STL_Char_FormatTo)
{
    std::string v;

    const std::string i0 = "Hello CppMiniToolkit";
    StandardLibrary::FormatTo(v, i0.c_str());
    EXPECT_EQ(v, i0);

    const std::string i1 = "Hello CppMiniToolkit {0}";
    StandardLibrary::FormatTo(v, i1.c_str(), 1024);
    EXPECT_EQ(v, "Hello CppMiniToolkit 1024");

    StandardLibrary::FormatTo(v, "{0}--#--{1,8}--#--{2}", 100, -40.2f, " String ");
    EXPECT_EQ(v, "100--#--  -40.20--#-- String ");

    StandardLibrary::FormatTo(v, "{0}--#--{1,8}--#--{1}", 100, -40.2f);
    EXPECT_EQ(v, "100--#--  -40.20--#---40.20");

    StandardLibrary::FormatTo(v, "{0}--#--{1,8}--#--{3}", 100, -40.2f, std::string("xxx"));
    EXPECT_EQ(v, "100--#--  -40.20--#--{3}");

    StandardLibrary::FormatTo(v, "{0}", char('c'), short(2));
    EXPECT_EQ(v, "c");

    StandardLibrary::FormatTo(v, "0x{0:x}", 100, (unsigned long)(100));
    EXPECT_EQ(v, "0x64");
}

TEST(Format, STL_WChar_Format)
{   
    const std::wstring r7 = StandardLibrary::Format(L"Test{1}, {2:f4}, {0}, {0,4}", L" X ", 20, -10.005f);
    EXPECT_EQ(r7, L"Test20, -10.0050,  X ,   X ");

    const std::wstring r8 = StandardLibrary::Format(L"Test{1}, {2:f4}, {0}, {0,4}");
    EXPECT_EQ(r8, L"Test{1}, {2:f4}, {0}, {0,4}");

    const std::wstring r9 = StandardLibrary::Format(std::wstring(L"Test{1}, {2:f4}, {0}, {0,4}"), L" X ", 20, -10.005f);
    EXPECT_EQ(r9, L"Test20, -10.0050,  X ,   X ");

    const std::wstring r11 = StandardLibrary::Format(L"\u4F60\u597D : {0}", L"\u4E2D\u6587");
    EXPECT_EQ(r11, L"\u4F60\u597D : \u4E2D\u6587");
}

TEST(Format, STL_WChar_FormatTo)
{
    std::wstring v;

    StandardLibrary::FormatTo(v, L"Test{1}, {2:f4}, {0}, {0,4}", L" X ", 20, -10.005f);
    EXPECT_EQ(v, L"Test20, -10.0050,  X ,   X ");

    // test invalid param
    StandardLibrary::FormatTo(v, L"Test{1}, {2:f4}, {0}, {0,4}");
    EXPECT_EQ(v, L"Test{1}, {2:f4}, {0}, {0,4}");

    StandardLibrary::FormatTo(v, std::wstring(L"Test{1}, {2:f4}, {0}, {0,4}"), L" X ", 20, -10.005f);
    EXPECT_EQ(v, L"Test20, -10.0050,  X ,   X ");

    StandardLibrary::FormatTo(v, L"\u4F60\u597D : {0}", L"\u4E2D\u6587");
    EXPECT_EQ(v, L"\u4F60\u597D : \u4E2D\u6587");
}

TEST(Format, TestSingleArg) 
{
    EXPECT_EQ(StandardLibrary::Format("{0}", 123), "123");
}

TEST(Format, TestMultipleArgs) 
{
    EXPECT_EQ(StandardLibrary::Format("{0} {1}", 123, "hello"), "123 hello");
}

TEST(Format, TestReorderedArgs) 
{
    EXPECT_EQ(StandardLibrary::Format("{1} {0}", 123, "hello"), "hello 123");
}

TEST(Format, TestRepeatedArgs) 
{
    EXPECT_EQ(StandardLibrary::Format("{0} {0}", 123), "123 123");
}

TEST(Format, TestString) 
{
    EXPECT_EQ(StandardLibrary::Format("{0}", "hello"), "hello");
}

TEST(Format, TestChar) 
{
    EXPECT_EQ(StandardLibrary::Format("{0}", 'a'), "a");
}

TEST(Format, TestBool) 
{
    EXPECT_EQ(StandardLibrary::Format("{0}", true), "True");
    EXPECT_EQ(StandardLibrary::Format("{0}", false), "False");
}

TEST(Format, TestEmptyFormat) 
{
    EXPECT_EQ(StandardLibrary::Format("", 123), "");
}

TEST(Format, TestNoArgs) 
{
    EXPECT_EQ(StandardLibrary::Format("hello"), "hello");
}

TEST(Format, TestMultipleFormats) 
{
    EXPECT_EQ(StandardLibrary::Format("{0} {1} {2}", 123, "hello", 1.23), "123 hello 1.23");
}

TEST(Format, TestRightAlign)
{
    EXPECT_EQ(StandardLibrary::Format("{0,5}", 123), "  123");
}

TEST(Format, TestLeftAlign)
{
    EXPECT_EQ(StandardLibrary::Format("{0,-5}", 123), "123  ");
}

TEST(Format, TestRightAlignString)
{
    EXPECT_EQ(StandardLibrary::Format("{0,5}", "hi"), "   hi");
}

TEST(Format, TestLeftAlignString)
{
    EXPECT_EQ(StandardLibrary::Format("{0,-5}", "hi"), "hi   ");
}

TEST(Format, TestRightAlignMultiple)
{
    EXPECT_EQ(StandardLibrary::Format("{0,5} {1,5}", 123, "hi"), "  123    hi");
}

TEST(Format, TestLeftAlignMultiple)
{
    EXPECT_EQ(StandardLibrary::Format("{0,-5} {1,-5}", 123, "hi"), "123   hi   ");
}

TEST(Format, TestMixedAlign)
{
    EXPECT_EQ(StandardLibrary::Format("{0,5} {1,-5}", 123, "hi"), "  123 hi   ");
}

TEST(Format, TestExponentialNotation)
{
    EXPECT_EQ(StandardLibrary::Format("{0:e}", 123.456), "1.234560e+02");
    EXPECT_EQ(StandardLibrary::Format("{0:E}", 123.456), "1.234560E+02");
    EXPECT_EQ(StandardLibrary::Format("{0:e3}", 123.456), "1.235e+02");
    EXPECT_EQ(StandardLibrary::Format("{0:E3}", 123.456), "1.235E+02");
}

TEST(Format, TestHexadecimalNotation)
{
    EXPECT_EQ(StandardLibrary::Format("{0:x}", 123), "7b");
    EXPECT_EQ(StandardLibrary::Format("{0:X}", 123), "7B");
    EXPECT_EQ(StandardLibrary::Format("{0:x8}", 123), "0000007b");
    EXPECT_EQ(StandardLibrary::Format("{0:X8}", 123), "0000007B");
}

TEST(Format, TestWidth)
{
    EXPECT_EQ(StandardLibrary::Format("{0,5}", 123), "  123");
    EXPECT_EQ(StandardLibrary::Format("{0,-5}", 123), "123  ");
    EXPECT_EQ(StandardLibrary::Format("{0,5}", "hi"), "   hi");
    EXPECT_EQ(StandardLibrary::Format("{0,-5}", "hi"), "hi   ");
}

TEST(Format, TestFloatingPointPrecision)
{
    EXPECT_EQ(StandardLibrary::Format("{0:f}", 123.456), "123.46");
    EXPECT_EQ(StandardLibrary::Format("{0:f3}", 123.456), "123.456");
    EXPECT_EQ(StandardLibrary::Format("{0:f6}", 123.456), "123.456000");
    EXPECT_EQ(StandardLibrary::Format("{0:f0}", 123.456), "123");
}

TEST(Format, TestEscapeBraces)
{
    EXPECT_EQ(StandardLibrary::Format("{{0}}"), "{0}");
    EXPECT_EQ(StandardLibrary::Format("{{0}}1"), "{0}1");
    EXPECT_EQ(StandardLibrary::Format("a{{0}}1a"), "a{0}1a");
    EXPECT_EQ(StandardLibrary::Format("{{{0}}}", 1), "{1}");
    EXPECT_EQ(StandardLibrary::Format("{{0}}, {0}", 1), "{0}, 1");
}

TEST(Format, TestOtherCharacters)
{
    EXPECT_EQ(StandardLibrary::Format("{0} is {1} years old", "John", 30), "John is 30 years old");
}
