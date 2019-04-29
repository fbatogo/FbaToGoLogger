#include <gtest/gtest.h>

#include <fbatogologger.h>
#include <consolehelpers.h>

#ifdef USING_QT
#include <QString>
#endif // USING_QT

using namespace fbatogo::logger;

TEST(FbaToGoLoggerTests, LoggingNowhereTests)
{
    ConsoleHelpers conHelper;
    std::string sTemp;
#ifdef USING_QT
    QString qTemp;

    // Redirect our QMessages.
    ASSERT_TRUE(conHelper.captureQMessages());
#endif // USING_QT

    // Capture STDOUT.
    ASSERT_TRUE(conHelper.captureStdOut());

#ifdef USING_QT
    // Write something to the log with a QString.
    qTemp = "Test QString Log Line";
    FbaToGoLogger::getInstance()->info(qTemp);

    // We should get an empty string back from stdOut, since we have not enabled logging to the console.
    EXPECT_EQ("", conHelper.stdOut());
#endif // USING_QT

    // Write something to the log with an std::string.
    sTemp = "Test QString Log Line";
    FbaToGoLogger::getInstance()->info(sTemp);

    // We should get an empty string back from stdOut, since we have not enabled logging to the console.
    EXPECT_EQ("", conHelper.stdOut());

    // Release STDOUT.
    ASSERT_TRUE(conHelper.releaseStdOut());

#ifdef USING_QT
    // Release our QMessages.
    ASSERT_TRUE(conHelper.releaseQMessages());
#endif // USING_QT
}

TEST(FbaToGoLoggerTests, LoggingToConsoleWithConvenienceTests)
{
    ConsoleHelpers conHelper;
    std::string sTemp;

#ifdef USING_QT
    QString qTemp;

    // Redirect our QMessages.
    ASSERT_TRUE(conHelper.captureQMessages());
#endif // USING_QT

    // Capture STDOUT.
    ASSERT_TRUE(conHelper.captureStdOut());

    // Enable logging to the console using our convenience function.
    ASSERT_TRUE(FbaToGoLogger::getInstance()->logToConsole());

#ifdef USING_QT
    // Write something to the log with a QString.
    qTemp = "Test QString Log Line";
    FbaToGoLogger::getInstance()->info(qTemp);

    // We should get an empty string back from stdOut, since we have not enabled logging to the console.
    EXPECT_EQ("Test QString Log Line\n", conHelper.stdOut());
#endif // USING_QT

    // Write something to the log with an std::string.
    sTemp = "Test QString Log Line";
    FbaToGoLogger::getInstance()->info(sTemp);

    // We should get an empty string back from stdOut, since we have not enabled logging to the console.
    EXPECT_EQ("Test QString Log Line\n", conHelper.stdOut());

    // ---  Clear the console logger, and run our tests again.
    FbaToGoLogger::getInstance()->clearWriterExtensions();

#ifdef USING_QT
    // Write something to the log with a QString.
    qTemp = "Test QString Log Line";
    FbaToGoLogger::getInstance()->info(qTemp);

    // We should get an empty string back from stdOut, since we have not enabled logging to the console.
    EXPECT_EQ("", conHelper.stdOut());
#endif // USING_QT

    // Write something to the log with an std::string.
    sTemp = "Test QString Log Line";
    FbaToGoLogger::getInstance()->info(sTemp);

    // We should get an empty string back from stdOut, since we have not enabled logging to the console.
    EXPECT_EQ("", conHelper.stdOut());

    // Release STDOUT.
    ASSERT_TRUE(conHelper.releaseStdOut());

#ifdef USING_QT
    // Release our QMessages.
    ASSERT_TRUE(conHelper.releaseQMessages());
#endif // USING_QT
}
