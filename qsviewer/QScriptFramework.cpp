#include "QScriptFramework.h"

QString readFile(const QString &path) {
    QFile file(path);
    QString r;
    if (file.exists()) {
        file.open(QFile::OpenModeFlag::ReadOnly);
        r = QString(file.readAll());
        file.close();
    }
    return r;
}

QScriptValue println(QScriptContext *context, QScriptEngine *engine) {
    QString s;
    for (int i = 0; i < context->argumentCount(); i++) {
        if (i != 0) s.append(" ");
        auto arg = context->argument(i);
        if (arg.isVariant()) {
            s.append(arg.toString());
        } else if (arg.isObject()) {
            s.append(to_string(convert(arg)).c_str());
        } else {
            s.append(arg.toString());
        }
    }
    qDebug().noquote() << "[QScript] " << s;
    return engine->undefinedValue();
}

json convert(const QScriptValue& sv) {
    if (sv.isNull())
        return nullptr;
    if (sv.isString())
        return sv.toString().toStdString();
    if (sv.isBoolean())
        return sv.toBoolean();
    if (sv.isNumber())
        return sv.toNumber();
    if (sv.isArray()) {
        json arr = json::array();
        QScriptValueIterator it(sv);
        while (it.hasNext()) {
            it.next();
            arr.push_back(convert(it.value()));
        }
        return arr;
    }
    json jr;
    QScriptValueIterator it(sv);
    while (it.hasNext()) {
        it.next();
        jr[it.name().toStdString()] = convert(it.value());
    }
    return jr;
}

QScriptValue convert(QScriptEngine *engine, json j) {
    if (j.is_string())
        return {QString(j.get<std::string>().c_str())};
    if (j.is_number_integer())
        return {j.get<int>()};
    if (j.is_number_float())
        return {j.get<double>()};
    if (j.is_boolean())
        return {j.get<bool>()};
    if (j.is_null())
        return engine->nullValue();
    if (j.is_array()) {
        QScriptValue arr = engine->newArray((int) j.size());
        int i = 0;
        for (auto& e : j) {
            arr.setProperty(i, convert(engine, e));
            i++;
        }
        return arr;
    }
    QScriptValue rj = engine->newObject();
    for (json::iterator it = j.begin(); it != j.end(); ++it) {
        rj.setProperty(it.key().c_str(), convert(engine, it.value()));
    }
    return rj;
}

QScriptValue typecast(QScriptContext *context, QScriptEngine *engine) {
    auto ref = context->argument(0);
    if (context->argumentCount() == 1) {
        if (!ref.isVariant()) return engine->nullValue();
        auto var = ref.toVariant();
        if (var.type() == QVariant::Type::Point) {
            auto point = var.toPoint();
            return convert(engine, {
                    {"x", point.x()},
                    {"y", point.y()}
            });
        }
        if (var.type() == QVariant::Type::Size) {
            auto size = var.toSize();
            return convert(engine, {
                    {"width", size.width()},
                    {"height", size.height()}
            });
        }
        if (var.type() == QVariant::Type::Rect) {
            auto rect = var.toRect();
            return convert(engine, {
                    {"x", rect.x()},
                    {"y", rect.y()},
                    {"width", rect.width()},
                    {"height", rect.height()}
            });
        }
        return engine->nullValue();
    }
    if (context->argumentCount() == 2) {
        auto base = context->argument(1);
        auto type = ref.toString();
        if (type == "QPoint")
            return engine->newVariant(QVariant(QPoint((int) base.property("x").toInteger(), (int) base.property("y").toInteger())));
        if (type == "QSize")
            return engine->newVariant(QVariant(QSize((int) base.property("width").toInteger(), (int) base.property("height").toInteger())));
        if (type == "QRect")
            return engine->newVariant(QVariant(QRect((int) base.property("x").toInteger(), (int) base.property("y").toInteger(), (int) base.property("width").toInteger(), (int) base.property("height").toInteger())));
    }
    return engine->nullValue();
}

//using QWidgetBuilder = std::function<QWidget *()>;

//void RunQScript(const QString& script) {
//    QString preload = readFile(":/qscriptpreload.js");
//    QScriptEngine engine;
//    QScriptValue console = engine.newObject();
//    console.setProperty("info" , engine.newFunction(println));
//    console.setProperty("error", engine.newFunction(println));
//    console.setProperty("warn" , engine.newFunction(println));
//    console.setProperty("debug", engine.newFunction(println));
//    console.setProperty("log"  , engine.newFunction(println));
//    auto *window = new QApplicationWindow();
//    engine.globalObject().setProperty("console", console);
//    engine.globalObject().setProperty("typecast", engine.newFunction(typecast));
//    engine.globalObject().setProperty("qApplicationWindow", engine.newQObject(window));
//    engine.evaluate(preload);
//    QScriptValue result = engine.evaluate(script);
//    if (engine.hasUncaughtException())  {
//        int line = engine.uncaughtExceptionLineNumber();
//        qFatal(QString("uncaught exception at line ").append(std::to_string(line).c_str()).append(" : ").append(result.toString()).toStdString().c_str());
//    }
//}

QApplicationWindow::QApplicationWindow(const QString& filename): _scriptPath(filename) {
    load();
}

QApplicationWindow::~QApplicationWindow() {
    clear();
}

void QApplicationWindow::load() {
    QString preload = readFile(":/qscriptpreload.js");
    QScriptEngine& engine = _engine;
    QScriptValue console = engine.newObject();
    console.setProperty("info" , engine.newFunction(println));
    console.setProperty("error", engine.newFunction(println));
    console.setProperty("warn" , engine.newFunction(println));
    console.setProperty("debug", engine.newFunction(println));
    console.setProperty("log"  , engine.newFunction(println));
    auto *window = this;
//    auto *window = new QApplicationWindow();
    engine.globalObject().setProperty("console", console);
    engine.globalObject().setProperty("typecast", engine.newFunction(typecast));
    engine.globalObject().setProperty("qApplicationWindow", engine.newQObject(window));
    engine.evaluate(preload);
    QScriptValue result = engine.evaluate(QtUtils::readFile(_scriptPath));
    if (engine.hasUncaughtException())  {
        int line = engine.uncaughtExceptionLineNumber();
        qFatal(QString("uncaught exception at line ").append(std::to_string(line).c_str()).append(" : ").append(result.toString()).toStdString().c_str());
    }
}

void QApplicationWindow::clear() {
    for (auto &p : _widgets) { p->hide(); R_PTR(p) } _widgets.clear();
}

void QApplicationWindow::hotReload() {
    qDebug() << "QApplicationWindow::hotReload()";
    clear();
    repaint();
    hide();
    QScriptEngine& engine = _engine;
    QScriptValue result = engine.evaluate(QtUtils::readFile(_scriptPath));
    if (engine.hasUncaughtException())  {
        int line = engine.uncaughtExceptionLineNumber();
        qFatal(QString("uncaught exception at line ").append(std::to_string(line).c_str()).append(" : ").append(result.toString()).toStdString().c_str());
    }
    show();
}

void QApplicationWindow::place(QWidget *w, QPoint p) {
    qDebug() << "QApplicationWindow::place(" << w->objectName() << ", " << p << ")";
    w->move(p);
}

void QApplicationWindow::setSize(QWidget *w, QSize size) {
    qDebug() << "QApplicationWindow::setSize(" << w->objectName() << ", " << size << ")";
    w->resize(size);
}

void QApplicationWindow::loadStylesheet(QString filename) {
    qDebug() << "QApplicationWindow::loadStylesheet(" << filename << ")";
    setStyleSheet(QtUtils::readFile(filename));
}

int QApplicationWindow::loadFont(QString filename) {
    qDebug() << "QApplicationWindow::loadFont(" << filename << ")";
    return QFontDatabase::addApplicationFont(filename);
}

void QApplicationWindow::setDefaultFont(QString fontFamily) {
    qDebug() << "QApplicationWindow::setDefaultFont(" << fontFamily << ")";
    QApplication::setFont(QFont(fontFamily));
}

#define IMPLEMENTATION_BUILD_WIDGET(CLS) \
    auto *p = new CLS(this);\
    p->setObjectName(id); \
    _widgets.push_back(p);\
    return p;

QWidget *QApplicationWindow::qLabel(QString id) {
    IMPLEMENTATION_BUILD_WIDGET(QLabel)
}

QWidget *QApplicationWindow::qColorLabel(QString id) {
    IMPLEMENTATION_BUILD_WIDGET(QColorLabel)
}

QWidget *QApplicationWindow::qPushButton(QString id) {
    IMPLEMENTATION_BUILD_WIDGET(QPushButton)
}

QWidget *QApplicationWindow::qToolButton(QString id) {
    IMPLEMENTATION_BUILD_WIDGET(QToolButton)
}

QWidget *QApplicationWindow::qNavigator(QString id) {
    IMPLEMENTATION_BUILD_WIDGET(QNavigator)
}

QWidget *QApplicationWindow::qLineEdit(QString id) {
    IMPLEMENTATION_BUILD_WIDGET(QLineEdit)
}

QWidget *QApplicationWindow::qLinearSpinner(QString id) {
    IMPLEMENTATION_BUILD_WIDGET(QLinearSpinner)
}

void QApplicationWindow::setWidgetGeometry(QWidget *widget, QRect geo) {
    qDebug() << "QApplicationWindow::setWidgetGeometry(" << widget->objectName() << ", " << geo << ")";
    widget->setGeometry(geo);
}

void QApplicationWindow::setWidgetVisible(QWidget *widget, bool visible) {
    qDebug() << "QApplicationWindow::setWidgetVisible(" << widget->objectName() << ", " << (visible ? "true" : "false") << ")";
    if (visible)
        widget->show();
    else
        widget->hide();
}

void QApplicationWindow::setButtonText(QAbstractButton *button, QString text) {
    qDebug() << "QApplicationWindow::setButtonText(" << button->objectName() << ", " << text << ")";
    button->setText(text);
}

void QApplicationWindow::setButtonIcon(QAbstractButton *button, QString icon) {
    qDebug() << "QApplicationWindow::setButtonIcon(" << button->objectName() << ", " << icon << ")";
    button->setIcon(QIcon(icon));
}

void QApplicationWindow::setButtonIconSize(QAbstractButton *button, QSize size) {
    qDebug() << "QApplicationWindow::setButtonIconSize(" << button->objectName() << ", " << size << ")";
    button->setIconSize(size);
}

void QApplicationWindow::setLineEditText(QLineEdit *edit, QString text) {
    edit->setText(text);
}

void QApplicationWindow::setLineEditPlaceholder(QLineEdit *edit, QString text) {
    edit->setPlaceholderText(text);
}

void QApplicationWindow::setLabelText(QLabel *label, QString text) {
    label->setText(text);
}

//QWidget *QApplicationWindow::createWidget(const QString& type, const QString& id) {
//    QWidget *p;
//    QWidget *parent = this;
//    QMap<QString, QWidgetBuilder> handles = {
//            {"QLabel", [parent]() { return new QLabel(parent); }},
//            {"QColorLabel", [parent]() { return new QColorLabel(parent); }},
//            {"QFrame", [parent]() { return new QFrame(parent); }},
//            {"QPushButton", [parent]() { return new QPushButton(parent); }},
//            {"QToolButton", [parent]() { return new QToolButton(parent); }},
//            {"QLinearSpinner", [parent]() { return new QLinearSpinner(parent); }},
//            {"QLineEdit", [parent]() { return new QLineEdit(parent); }},
//            {"QNavigator", [parent]() { return new QNavigator(parent); }},
//    };
//    if (handles.find(type) == handles.end())
//        p = new QWidget(parent);
//    else
//        p = handles[type]();
//    if (!id.isEmpty())
//        p->setObjectName(id);
//    _widgets.push_back(p);
//    return p;
//}
