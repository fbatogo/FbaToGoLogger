#include "fbatogologger.h"

#include "extensions/filewriterextension.h"

using namespace fbatogo;
using namespace logger;

/**
 * @brief FbaToGoLogger::logToFile - Convenience call to easily add a file writer
 *      extension to the writer object extensions vector.   The log file will be
 *      written to the path provided.
 *
 * @param path - The path and file name to write the log file to.
 *
 * @return true if the logger is now set up to write log lines to the log file.  false
 *      otherwise.
 */
bool FbaToGoLogger::logToFile(const std::string &path)
{
    extension::FileWriterExtension fileExtension;

    if (!fileExtension.setLogFile(path)) {
        error("Failed to open the log file '" + path + "' for writing!  Won't enable writing to a log file!");
        error("    Error reason : " + fileExtension.getOpenErrorString());
        return false;
    }
}

void FbaToGoLogger::logToConsole(bool shouldLogToConsole)
{

}

void FbaToGoLogger::addModificationExtension(const extension::baseclass::ModificationExtensionBase &newModifier)
{

}

void FbaToGoLogger::addWriterExtension(const extension::baseclass::WriterExtensionBase &newWriterExtension)
{

}

void FbaToGoLogger::debug(const std::string &logline)
{

}

void FbaToGoLogger::warning(const std::string &logline)
{

}

void FbaToGoLogger::info(const std::string &logline)
{

}

void FbaToGoLogger::error(const std::string &logline)
{

}

#ifdef USING_QT
void FbaToGoLogger::logToFile(const QString &path)
{

}

void FbaToGoLogger::debug(const QString &logline)
{

}

void FbaToGoLogger::warning(const QString &logline)
{

}

void FbaToGoLogger::info(const QString &logline)
{

}

void FbaToGoLogger::error(const QString &logline)
{

}
#endif // USING_QT

FbaToGoLogger::FbaToGoLogger()
{
}

/**
 * @brief FbaToGoLogger::modifyLine - Run the log line through any modification
 *      extensions that might be registered.
 *
 * @param logline - The log line to run through any modification extensions.
 *
 * @return std::string containing \c logline , modified by any modification extensions
 *      that might be installed.  If no modification extensions are installed, the
 *      original log line is returned.
 */
std::string FbaToGoLogger::modifyLine(const std::string &logline)
{
    std::string modifying = logline;

    for (auto & modifier : mModificationExtensions) {
        modifying = modifier.parseLogLine(modifying);
    }

    return modifying;
}
