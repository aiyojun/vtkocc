#ifndef VTKOCC_IMP_H
#define VTKOCC_IMP_H

#include <regex>
#include <algorithm>
#include <utility>
#include <functional>
#include <string>
#include <sstream>
#include <strstream>
#include <vector>
#include <tuple>
#include <map>
#include <exception>
#include <iostream>
#define TO_STR(S) #S
#define LOG(STR) std::cout << STR << std::endl
#include <QtCore/QJsonObject>
#include <QtCore/QMap>
#include <QtCore/QVector>
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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QFileDialog.h>
#include <QtWidgets/qstyleoption.h>
#include <QtWidgets/qstylepainter.h>

#include "QtTools.h"

#define R_PTR(P) if (!P) {delete P; P = nullptr;}

std::string toLowerCase(const std::string& text);
std::string toUpperCase(const std::string& text);


#endif //VTKOCC_IMP_H
