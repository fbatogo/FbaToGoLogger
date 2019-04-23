#include "fbatogologger.h"

#include <limits>

#include "extensions/filewriterextension.h"
#include "extensions/consolewriterextension.h"

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

    // Then, add our extension to the list of extensions.
    addWriterExtension(fileExtension);

    return true;
}

/**
 * @brief FbaToGoLogger::logToConsole - Convenience call to easily add a console
 *      writer extension to the write object extensions vector.
 */
void FbaToGoLogger::logToConsole()
{
    extension::ConsoleWriterExtension consoleExtension;

    // Add it.
    addWriterExtension(consoleExtension);
}

/**
 * @brief FbaToGoLogger::addModificationExtension - Add a new modification
 *      extension, as long as it doesn't already exist.
 *
 * @param newModifier - The new extension object to add.
 *
 * @return true if the modification object was added.  false if it wasn't
 *      added because another object already exists with the same name.
 */
bool FbaToGoLogger::addModificationExtension(const extension::baseclass::ModificationExtensionBase &newModifier)
{
    if (findModificationExtensionExistsByName(newModifier.extensionName()) != std::numeric_limits<size_t>::max()) {
        // Do nothing.
        return false;
    }

    // Otherwise, add it.
    mModificationExtensions.push_back(newModifier);

    return true;
}

/**
 * @brief FbaToGoLogger::removeModificationExtensionByName - Locate a modification extension
 *      based on its name, and remove it.
 *
 * @param name - The name of the modification extension to remove.
 *
 * @return true if the modification extension was found and removed.  false if it wasn't.
 */
bool FbaToGoLogger::removeModificationExtensionByName(const std::string &name)
{
    size_t index;
    std::vector<extension::baseclass::ModificationExtensionBase> newVector;

    index = findModificationExtensionExistsByName(name);
    if (index == std::numeric_limits<size_t>::max()) {
        // Didn't find it.
        return false;
    }

    // Found it, remove it from the vector.
    newVector.clear();

    for (size_t i = 0; i < mModificationExtensions.size(); i++) {
        if (i != index) {
            newVector.push_back(mModificationExtensions.at(i));
        }
    }

    // Update the vector.
    mModificationExtensions = newVector;

    return true;
}

/**
 * @brief FbaToGoLogger::clearModificationExtensions - Clear all of the modification extensions
 *      that are currently set.
 */
void FbaToGoLogger::clearModificationExtensions()
{
    mModificationExtensions.clear();
}

/**
 * @brief FbaToGoLogger::addWriterExtension - Add a new writer extension,
 *      as long as it doesn't already exist.
 *
 * @param newWriterExtension - The new writer extension object to add.
 *
 * @return true if the object was added.  false if it was rejected because
 *      an object with the same name is already registered.
 */
bool FbaToGoLogger::addWriterExtension(const extension::baseclass::WriterExtensionBase &newWriterExtension)
{
    if (findWriterExtensionExistsByName(newWriterExtension.extensionName()) != std::numeric_limits<size_t>::max()) {
        // Do nothing.
        return false;
    }

    // Add it to our vector.
    mWriterExtensions.push_back(newWriterExtension);

    return true;
}

/**
 * @brief FbaToGoLogger::removeWriterExtensionByName - Remove a writer extension based on the
 *      name of the extension.
 *
 * @param name - The name of the writer extension to remove.
 *
 * @return true if the writer extension was removed.  false on error.
 */
bool FbaToGoLogger::removeWriterExtensionByName(const std::string &name)
{
    size_t index;
    std::vector<extension::baseclass::WriterExtensionBase> newVector;

    index = findWriterExtensionExistsByName(name);
    if (index == std::numeric_limits<size_t>::max()) {
        // Didn't find it.
        return false;
    }

    // Found it, remove it from the vector.
    newVector.clear();

    for (size_t i = 0; i < mWriterExtensions.size(); i++) {
        if (i != index) {
            newVector.push_back(mWriterExtensions.at(i));
        }
    }

    // Update the vector.
    mWriterExtensions = newVector;

    return true;
}

/**
 * @brief FbaToGoLogger::clearWriterExtensions - Clear all of the writer extensions that
 *      are currently set.
 */
void FbaToGoLogger::clearWriterExtensions()
{
    mWriterExtensions.clear();
}

/**
 * @brief FbaToGoLogger::setLogLevelTags - Set the new tags that should be used when writing a
 *      log line at a specified level.
 *
 * @param debugTag - The new debug log level tag to use.
 * @param warningTag - The new warning log level tag to use.
 * @param infoTag - The new info log level tag to use.
 * @param errorTag - The new error log level tag to use.
 */
void FbaToGoLogger::setLogLevelTags(const std::string &debugTag, const std::string &warningTag, const std::string &infoTag, const std::string &errorTag)
{
    mDebugTag = debugTag;
    mWarningTag = warningTag;
    mInfoTag = infoTag;
    mErrorTag = errorTag;
}

/**
 * @brief FbaToGoLogger::debug - Write a line to the log at debug level.
 *
 * @param logline - The line to write to the log at debug level.
 */
void FbaToGoLogger::debug(const std::string &logline)
{
    std::string toWrite;

    // Modify the line, if needed.
    toWrite = modifyLine(logline);

    if (!mDebugTag.empty()) {
        toWrite = mDebugTag + logline;
    }

    // Iterate all of our writers, and write the log line to each one.
    for (auto & extension : mWriterExtensions) {
        extension.debug(toWrite);
    }
}

/**
 * @brief FbaToGoLogger::warning - Write a line to the log at warning level.
 *
 * @param logline - The line to write to the log at warning level.
 */
void FbaToGoLogger::warning(const std::string &logline)
{
    std::string toWrite;

    // Modify the line, if needed.
    toWrite = modifyLine(logline);

    if (!mWarningTag.empty()) {
        toWrite = mWarningTag + logline;
    }

    // Iterate all of our writers, and write the log line to each one.
    for (auto & extension : mWriterExtensions) {
        extension.warning(toWrite);
    }
}

/**
 * @brief FbaToGoLogger::info - Write a line to the log at info level.
 *
 * @param logline - The line to write to the log at info level.
 */
void FbaToGoLogger::info(const std::string &logline)
{
    std::string toWrite;

    // Modify the line, if needed.
    toWrite = modifyLine(logline);

    if (!mInfoTag.empty()) {
        toWrite = mInfoTag + logline;
    }

    // Iterate all of our writers, and write the log line to each one.
    for (auto & extension : mWriterExtensions) {
        extension.info(toWrite);
    }
}

/**
 * @brief FbaToGoLogger::error - Write a line to the log at error level.
 *
 * @param logline - The line to write to the log at error level.
 */
void FbaToGoLogger::error(const std::string &logline)
{
    std::string toWrite;

    // Modify the line, if needed.
    toWrite = modifyLine(logline);

    if (!mErrorTag.empty()) {
        toWrite = mErrorTag + logline;
    }

    // Iterate all of our writers, and write the log line to each one.
    for (auto & extension : mWriterExtensions) {
        extension.error(toWrite);
    }
}

#ifdef USING_QT
/**
 * @brief FbaToGoLogger::logToFile - A QString overloaded version of the
 *      logToFile() method used with a standard string.
 *
 * @param path - The path and file name to write log data to.
 *
 * @return true if the log filew as opened and data will be written to it.
 *      false on error.
 */
bool FbaToGoLogger::logToFile(const QString &path)
{
    return logToFile(path.toStdString());
}

/**
 * @brief FbaToGoLogger::debug - A QString overloaded version of the
 *      debug() method used with a standard string.
 *
 * @param logline - The log line to write at debug level.
 */
void FbaToGoLogger::debug(const QString &logline)
{
    debug(logline.toStdString());
}

/**
 * @brief FbaToGoLogger::warning - A QString overloaded version of the
 *      warning() method used with a standard string.
 *
 * @param logline - The log line to write at warning level.
 */
void FbaToGoLogger::warning(const QString &logline)
{
    warning(logline.toStdString());
}

/**
 * @brief FbaToGoLogger::info - A QString overloaded version of the
 *      info() method used with a standard string.
 *
 * @param logline - The log line to write at info level.
 */
void FbaToGoLogger::info(const QString &logline)
{
    info(logline.toStdString());
}

/**
 * @brief FbaToGoLogger::error - A QString overloaded version of the
 *      error() method used with a standard string.
 *
 * @param logline - The log line to write at error level.
 */
void FbaToGoLogger::error(const QString &logline)
{
    error(logline.toStdString());
}
#endif // USING_QT

/**
 * @brief FbaToGoLogger::findModificationExtensionExistsByName - Look at
 *      the registered modification extensions, and see if one is registered
 *      using the name provided.
 *
 * @param name - The name of the object that we want to search for.
 *
 * @return size_t containing the index of the object with the specified name.
 *      If no matching object is found, std::numeric_limits<size_t>::max()
 *      is returned.
 */
size_t FbaToGoLogger::findModificationExtensionExistsByName(const std::string &name)
{
    for (size_t i = 0; i < mModificationExtensions.size(); i++) {
        if (mModificationExtensions.at(i).extensionName() == name) {
            return i;
        }
    }

    return std::numeric_limits<size_t>::max();
}

/**
 * @brief FbaToGoLogger::findWriterExtensionExistsByName - Look at
 *      the registered writer extensions, and see if one is registered
 *      using the name provided.
 *
 * @param name - The name of the object that we want to search for.
 *
 * @return size_t containing the index of the object with the specified name.
 *      If no matching object is found, std::numeric_limits<size_t>::max()
 *      is returned.
 */
size_t FbaToGoLogger::findWriterExtensionExistsByName(const std::string &name)
{
    for (size_t i = 0; i < mWriterExtensions.size(); i++) {
        if (mWriterExtensions.at(i).extensionName() == name) {
            return i;
        }
    }

    return std::numeric_limits<size_t>::max();
}

FbaToGoLogger::FbaToGoLogger()
{
    // Set the default values for logging tags.
    mDebugTag = "[DEBUG] ";
    mWarningTag = "<WARNING> ";
    mInfoTag.clear();
    mErrorTag = "!!ERROR!! ";

    // Start clean.
    mModificationExtensions.clear();
    mWriterExtensions.clear();
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
