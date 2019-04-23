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
    void logToConsole();

    bool addModificationExtension(const extension::baseclass::ModificationExtensionBase &newModifier);
    bool removeModificationExtensionByName(const std::string &name);
    void clearModificationExtensions();

    bool addWriterExtension(const extension::baseclass::WriterExtensionBase &newWriterExtension);
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

    std::vector<extension::baseclass::ModificationExtensionBase> mModificationExtensions;
    std::vector<extension::baseclass::WriterExtensionBase> mWriterExtensions;

    // The tags we use for each log level.
    std::string mDebugTag;
    std::string mWarningTag;
    std::string mInfoTag;
    std::string mErrorTag;
};

}

}

#endif // FBATOGOLOGGER_H
