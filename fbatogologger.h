#ifndef FBATOGOLOGGER_H
#define FBATOGOLOGGER_H

#ifdef USING_QT
#include <QString>
#else
#include <string>
#endif // USING_QT

#include <vector>

#include "extensiontemplates/modificationextensionbase.h"
#include "extensiontemplates/writerextensionbase.h"

namespace fbatogo {

namespace logger {

typedef std::pair<extension::baseclass::ModificationExtensionBase *, bool> modificationExtensionContainer;
typedef std::pair<extension::baseclass::WriterExtensionBase *, bool> writerExtensionContainer;

/**
 * @brief The FbaToGoLogger class is the main class that should be used for all logging
 *      operations.  It allows management of any extensions that might be configured
 *      along with some convenience handlers to quickly configure some common logging
 *      methods.
 */
class FbaToGoLogger
{
    static FbaToGoLogger *getInstance();

    bool logToFile(const std::string &path);
    bool logToConsole();

    bool addModificationExtension(extension::baseclass::ModificationExtensionBase *newModifier, bool takeOwnership = true);
    bool removeModificationExtensionByName(const std::string &name);
    void clearModificationExtensions();

    bool addWriterExtension(extension::baseclass::WriterExtensionBase *newWriterExtension, bool takeOwnership = true);
    bool removeWriterExtensionByName(const std::string &name);
    void clearWriterExtensions();

    void setLogLevelTags(const std::string &debugTag, const std::string &warningTag, const std::string &infoTag, const std::string &errorTag);

    void debug(const std::string &logline);
    void warning(const std::string &logline);
    void info(const std::string &logline);
    void error(const std::string &logline);

#ifdef USING_QT
    bool logToFile(const QString &path);

    void debug(const QString &logline);
    void warning(const QString &logline);
    void info(const QString &logline);
    void error(const QString &logline);
#endif // USING_QT

protected:
    size_t findModificationExtensionExistsByName(const std::string &name);
    size_t findWriterExtensionExistsByName(const std::string &name);

private:
    FbaToGoLogger();

    std::string modifyLine(const std::string &logline);

    // The bool in the 2nd position indicates if we have taken ownership of the object.
    std::vector<modificationExtensionContainer> mModificationExtensions;
    std::vector<writerExtensionContainer> mWriterExtensions;

    // The tags we use for each log level.
    std::string mDebugTag;
    std::string mWarningTag;
    std::string mInfoTag;
    std::string mErrorTag;
};

}

}

#endif // FBATOGOLOGGER_H
