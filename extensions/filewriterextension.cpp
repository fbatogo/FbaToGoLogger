#include "filewriterextension.h"

#include <errno.h>
#include <string.h>

using namespace fbatogo::logger::extension;

FileWriterExtension::FileWriterExtension() :
    WriterExtensionBase("FileWriter")
{
    mFileHandle = nullptr;
    mErrorCode = 0;
}

/**
 * @brief FileWriterExtension::setLogFile - Create a new log file at the path and
 *      file name provided.   If a log file is already open, it will be flushed and
 *      closed.
 *
 * @param path - The path and file name of the log file that we want to write to using
 *      this object.
 *
 * @return true if the file was opened and is ready to be written to.  false on error.
 */
bool FileWriterExtension::setLogFile(const std::string &path)
{
    // If we have a log file already open, close it.
    if (nullptr != mFileHandle) {
        // Flush any data, and close the file.
        fflush(mFileHandle);

        fclose(mFileHandle);
        mFileHandle = nullptr;
    }

    mFilePath = path;

    // Open the log file that we want to write to.
    mFileHandle = fopen(path.c_str(), "w+");
    if (nullptr == mFileHandle) {
        // Store the error code for the failure.
        mErrorCode = errno;
        return false;
    }

    // Success!
    mErrorCode = 0;

    return true;
}

/**
 * @brief FileWriterExtension::getOpenErrorCode - Return the error code that indicates
 *      the success/failure of our last attempt to open the log file to be written.
 *
 * @return int containing the value of \c errno at the point that we attempted to open
 *      the log file to write to.   If the log file has not been opened yet, or if the
 *      log file opened properly, this value will be 0.
 */
int FileWriterExtension::getOpenErrorCode()
{
    return mErrorCode;
}

/**
 * @brief FileWriterExtension::getOpenErrorString - Return the string that indicates
 *      the success/failure of the attempt to open the log file.  (This basically
 *      takes the error code, and runs it through strerror().)
 *
 * @return std::string describing the success/failure of our attempt to open a log
 *      file to write to.
 */
std::string FileWriterExtension::getOpenErrorString()
{
    return std::string(strerror(mErrorCode));
}

/**
 * @brief FileWriterExtension::getFilePath - Return the path and file name of the log
 *      file that we are currently writing to.
 *
 * @return std::string containing the file name and path to the log file we are writing
 *      to.
 */
std::string FileWriterExtension::getFilePath()
{
    return mFilePath;
}

/**
 * @brief FileWriterExtension::debug - Write a debug log line to the log file.
 *
 * @param logline - The debug log line to write to the log file.
 */
void FileWriterExtension::debug(const std::string &logline)
{
    writeLogLineToFile(logline);
}

/**
 * @brief FileWriterExtension::warning - Write a warning log line to the log file.
 *
 * @param logline - The warning log line to write to the log file.
 */
void FileWriterExtension::warning(const std::string &logline)
{
    writeLogLineToFile(logline);
}

/**
 * @brief FileWriterExtension::info - Write an info level log line to the log file.
 *
 * @param logline - The info log line to write to the log file.
 */
void FileWriterExtension::info(const std::string &logline)
{
    writeLogLineToFile(logline);
}

/**
 * @brief FileWriterExtension::error - Write an error level log line to the log file.
 *
 * @param logline - The error log line to write to the log file.
 */
void FileWriterExtension::error(const std::string &logline)
{
    writeLogLineToFile(logline);
}

/**
 * @brief FileWriterExtension::writeLogLineToFile - Actually write the log line to the
 *      log file, assuming a log file is open.   If a log file is NOT open, the log
 *      line is discarded.
 *
 * @param logline - The log line to write to the log file.
 */
void FileWriterExtension::writeLogLineToFile(const std::string &logline)
{
    if (nullptr != mFileHandle) {
        fprintf(mFileHandle, "%s\n", logline.c_str());
    }
}
