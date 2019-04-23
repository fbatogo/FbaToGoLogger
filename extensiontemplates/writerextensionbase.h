#ifndef WRITEREXTENSIONBASE_H
#define WRITEREXTENSIONBASE_H

#include "loggerextensionbase.h"

namespace fbatogo {

namespace logger {

namespace extension {

namespace baseclass {

class WriterExtensionBase : public LoggerExtensionBase
{
public:
    WriterExtensionBase(const std::string &extensionName);

    virtual void debug(const std::string &logline) = 0;
    virtual void warning(const std::string &logline) = 0;
    virtual void info(const std::string &logline) = 0;
    virtual void error(const std::string &logline) = 0;
};

}

}

}

}

#endif // WRITEREXTENSIONBASE_H
