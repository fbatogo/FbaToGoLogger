#include "loggerextensionbase.h"

using namespace fbatogo;
using namespace logger;
using namespace extension;

LoggerExtensionBase::LoggerExtensionBase(const std::string &extensionName, int extensionType)
{
    mExtensionName = extensionName;
    mExtensionType = extensionType;
}

#ifdef USING_QT
LoggerExtensionBase::LoggerExtensionBase(const QString &extensioName, int extensionType)
{
    mExtensionName = extensionName.toStdString();
    mExtensionType = extensionType;
}
#endif // USING_QT

std::string LoggerExtensionBase::extensionName()
{
    return mExtensionName;
}

#ifdef USING_QT
QString LoggerExtensionBase::qstringExtensionName()
{
    return QString::fromStdString(mExtensionName);
}
#endif // USING_QT

int LoggerExtensionBase::extensionType()
{
    return mExtensionType;
}
