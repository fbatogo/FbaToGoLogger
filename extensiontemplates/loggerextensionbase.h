#ifndef LOGGEREXTENSION_H
#define LOGGEREXTENSION_H

#include <string>

#ifdef USING_QT
#include <QString>
#endif // USING_QT

// Define our extension types.
#define LOGGER_EXTENSION_TYPE_WRITER        1
#define LOGGER_EXTENSION_TYPE_MODIFIER      2

namespace fbatogo {

namespace logger {

namespace extension {

namespace baseclass {

class LoggerExtensionBase
{
public:
    LoggerExtensionBase(const std::string &extensionName, int extensionType);

#ifdef USING_QT
    LoggerExtensionBase(const QString &qextensionName, int extensionType);
#endif // USING_QT

    virtual ~LoggerExtensionBase() = default;

    std::string extensionName();

#ifdef USING_QT
    QString qstringExtensionName();
#endif // USING_QT

    int extensionType();

private:
    std::string mExtensionName;
    int mExtensionType;
};

}

}

}

}

#endif // LOGGEREXTENSION_H
