#ifndef FBATOGOLOGGER_H
#define FBATOGOLOGGER_H

#include <QString>

namespace fbatogo {

namespace logger {

class FbaToGoLogger
{
    static FbaToGoLogger *getInstance();

    void debug(const std::string &logline);
    void debug(const QString &logline);

    void warning(const std::string &logline);
    void warning(const QString &logline);

    void info(const std::string &logline);
    void info(const QString &logline);

    void error(const std::string &logline);
    void error(const QString &logline);

private:
    FbaToGoLogger();


};

}

}

#endif // FBATOGOLOGGER_H
