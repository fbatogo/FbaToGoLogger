#include "modificationextensionbase.h"

using namespace fbatogo::logger::extension::baseclass;

ModificationExtensionBase::ModificationExtensionBase(const std::string &extensionName) :
    LoggerExtensionBase(extensionName, LOGGER_EXTENSION_TYPE_MODIFIER)
{

}

