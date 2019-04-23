#ifndef CONSOLEWRITEREXTENSION_H
#define CONSOLEWRITEREXTENSION_H

#include <string>

#include "extensiontemplates/writerextensionbase.h"

namespace fbatogo {

namespace logger {

namespace extension {

class ConsoleWriterExtension : baseclass::WriterExtensionBase
{
public:
    ConsoleWriterExtension();

    // Implement the pure virtual methods for the base class.
    void debug(const std::string &logline);
    void warning(const std::string &logline);
    void info(const std::string &logline);
    void error(const std::string &logline);
};

}

}

}

#endif // CONSOLEWRITEREXTENSION_H
