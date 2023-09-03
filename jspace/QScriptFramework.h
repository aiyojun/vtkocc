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
#include <QtCore/QResource>

#include <QtWidgets/QLabel>
#include <QtWidgets/QFrame>
#include <QtWidgets/QWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QApplication>

#include <QtScript/QScriptEngine>
#include <QtScript/QScriptClass>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptValue>
#include <QtScript/QScriptClass>
#include <QtScript/QScriptValueIterator>
#include <QtGui/QFontDatabase>

#include "../libs3rd/json.hpp"
#include "../libui/QColorLabel.h"
#include "../libui/QLinearSpinner.h"
#include "../libui/QNavigator.h"


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

//    Q_INVOKABLE QWidget *createWidget(const QString &type, const QString &id = "");

    Q_INVOKABLE void place(QWidget *w, QPoint p) { w->move(p); }

    Q_INVOKABLE void loadStylesheet(QString filename) { QResource::registerResource(filename); }

    Q_INVOKABLE int loadFont(QString filename) { return QFontDatabase::addApplicationFont(filename); }

    Q_INVOKABLE void setDefaultFont(QString fontFamily) { QApplication::setFont(QFont(fontFamily)); }

    Q_INVOKABLE QWidget *qLabel(QString id);

    Q_INVOKABLE QWidget *qColorLabel(QString id);

    Q_INVOKABLE QWidget *qPushButton(QString id);

    Q_INVOKABLE QWidget *qToolButton(QString id);

    Q_INVOKABLE QWidget *qNavigator(QString id);

    Q_INVOKABLE QWidget *qLineEdit(QString id);

    Q_INVOKABLE void setLabelText(QLabel *label, QString text);

    Q_INVOKABLE void setWidgetGeometry(QWidget *widget, QRect geo);

    Q_INVOKABLE void setWidgetVisible(QWidget *widget, bool visible);

    Q_INVOKABLE void setButtonText(QAbstractButton *button, QString text);

    Q_INVOKABLE void setButtonIcon(QAbstractButton *button, QString icon);

    Q_INVOKABLE void setButtonIconSize(QAbstractButton *button, QSize size);

    Q_INVOKABLE void setLineEditText(QLineEdit *edit, QString text);

    Q_INVOKABLE void setLineEditPlaceholder(QLineEdit *edit, QString text);

private:
    QVector<QWidget *> _widgets;
};

void RunQScript(const QString &script);


#endif //VTKOCC_QSCRIPTFRAMEWORK_H
