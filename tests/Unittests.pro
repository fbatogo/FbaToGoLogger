QT       -= gui

TARGET = FbaToGoLogger-Unittests
TEMPLATE = app

linux {
  QMAKE_CFLAGS *= -ftest-coverage -fprofile-arcs
  QMAKE_CXXFLAGS *= -ftest-coverage -fprofile-arcs
  QMAKE_LFLAGS *= -ftest-coverage -fprofile-arcs
  }

# If we are told to use the address sanitizer.
asan {
    QMAKE_CFLAGS *= -fsanitize=address #-fsanitize-address-use-after-scope
    QMAKE_LFLAGS *= -fsanitize=address
}

  
# Include the files that we will be testing.
include(../fbatogologger.pri)

# Set up everything to use Google Test.
INCLUDEPATH += gtest/googletest/include
INCLUDEPATH += gtest/googletest             # Include the base path so that when we include gtest-all.cc it can find everything.

# Set the path to our test helpers.
INCLUDEPATH *= $$PWD/helpers

linux {
    LIBS *= -pthread
}

SOURCES += $$PWD/gtest/googletest/src/gtest-all.cc \
    fbatogologgertests.cpp \
    helpers/consolehelpers.cpp \
    main.cpp \
    extensions/consolewriterextensiontests.cpp

HEADERS += \
    helpers/consolehelpers.h

