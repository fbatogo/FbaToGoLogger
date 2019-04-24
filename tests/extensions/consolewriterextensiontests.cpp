#include <gtest/gtest.h>

#include <extensions/consolewriterextension.h>

// Stuff needed to capture the STDOUT.
#include <streambuf>
#include <sstream>
#include <iostream>

using namespace fbatogo::logger::extension;

// XXX Add support for testing when the "using_qt" CONFIG setting is set.

#ifndef USING_QT
TEST(ConsoleWriterExtensionTests, WriteLogsTest)
{
    ConsoleWriterExtension writer;
    std::streambuf *oldCoutStream;
    std::ostringstream strCout;

    // Save the original cout stream.
    oldCoutStream = std::cout.rdbuf();

    // Set the new stream for cout.
    std::cout.rdbuf( strCout.rdbuf() );

    // Write empty strings and check them.
    writer.debug("");
    EXPECT_EQ("\n", strCout.str());

    // Clear the stream.
    strCout.str("");
    strCout.clear();

    writer.error("");
    EXPECT_EQ("\n", strCout.str());

    // Clear the stream.
    strCout.str("");
    strCout.clear();

    writer.info("");
    EXPECT_EQ("\n", strCout.str());

    // Clear the stream.
    strCout.str("");
    strCout.clear();

    writer.warning("");
    EXPECT_EQ("\n", strCout.str());

    // Clear the stream.
    strCout.str("");
    strCout.clear();

    // Write a string with content.
    writer.debug("This is a debug line.");
    EXPECT_EQ("This is a debug line.\n", strCout.str());

    // Clear the stream.
    strCout.str("");
    strCout.clear();

    writer.error("This is an error line.");
    EXPECT_EQ("This is an error line.\n", strCout.str());

    // Clear the stream.
    strCout.str("");
    strCout.clear();

    writer.warning("This is a warning line.");
    EXPECT_EQ("This is a warning line.\n", strCout.str());

    // Clear the stream.
    strCout.str("");
    strCout.clear();

    writer.info("This is an info line.");
    EXPECT_EQ("This is an info line.\n", strCout.str());

    // Restore old cout.
    std::cout.rdbuf(oldCoutStream);
}

#else

TEST(ConsoleWriterExtensionTests, WriteLogsQtTest)
{
    // XXX Implement!
}

#endif // USING_QT
