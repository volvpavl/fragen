#   Copyright 2015 Vladimir Volosunov
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET   = fragen
TEMPLATE = app
VERSION  = 0.1.0

win32: {
  set_version.commands = cd $$PWD && set_version.bat $$VERSION
}

QMAKE_EXTRA_TARGETS += set_version
PRE_TARGETDEPS      += set_version

CONFIG += c++14

SOURCES  += main.cpp \
            mainwindow.cpp \
            renderarea.cpp \
            image_renderer.cpp \
            save_dialog.cpp

HEADERS  += mainwindow.h \
            renderarea.h \
            image_renderer.h \
            save_dialog.h \
            fg_version.h

FORMS    += mainwindow.ui \
            save_dialog.ui
