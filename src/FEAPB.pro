#-------------------------------------------------
#
# Project created by QtCreator 2013-10-11T06:15:32
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FEAPB
TEMPLATE = app
CONFIG   += c++11


SOURCES += main.cpp\
        mainwindow.cpp \
    QCustomPlot/qcustomplot.cpp \
    ElementMatrix.cpp \
    DirichletBoundaryConditions.cpp \
    DefineProblem.cpp \
    Assembly.cpp \
    TimeIntegration.cpp \
    ReadDataFile.cpp \
    PiezoAreaMoments.cpp \
    NumInt.cpp \
    JacobiPolynomials.cpp \
    hpBasis1D.cpp

HEADERS  += mainwindow.h \
    QCustomPlot/qcustomplot.h \
    ElementMatrix.h \
    DirichletBoundaryConditions.h \
    DefineProblem.h \
    BasisFunctions.h \
    Assembly.h \
    TimeIntegration.h \
    ReadDataFile.h \
    PiezoAreaMoments.h \
    NumInt.h \
    JacobiPolynomials.h \
    hpBasis1D.h \
    find.h

FORMS    += mainwindow.ui

RC_FILE = FEAPB.rc

QMAKE_CXXFLAGS += -Wno-unused
QMAKE_CXXFLAGS += -pipe
QMAKE_CXXFLAGS += -DNDEBUG
#QMAKE_CXXFLAGS = -msse2
#QMAKE_CXXFLAGS += -ffast-math -funroll-loops -march=native -mtune=native -mfpmath=sse -finline-functions
QMAKE_CXXFLAGS +=-O2 -ffast-math -funroll-loops -finline-functions

INCLUDEPATH +=C:/Eigen_3
INCLUDEPATH += C:\boost_1_54_0
