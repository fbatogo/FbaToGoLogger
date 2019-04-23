#include "consolewriterextension.h"

#ifdef USING_QT
#include <QDebug>
#else
#include <iostream>
#endif // USING_QT

using namespace fbatogo::logger::extension;

ConsoleWriterExtension::ConsoleWriterExtension() :
    WriterExtensionBase("ConsoleWriter")
{

}

/**
 * @brief ConsoleWriterExtension::debug - Write a debug level log line to the console.
 *
 * @param logline - The log line to write to the console.
 */
void ConsoleWriterExtension::debug(const std::string &logline)
{
#ifndef USING_QT
    std::cout << logline << std::endl;
#else
    qDebug("%s", logline.c_str());
#endif // USING_QT
}

/**
 * @brief ConsoleWriterExtension::warning - Write a warning level log line to the
 *      console.
 *
 * @param logline - The log line to write to the console.
 */
void ConsoleWriterExtension::warning(const std::string &logline)
{
#ifndef USING_QT
    std::cout << logline << std::endl;
#else
    qWarning("%s", logline.c_str());
#endif // USING_QT
}

/**
 * @brief ConsoleWriterExtension::info - Write an info level log line to the console.
 *
 * @param logline - The log line to write to the console.
 */
void ConsoleWriterExtension::info(const std::string &logline)
{
#ifndef USING_QT
    std::cout << logline << std::endl;
#else
    qInfo("%s", logline.c_str());
#endif // USING_QT
}

/**
 * @brief ConsoleWriterExtension::error - Write an error level log line to the console.
 *
 * @param logline - The log line to write to the console.
 */
void ConsoleWriterExtension::error(const std::string &logline)
{
#ifndef USING_QT
    std::cout << logline << std::endl;
#else
    qCritical("%s", logline.c_str());
#endif // USING_QT
}
