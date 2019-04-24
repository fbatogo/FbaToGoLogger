#ifndef MODIFICATIONEXTENSIONBASE_H
#define MODIFICATIONEXTENSIONBASE_H

#include "loggerextensionbase.h"

namespace fbatogo {

namespace logger {

namespace extension {

namespace baseclass {

class ModificationExtensionBase : public LoggerExtensionBase
{
public:
    ModificationExtensionBase(const std::string &extensionName);

    virtual std::string parseLogLine(const std::string &logLine) = 0;
};

}

}

}

}

#endif // MODIFICATIONEXTENSIONBASE_H
