#include <gtest/gtest.h>

#include <extensions/consolewriterextension.h>

#include <consolehelpers.h>

using namespace fbatogo::logger::extension;

TEST(ConsoleWriterExtensionTests, WriteLogsTest)
{
    ConsoleHelpers conHelper;
    ConsoleWriterExtension writer;

#ifdef USING_QT
    // We need to configure a handler to redirect the output to STDOUT.
    ASSERT_TRUE(conHelper.captureQMessages());
#endif // USING_QT

    // Capture the STDOUT stream.
    ASSERT_TRUE(conHelper.captureStdOut());

    // Write empty strings and check them.
    writer.debug("");
    EXPECT_EQ("\n", conHelper.stdOut());

    writer.error("");
    EXPECT_EQ("\n", conHelper.stdOut());

    writer.info("");
    EXPECT_EQ("\n", conHelper.stdOut());

    writer.warning("");
    EXPECT_EQ("\n", conHelper.stdOut());

    // Write a string with content.
    writer.debug("This is a debug line.");
    EXPECT_EQ("This is a debug line.\n", conHelper.stdOut());

    writer.error("This is an error line.");
    EXPECT_EQ("This is an error line.\n", conHelper.stdOut());

    writer.warning("This is a warning line.");
    EXPECT_EQ("This is a warning line.\n", conHelper.stdOut());

    writer.info("This is an info line.");
    EXPECT_EQ("This is an info line.\n", conHelper.stdOut());

    // Restore old cout.
    ASSERT_TRUE(conHelper.releaseStdOut());

#ifdef USING_QT
    // Restore original QT message handler.
    ASSERT_TRUE(conHelper.releaseQMessages());
#endif // USING_QT
}

