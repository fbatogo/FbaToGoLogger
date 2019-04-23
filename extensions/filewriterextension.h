#ifndef FILEWRITEREXTENSION_H
#define FILEWRITEREXTENSION_H

#include <string>

#include "extensiontemplates/writerextensionbase.h"

namespace fbatogo {

namespace logger {

namespace extension {

/**
 * @brief The FileWriterExtension class implements a writer extension that handles
 *      writing log lines to a file on a file system.
 */
class FileWriterExtension : public baseclass::WriterExtensionBase
{
public:
    FileWriterExtension();

    bool setLogFile(const std::string &path);
    int getOpenErrorCode();
    std::string getOpenErrorString();

    // Implement the pure virtual methods for the base class.
    void debug(const std::string &logline);
    void warning(const std::string &logline);
    void info(const std::string &logline);
    void error(const std::string &logline);

private:
    void writeLogLineToFile(const std::string logline);

    FILE *mFileHandle;
    int mErrorCode;
};

}

}

}

#endif // FILEWRITEREXTENSION_H
