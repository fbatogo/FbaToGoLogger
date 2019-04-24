QT       -= gui

TARGET = FbaToGoLogger-Unittests
TEMPLATE = app
  
# Include the files that we will be testing.
include(../fbatogologger.pri)

# Set up everything to use Google Test.
INCLUDEPATH += gtest/googletest/include
INCLUDEPATH += gtest/googletest             # Include the base path so that when we include gtest-all.cc it can find everything.
SOURCES += $$PWD/gtest/googletest/src/gtest-all.cc

linux {
    LIBS *= -pthread
}

SOURCES += \
    main.cpp \
    extensions/consolewriterextensiontests.cpp

