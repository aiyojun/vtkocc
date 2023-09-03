#ifndef VTKOCC_QSCRIPTFRAMEWORK_H
#define VTKOCC_QSCRIPTFRAMEWORK_H

#include <string>
#include <functional>

#include <QtCore/QString>
#include <QtCore/QVector>
#include <QtCore/QDebug>
#include <QtCore/QMap>
#include <QtCore/QFile>
#include <QtCore/QVariant>

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
#include <QtScript/QScriptValueIterator>

#include "../libs3rd/json.hpp"

using nlohmann::json;

QString readFile(const QString &path);

QScriptValue println(QScriptContext *context, QScriptEngine *engine);

QScriptValue error(QScriptContext *context, QScriptEngine *engine);

QScriptValue warn(QScriptContext *context, QScriptEngine *engine);

json convert(const QScriptValue &sv);

QScriptValue convert(QScriptEngine *engine, json j);

QScriptValue typecast(QScriptContext *context, QScriptEngine *engine);

class QApplicationWindow : public QMainWindow {
Q_OBJECT
public:
    QApplicationWindow();

    ~QApplicationWindow() override;

    Q_INVOKABLE QWidget *createWidget(const QString &type, const QString &id = "");

    Q_INVOKABLE void place(QWidget *w, QPoint p) { w->move(p); }

private:
    QVector<QWidget *> _widgets;
};

void RunQScript(const QString &script);


#endif //VTKOCC_QSCRIPTFRAMEWORK_H
