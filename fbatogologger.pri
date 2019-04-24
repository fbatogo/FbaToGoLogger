# This file can be included in to other projects if you
# want to compile the code directly instead of using it as
# an actual static library.

# If we have a "CONFIG+=using_qt" parameter, build with the Qt extensions to the logger.
CONFIG(using_qt) {
    DEFINES *= USING_QT
}

# Include the current path in our include path.
INCLUDEPATH += $$PWD

SOURCES += \
    $$PWD/fbatogologger.cpp \
    $$PWD/extensiontemplates/loggerextensionbase.cpp \
    $$PWD/extensiontemplates/modificationextensionbase.cpp \
    $$PWD/extensiontemplates/writerextensionbase.cpp \
    $$PWD/extensions/filewriterextension.cpp \
    $$PWD/extensions/consolewriterextension.cpp

HEADERS += \
    $$PWD/fbatogologger.h \
    $$PWD/extensiontemplates/loggerextensionbase.h \
    $$PWD/extensiontemplates/modificationextensionbase.h \
    $$PWD/extensiontemplates/writerextensionbase.h \
    $$PWD/extensions/filewriterextension.h \
    $$PWD/extensions/consolewriterextension.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
