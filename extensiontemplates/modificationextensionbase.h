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

    std::string parseLogLine(const std::string &logLine);
};

}

}

}

}

#endif // MODIFICATIONEXTENSIONBASE_H
