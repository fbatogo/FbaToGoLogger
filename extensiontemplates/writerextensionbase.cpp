#include "writerextensionbase.h"

using namespace fbatogo::logger::extension::baseclass;

WriterExtensionBase::WriterExtensionBase(const std::string &extensionName) :
    LoggerExtensionBase(extensionName, LOGGER_EXTENSION_TYPE_WRITER)
{

}
