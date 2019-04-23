# This file can be included in to other projects if you
# want to compile the code directly instead of using it as
# an actual static library.

# If we have a "CONFIG+=using_qt" parameter, build with the Qt extensions to the logger.
CONFIG(using_qt) {
    DEFINES *= USING_QT
}

SOURCES += \
        fbatogologger.cpp \
    $$PWD/extensiontemplates/loggerextensionbase.cpp \
    $$PWD/extensiontemplates/modificationextensionbase.cpp \
    $$PWD/extensiontemplates/writerextensionbase.cpp \
    $$PWD/extensions/filewriterextension.cpp \
    $$PWD/extensions/consolewriterextension.cpp

HEADERS += \
        fbatogologger.h \
    $$PWD/extensiontemplates/loggerextensionbase.h \
    $$PWD/extensiontemplates/modificationextensionbase.h \
    $$PWD/extensiontemplates/writerextensionbase.cpp.autosave \
    $$PWD/extensiontemplates/writerextensionbase.h \
    $$PWD/extensions/filewriterextension.h \
    $$PWD/extensions/consolewriterextension.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
