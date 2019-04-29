#include "consolehelpers.h"

#include <iostream>

#ifdef USING_QT
#include <QDebug>
#endif  // USING_QT

ConsoleHelpers::ConsoleHelpers()
{
    mOldStdErrStream = nullptr;
    mOldStdOutStream = nullptr;


}

/**
 * @brief ConsoleHelpers::captureStdOut - Capture STDOUT, and redirect it to our mStdOutStream.
 *
 * @return true if STDOUT was captured.  false on error.
 */
bool ConsoleHelpers::captureStdOut()
{
    // Store the currently install STDOUT stream handler.
    mOldStdOutStream = std::cout.rdbuf();

    // Point STDOUT to our ostringstream.
    std::cout.rdbuf(mStdOutStream.rdbuf());

    return true;
}

/**
 * @brief ConsoleHelpers::captureStdErr - Capture STDERR, and redirect it to our mStdErrStream.
 *
 * @return true if STDERR was captured.  false on error.
 */
bool ConsoleHelpers::captureStdErr()
{
    // Store the currently install STDERR stream handler.
    mOldStdErrStream = std::cerr.rdbuf();

    // Point STDERR to our ostringstream.
    std::cerr.rdbuf(mStdErrStream.rdbuf());

    return true;
}

/**
 * @brief ConsoleHelpers::clearStdOutBuffer - Clear any data in our internal STDOUT stream buffer.
 */
void ConsoleHelpers::clearStdOutBuffer()
{
    mStdOutStream.clear();
    mStdOutStream.str("");
}

/**
 * @brief ConsoleHelpers::clearStdErrBuffer - Clear any data in our internal STDERR stream buffer.
 */
void ConsoleHelpers::clearStdErrBuffer()
{
    mStdErrStream.clear();
    mStdErrStream.str("");
}

/**
 * @brief ConsoleHelpers::stdOut - Return everything read from STDOUT since the last call to
 *      stdOut().
 *
 * @return std::string containing everything read from STDOUT since the last call to this
 *      method.
 */
std::string ConsoleHelpers::stdOut()
{
    std::string result;

    // Get the data from the stream.
    result = mStdOutStream.str();

    // Clear the stream.
    clearStdOutBuffer();;

    // Return the data.
    return result;
}

/**
 * @brief ConsoleHelpers::stdErr - Return everything read from STDERR since the last call to
 *      stdErr().
 *
 * @return std::string containing everything read from STDERR since the last call to this
 *      method.
 */
std::string ConsoleHelpers::stdErr()
{
    std::string result;

    // Get the data from the stream.
    result = mStdErrStream.str();

    // Clear the stream.
    clearStdErrBuffer();;

    // Return the data.
    return result;
}

/**
 * @brief ConsoleHelpers::releaseStdOut - Change STDOUT to go back to how it was before we
 *      captured it.
 *
 * @return true if STDOUT was released.  false if STDOUT was NOT released.
 */
bool ConsoleHelpers::releaseStdOut()
{
    // Set STDOUT back to the original stream.
    std::cout.rdbuf(mOldStdOutStream);

    // Get rid of the pointer to the old stream.
    mOldStdOutStream = nullptr;

    return true;
}

/**
 * @brief ConsoleHelpers::releaseStdErr - Change STDERR to go back to how it was before we
 *      captured it.
 *
 * @return true if STDERR was released.  false if STDERR was NOT released.
 */
bool ConsoleHelpers::releaseStdErr()
{
    // Set STDERR back to the original stream.
    std::cout.rdbuf(mOldStdErrStream);

    // Get rid of the pointer to the old stream.
    mOldStdErrStream = nullptr;

    return true;
}

#ifdef USING_QT
// A message handler to convert the qDebug/qWarning/qInfo/qCritical message to be output
// over STDOUT.
void myMessageOutput(QtMsgType, const QMessageLogContext &, const QString &msg)
{
    std::cout << msg.toStdString() << std::endl;
}

/**
 * @brief ConsoleHelpers::captureQMessages - Redirect all qMessages to STDOUT so they can be
 *      captured using the code above.
 *
 * @return true if qMessages were redirected to STDOUT.  false on error.
 */
bool ConsoleHelpers::captureQMessages()
{
    qInstallMessageHandler(myMessageOutput);

    return true;
}

/**
 * @brief ConsoleHelpers::releaseQMessages - Disable the redirection of qMessages to STDOUT.
 *
 * @return true if qMessages are no longer redirected to STDOUT.  false on error.
 */
bool ConsoleHelpers::releaseQMessages()
{
    qInstallMessageHandler(nullptr);

    return true;
}
#endif // USING_QT
