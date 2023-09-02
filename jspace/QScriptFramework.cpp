#include "QScriptFramework.h"

namespace  {

    QScriptValue println(QScriptContext *context, QScriptEngine *engine) {
        QString s;
        for (int i = 0; i < context->argumentCount(); i++) {
            s.append(context->argument(i).toString());
        }
        qDebug().noquote() << s;
        return engine->undefinedValue();
    }

}

using QWidgetBuilder = std::function<QWidget *()>;

void executeScript(const QString& script) {
    QScriptEngine engine;
    QScriptValue console;
    console.setProperty("info" , engine.newFunction(println));
    console.setProperty("error", engine.newFunction(println));
    console.setProperty("warn" , engine.newFunction(println));
    console.setProperty("debug", engine.newFunction(println));
    console.setProperty("log"  , engine.newFunction(println));
    auto *window = new QApplicationWindow();
    engine.globalObject().setProperty("console" , console);
    engine.globalObject().setProperty("qApplicationWindow", engine.newQObject(window));
    QScriptValue result = engine.evaluate(script);
    if (engine.hasUncaughtException())  {
        int line = engine.uncaughtExceptionLineNumber();
        qDebug() << "uncaught exception at line " << line << " : " << result.toString();
    }
}

QApplicationWindow::QApplicationWindow() {

}

QApplicationWindow::~QApplicationWindow() {

}

QWidget *QApplicationWindow::createWidget(const QString& type, const QString& id) {
    QWidget *p;
    QWidget *parent = this;
    QMap<QString, QWidgetBuilder> handles = {
            {"QLabel", [parent]() { return new QLabel(parent); }},
            {"QFrame", [parent]() { return new QFrame(parent); }},
            {"QPushButton", [parent]() { return new QPushButton(parent); }},
    };
    if (handles.find(type) == handles.end())
        p = new QWidget(parent);
    else
        p = handles[type]();
    if (!id.isEmpty())
        p->setObjectName(id);
    _widgets.push_back(p);
    return p;
}

