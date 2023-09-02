#ifndef VTKOCC_QSCRIPTFRAMEWORK_H
#define VTKOCC_QSCRIPTFRAMEWORK_H

#include <functional>

#include <QtCore/QString>
#include <QtCore/QVector>
#include <QtCore/QDebug>
#include <QtCore/QMap>
#include <QtCore/QFile>

#include <QtWidgets/QLabel>
#include <QtWidgets/QFrame>
#include <QtWidgets/QWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QApplication>

#include <QtScript/QScriptEngine>
#include <QtScript/QScriptClass>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtScript/QScriptClass>

class QApplicationWindow : public QMainWindow {
    Q_OBJECT
public:
    QApplicationWindow();
    ~QApplicationWindow() override;

    Q_INVOKABLE QWidget* createWidget(const QString &type, const QString& id = "");

private:
    QVector<QWidget *> _widgets;
};

void executeScript(const QString& script);




#endif //VTKOCC_QSCRIPTFRAMEWORK_H
