#include "fbatogologger.h"

#include <limits>

#include "extensions/filewriterextension.h"
#include "extensions/consolewriterextension.h"

using namespace fbatogo;
using namespace logger;

/**
 * @brief FbaToGoLogger::getInstance - Get the singleton instance for the logger.
 *
 * @return FbaToGoLogger pointer.
 */
FbaToGoLogger *FbaToGoLogger::getInstance()
{
    static FbaToGoLogger singleton;

    return &singleton;
}

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
    extension::FileWriterExtension *fileExtension;

    // Create the object.
    fileExtension = new extension::FileWriterExtension();
    if (nullptr == fileExtension) {
        return false;
    }

    if (!fileExtension->setLogFile(path)) {
        error("Failed to open the log file '" + path + "' for writing!  Won't enable writing to a log file!");
        error("    Error reason : " + fileExtension->getOpenErrorString());

        // Clean up.
        delete fileExtension;
        fileExtension = nullptr;

        return false;
    }

    // Then, add our extension to the list of extensions.
    if (!addWriterExtension(fileExtension)) {
        // Clean up the object.
        delete fileExtension;
        fileExtension = nullptr;
        return false;
    }

    return true;
}

/**
 * @brief FbaToGoLogger::logToConsole - Convenience call to easily add a console
 *      writer extension to the write object extensions vector.
 *
 * @return true if the console logger was installed.  false on error.
 */
bool FbaToGoLogger::logToConsole()
{
    extension::ConsoleWriterExtension *consoleExtension;

    consoleExtension = new extension::ConsoleWriterExtension();
    if (nullptr == consoleExtension) {
        return false;
    }

    // Add it.
    if (!addWriterExtension(consoleExtension)) {
        // Clean up the object.
        delete consoleExtension;
        consoleExtension = nullptr;
        return false;
    }

    return true;
}

/**
 * @brief FbaToGoLogger::addModificationExtension - Add a new modification
 *      extension, as long as it doesn't already exist.
 *
 * @param newModifier - The new extension object to add.
 * @param takeOwnership - true if this object should take ownership of the
 *      extension object.  If this is true, then this object will handle
 *      deleting the object when it needs to be destroyed.  If set to false,
 *      the caller will be responsible for deleting the object, but making
 *      sure that it is not in use!
 *
 * @return true if the modification object was added.  false if it wasn't
 *      added because another object already exists with the same name.  If
 *      false is returned, the caller needs to free the object it passed in,
 *      even if \c takeOwnership was set to true!
 */
bool FbaToGoLogger::addModificationExtension(extension::baseclass::ModificationExtensionBase *newModifier, bool takeOwnership)
{
    if (findModificationExtensionExistsByName(newModifier->extensionName()) != std::numeric_limits<size_t>::max()) {
        // Do nothing.
        return false;
    }

    // Otherwise, add it.
    mModificationExtensions.push_back(modificationExtensionContainer(newModifier, takeOwnership));

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
    bool found = false;
    std::vector<modificationExtensionContainer> newVector;

    // Found it, remove it from the vector.
    newVector.clear();

    for (auto & extension : mModificationExtensions) {
        if (extension.first->extensionName() == name) {
            // If we have ownership of it, delete it.
            if (extension.second) {
                delete extension.first;
            }
            found = true;
        } else {
            // Add it to our new vector.
            newVector.push_back(extension);
        }
    }

    if (found) {
        // Update the vector, if it has been modified.
        mModificationExtensions = newVector;
    }

    return found;
}

/**
 * @brief FbaToGoLogger::clearModificationExtensions - Clear all of the modification extensions
 *      that are currently set.
 */
void FbaToGoLogger::clearModificationExtensions()
{
    // Delete all of the objects that are owned by us.
    for (auto & extension : mModificationExtensions) {
        // If we have ownership of this object, delete it.
        if (extension.second) {
            delete extension.first;
        }
    }

    // Then, clear out the vector.
    mModificationExtensions.clear();
}

/**
 * @brief FbaToGoLogger::addWriterExtension - Add a new writer extension,
 *      as long as it doesn't already exist.
 *
 * @param newWriterExtension - The new writer extension object to add.
 * @param takeOwnership - true if this object should take ownership of the
 *      extension object.  If this is true, then this object will handle
 *      deleting the object when it needs to be destroyed.  If set to false,
 *      the caller will be responsible for deleting the object, but making
 *      sure that it is not in use!
 *
 * @return true if the object was added.  false if it was rejected because
 *      an object with the same name is already registered.
 */
bool FbaToGoLogger::addWriterExtension(extension::baseclass::WriterExtensionBase *newWriterExtension, bool takeOwnership)
{
    if (findWriterExtensionExistsByName(newWriterExtension->extensionName()) != std::numeric_limits<size_t>::max()) {
        // Do nothing.
        return false;
    }

    // Add it to our vector.
    mWriterExtensions.push_back(writerExtensionContainer(newWriterExtension, takeOwnership));

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
    bool found = false;
    std::vector<writerExtensionContainer> newVector;

    for (auto & extension : mWriterExtensions) {
        if (extension.first->extensionName() == name) {
            // If we have ownership of it, delete it.
            if (extension.second) {
                delete extension.first;
            }
            found = true;
        } else {
            // Add it to our new vector.
            newVector.push_back(extension);
        }
    }

    if (found) {
        // Update the vector, if it has been modified.
        mWriterExtensions = newVector;
    }

    return true;
}

/**
 * @brief FbaToGoLogger::clearWriterExtensions - Clear all of the writer extensions that
 *      are currently set.
 */
void FbaToGoLogger::clearWriterExtensions()
{
    // Delete all of the objects that are owned by us.
    for (auto & extension : mWriterExtensions) {
        // If we have ownership of this object, delete it.
        if (extension.second) {
            delete extension.first;
        }
    }

    // Then, clear out the vector.
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
        extension.first->debug(toWrite);
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
        extension.first->warning(toWrite);
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
        extension.first->info(toWrite);
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
        extension.first->error(toWrite);
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
        if (mModificationExtensions.at(i).first->extensionName() == name) {
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
        if (mWriterExtensions.at(i).first->extensionName() == name) {
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
        modifying = modifier.first->parseLogLine(modifying);
    }

    return modifying;
}
