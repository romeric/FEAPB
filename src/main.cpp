/** This program is an implemention of hp-finite elements for
*   three-dimensional linear piezoelectric beams.
*
*   © Copyright 2013 Roman Poya
*
*   This file is part of FEAPB.
*   FEAPB is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   any later version.
*
*   FEAPB is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with FEAPB.  If not, see <http://www.gnu.org/licenses/>.
*
*
*   Contact details: romanpoya@gmail.com or roman.poya@cimne.com
*/

#include <QApplication>
#include "mainwindow.h"
#include <QtPrintSupport/QPrinter>

int main(int argc, char *argv[])
{
    QApplication FEAPB(argc, argv);

    // startup screen
    QString path = QDir::currentPath();
    QPixmap pixmap(path+"/img/feapb_transparent.png");
    QSplashScreen splash(pixmap);
    splash.show();
    FEAPB.processEvents();

    FEAPB.setOrganizationName("Civil & Computational Engineering Centre, Swansea University");
    MainWindow window;

    QPalette pal = FEAPB.palette();
    QColor gray(250,250,250);
    pal.setColor(QPalette::Window, gray);
    pal.setBrush(QPalette::NoRole,Qt::NoBrush);

    // QFont newFont("Consolas", 10, QFont::Bold, false);
    // window.setFont(newFont);

    QFont newFont;
    newFont.setBold(true);
    newFont.setWeight(10);
    window.setFont(newFont);

    FEAPB.setPalette(pal);

    // Styling (All CSS Format)
    FEAPB.setStyleSheet(
                        "QPushButton {min-height: 1em; font: 1em; margin: 0px 1px 0 1px; background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffffff, stop: 1 #e8e8e8); color: #585858; border-style: outset; border-radius: 6px; border-width: 1.25px; border-top-left-radius: 10px; border-bottom-left-radius: 0px; border-bottom-right-radius: 10px; border-top-right-radius: 0px; border-color: #A8A8A8; font-size: 9pt; font-weight: bold;}"
                        "QPushButton:pressed {border-style: inset; background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #e8e8e8, stop: 1 #ffffff);}"
                        "QPushButton::disabled {border-style: solid; color: darkgray; border-color: darkgray;}"

                        "QComboBox {color: #585858; border-style: outset; border-radius: 5px; border-width: 1.25px; border-color: #a0a0a0; border-color: #a0a0a0; font-weight: bold;}"
                        "QComboBox QAbstractItemView {border-style: inset; border-radius: 2px; border-color: transparent; color: #585858; font-weight: bold; selection-background-color: #585858; selection-color: white;   }"
                        "QComboBox::drop-down {subcontrol-origin: padding; subcontrol-position: top right; width: 15px; border-left-width: 1px; border-left-color: #585858; border-left-style: solid; border-top-right-radius: 3px; border-bottom-right-radius: 3px;}"
                        "QComboBox::down-arrow {image: url("+path+"/img/down_arrow_6.png); width: 9px; height: 7px;}"
                        "QComboBox::disabled {color: darkgray; border-style: solid; border-radius: 5px; border-width: 1.25px; border-color: darkgray; font-weight: bold;}"
                        "QComboBox::down-arrow::disabled {image: url("+path+"/img/down_arrow_2.png); width: 9px; height: 7px;}"
                        "QComboBox::drop-down::disabled {subcontrol-origin: padding; subcontrol-position: top right; width: 15px; border-left-width: 1px; border-left-color: darkgray; border-left-style: solid; border-top-right-radius: 3px; border-bottom-right-radius: 3px;}"

                        "QLineEdit {color: #585858; border-style: inset; border-radius: 5px; border-width: 1.25px; border-color: #a0a0a0; border-top-left-radius: 10px; border-bottom-left-radius: 0px; border-bottom-right-radius: 10px; border-top-right-radius: 0px; background-color: white; font-weight: bold; selection-background-color: #585858; selection-color: white;}"
                        "QLineEdit::disabled {color: darkgray; border-style: solid; border-radius: 5px; border-width: 1.25px; border-color: darkgray; border-top-left-radius: 10px; border-bottom-left-radius: 0px; border-bottom-right-radius: 10px; border-top-right-radius: 0px; font-weight: bold; background-color: rgb(211,211,211);}"

                        "QSpinBox {color: #585858; border-style: outset; border-radius: 5px; border-width: 1.25px; border-color: #a0a0a0; font-weight: bold; selection-background-color: #585858; selection-color; white;}"
                        "QSpinBox::up-button {subcontrol-origin: padding; subcontrol-position: top right; width: 15px; border-left-width: 1px; border-left-color: #585858; border-left-style: solid; border-top-right-radius: 3px; border-bottom-right-radius: 3px;}"
                        "QSpinBox::down-button {subcontrol-origin: padding; subcontrol-position: bottom right; width: 15px; border-left-width: 1px; border-left-color: #585858; border-left-style: solid; border-top-right-radius: 3px; border-bottom-right-radius: 3px;}"
                        "QSpinBox::down-arrow {image: url("+path+"/img/down_arrow_8.png); width: 6px; height: 7px;}"
                        "QSpinBox::up-arrow {image: url("+path+"/img/down_arrow_7.png); width: 6px; height: 7px;}"

                        "QMenu {min-height: 1.25em; font: 1em; margin: 0 1px 0 1px; padding: 2px 15px 2px 10px; color: #585858; border-style: inset; border-radius: 4px; border-width: 1.35px; border-color: #A8A8A8; font-size: 9pt; font-weight: bold;}"
                        "QMenu::item {padding: 2px 15px 2px 10px; color: #585858; border-style: outset; border-radius: 5.5px; border-width: 1.25px; border-color: #A8A8A8; font-size: 9pt;}"
                        "QMenu::item:selected {border-color: #585858; background: #888888; color: white;}"  // for hovering
                        "QMenu::item::disabled {color: darkgray; border-style: solid; border-radius: 5.5px; border-width: 1.25px; border-color: darkgray; font-weight: bold;}"
                        "QMenu::item:pressed {border-color: #585858; background: #888888; color: white; border-style: inset;}"  // for hovering
                        "QMenu::item::disabled:pressed {color: darkgray; border-style: solid; border-radius: 5.5px; border-width: 1.25px; border-color: darkgray; font-weight: bold;}"
                        "QMenu::separator {height: 4px; background: #787878; margin-left: 5px; margin-right: 5px;}"

                        "QMenuBar {min-height: 1.0em; font: 1em; margin: 0px 0px 0 0px; padding: 10px 15px 2px 10px; background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffffff, stop: 1 #e8e8e8); color: #585858; border-style: outset; border-radius: 6px; border-width: 1.0px; border-color: #A8A8A8; font-size: 9pt; font-weight: bold;}"
                        "QMenuBar::item {margin: 0px 5px 0px 5px; padding: 2px 15px 2px 10px; border-color: #a0a0a0; border-style: inset; border-radius: 8x; border-width: 1px; border-top-left-radius: 10px; border-bottom-left-radius: 0px; border-bottom-right-radius: 10px; border-top-right-radius: 0px; background-color: white;}"
                        "QMenuBar::item:selected {border-color: #585858; background: #888888; color: white;}"

                        "QTextEdit {color: #585858; border-style: outset; border-radius: 10px; border-width: 1.4px; border-color: #b0b0b0; border-top-left-radius: 15px; border-bottom-left-radius: 0px; border-bottom-right-radius: 15px; border-top-right-radius: 0px; background-color: white; font-weight: bold; selection-background-color: #585858; selection-color: white;}"

                        "QDialog {color: #585858; border-style: inset; border-radius: 10px; border-width: 1.4px; border-color: #b0b0b0; border-top-left-radius: 15px; border-bottom-left-radius: 0px; border-bottom-right-radius: 15px; border-top-right-radius: 0px; background-color: #f8f8f8; font-weight: bold; selection-background-color: #585858; selection-color: white;}"

                        // "QWidget {min-height: 1.4em; font: 1em; color: #585858; border-style: outset; border-radius: 10px; border-width: 1.4px; border-color: #b0b0b0; border-top-left-radius: 15px; border-bottom-left-radius: 0px; border-bottom-right-radius: 15px; border-top-right-radius: 0px; background-color: #f8f8f8; font-weight: bold; selection-background-color: #585858; selection-color: white;}"

                        "QStatusBar {min-height: 1.4em; font: 1em; margin: 0px 0.1px 0px 0.1px; color: #585858; border-style: inset; border-radius: 10px; border-width: 1.4px; border-color: #b0b0b0; border-top-left-radius: 0px; border-bottom-left-radius: 0px; border-bottom-right-radius: 0px; border-top-right-radius: 0px; background-color: #f8f8f8; font-weight: bold; selection-background-color: #585858; selection-color: white;}"

                        "QMessageBox::critical {min-height: 1.4em; font: 1em; margin: 0px 0.1px 0px 0.1px; color: #585858; border-style: outset; border-radius: 10px; border-width: 1.4px; border-color: #b0b0b0; border-top-left-radius: 15px; border-bottom-left-radius: 15px; border-bottom-right-radius: 15px; border-top-right-radius: 15px; background-color: #f8f8f8; font-weight: bold; selection-background-color: #585858; selection-color: white;}"

                        "QScrollBar:vertical {background: white; width: 7px; border-style: inset; margin: 0.5px 0px 9px 0px;}"
                        "QScrollBar::handle:vertical {background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 #eaeaea, stop: 1 #a8a8a8); border-style: outset; min-height: 0px; border-top-left-radius: 3px; border-bottom-left-radius: 3px; border-bottom-right-radius: 3px; border-top-right-radius: 3px;}"

                        "QLabel {min-height: 1.4em; font: 1em; color: #585858; font-weight: bold; selection-background-color: #585858; selection-color: white;}"

                        "QProgressBar {border: 1.4px inset grey; border-radius: 5px; }"
                        "QProgressBar::chunk { background-color:  #585858;  width: 20px; border: 1.4px outset #b0b0b0; border-radius: 5px; border-top-left-radius: 5px; border-bottom-left-radius: 0px; border-bottom-right-radius: 5px; border-top-right-radius: 0px;}"

                        "QToolTip {min-height: 1.4em; font: 1em; margin: 0px 0.1px 0px 0.1px; color: #585858; border-style: inset; border-radius: 10px; border-width: 1.4px; border-color: #b0b0b0; border-top-left-radius: 2px; border-bottom-left-radius: 0px; border-bottom-right-radius: 2px; border-top-right-radius: 0px; background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #e8e8e8, stop: 1 #ffffff); font-weight: bold; selection-background-color: #585858; selection-color: white;}"

                );


    window.setWindowFlags(Qt::FramelessWindowHint);
    window.show();
    splash.finish(&window);

    return FEAPB.exec();
}
