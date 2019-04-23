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
    void logToConsole(bool shouldLogToConsole);

    void addModificationExtension(const extension::baseclass::ModificationExtensionBase &newModifier);
    void addWriterExtension(const extension::baseclass::WriterExtensionBase &newWriterExtension);

    void debug(const std::string &logline);
    void warning(const std::string &logline);
    void info(const std::string &logline);
    void error(const std::string &logline);

#ifdef USING_QT
    void logToFile(const QString &path);

    void debug(const QString &logline);
    void warning(const QString &logline);
    void info(const QString &logline);
    void error(const QString &logline);
#endif // USING_QT

private:
    FbaToGoLogger();

    std::string modifyLine(const std::string &logline);

    bool mWriteToConsole;
    std::vector<extension::baseclass::ModificationExtensionBase> mModificationExtensions;
    std::vector<extension::baseclass::WriterExtensionBase> mWriterExtensions;

};

}

}

#endif // FBATOGOLOGGER_H
