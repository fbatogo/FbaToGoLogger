#ifndef CONSOLEHELPERS_H
#define CONSOLEHELPERS_H

#include <streambuf>
#include <sstream>

class ConsoleHelpers
{
public:
    ConsoleHelpers();

    bool captureStdOut();
    bool captureStdErr();

    void clearStdOutBuffer();
    void clearStdErrBuffer();

    std::string stdOut();
    std::string stdErr();

    bool releaseStdOut();
    bool releaseStdErr();

#ifdef USING_QT
    bool captureQMessages();
    bool releaseQMessages();
#endif // USING_QT

private:
    std::streambuf *mOldStdOutStream;
    std::streambuf *mOldStdErrStream;

    std::ostringstream mStdOutStream;
    std::ostringstream mStdErrStream;
};

#endif // CONSOLEHELPERS_H
