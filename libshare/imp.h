#ifndef VTKOCC_IMP_H
#define VTKOCC_IMP_H

#include <regex>
#include <algorithm>
#include <utility>
#include <functional>
#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <exception>
#include <iostream>
#define TO_STR(S) #S
#define LOG(STR) std::cout << STR << std::endl
#include <QtCore/QString>
#include <QtCore/QFile>
#include <QtCore/QResource>
#include <QtCore/QRunnable>
#include <QtCore/QThread>
#include <QtCore/QThreadPool>
#include <QtGui/QFont>
#include <QtGui/QFontDatabase>
#include <QtGui/QPainter>
#include <QtGui/QResizeEvent>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLayout>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/qstyleoption.h>
#include <QtWidgets/qstylepainter.h>

#include "QxWidget.h"
#include "QtTools.h"

std::string toLowerCase(const std::string& text);
std::string toUpperCase(const std::string& text);


#endif //VTKOCC_IMP_H
