# This file can be included in to other projects if you
# want to compile the code directly instead of using it as
# an actual static library.

# If we have a "CONFIG+=using_qt" parameter, build with the Qt extensions to the logger.
CONFIG(using_qt) {
    DEFINES *= USING_QT
}

SOURCES += \
        fbatogologger.cpp \
    extensions/loggerextensionbase.cpp

HEADERS += \
        fbatogologger.h \
    extensions/loggerextensionbase.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
