#ifndef VTKOCC_QSCRIPTFRAMEWORK_H
#define VTKOCC_QSCRIPTFRAMEWORK_H

#include "basic_qt.h"
#include "QColorLabel.h"
#include "QLinearSpinner.h"
#include "QNavigator.h"
#include "QOccViewer.h"
#include "json.hpp"

using nlohmann::json;

class QApplicationWindow;

QString readFile(const QString &path);

QScriptValue println(QScriptContext *context, QScriptEngine *engine);

QScriptValue error(QScriptContext *context, QScriptEngine *engine);

QScriptValue warn(QScriptContext *context, QScriptEngine *engine);

json convert(const QScriptValue &sv);

QScriptValue convert(QScriptEngine *engine, json j);

QScriptValue typecast(QScriptContext *context, QScriptEngine *engine);

//void RunQScript(const QString &script);

QScriptValue setTimeout(QScriptContext *context, QScriptEngine *engine, void *w);

QScriptValue parseInt(QScriptContext *context, QScriptEngine *engine);

QScriptValue parseFloat(QScriptContext *context, QScriptEngine *engine);


class QScriptTimer : public QObject {
    Q_OBJECT
public:
    QScriptTimer(QScriptValue fn): QObject(), _fn(fn), _finished(false) {}
    bool isFinished() { return _finished; }
public Q_SLOTS:
    void callback();
private:
    bool _finished;
    QScriptValue _fn;
};

class QScriptTimerManager {
public:
    int create(QScriptValue v);
    QScriptTimer *timer(int hd) { return _timers.contains(hd) ? _timers[hd] : nullptr; }
private:
    QMap<int, QScriptTimer*> _timers;
    QMutex _mutex;
    int _counter = 0;
};

class QApplicationWindow : public QMainWindow {

    Q_OBJECT

public:

    explicit QApplicationWindow(const QString& filename);

    ~QApplicationWindow() override;

    Q_INVOKABLE QString openLocalFilesystem();

Q_SIGNALS:

    void windowSizeChanged(int w, int h);

public Q_SLOTS:

    Q_INVOKABLE void setWindowIcon(const QString& filename);

    Q_INVOKABLE void hotReload();

    Q_INVOKABLE void place(QWidget *w, QPoint p);

    Q_INVOKABLE void setSize(QWidget *w, QSize size);

    Q_INVOKABLE void loadStylesheet(QString filename);

    Q_INVOKABLE int loadFont(QString filename);

    Q_INVOKABLE void setDefaultFont(QString fontFamily);

    Q_INVOKABLE QWidget *qLabel(QString id);

    Q_INVOKABLE QWidget *qColorLabel(QString id);

    Q_INVOKABLE QWidget *qPushButton(QString id);

    Q_INVOKABLE QWidget *qToolButton(QString id);

    Q_INVOKABLE QWidget *qNavigator(QString id);

    Q_INVOKABLE QWidget *qLineEdit(QString id);

    Q_INVOKABLE QWidget *qLinearSpinner(QString id);

    Q_INVOKABLE QWidget *qOccViewer(QString id);

    Q_INVOKABLE void setLabelText(QLabel *label, QString text);

    Q_INVOKABLE void setWidgetGeometry(QWidget *widget, QRect geo);

    Q_INVOKABLE void setWidgetVisible(QWidget *widget, bool visible);

    Q_INVOKABLE void setButtonText(QAbstractButton *button, QString text);

    Q_INVOKABLE void setButtonIcon(QAbstractButton *button, QString icon);

    Q_INVOKABLE void setButtonIconSize(QAbstractButton *button, QSize size);

    Q_INVOKABLE void setLineEditText(QLineEdit *edit, QString text);

    Q_INVOKABLE void setLineEditPlaceholder(QLineEdit *edit, QString text);

    Q_INVOKABLE void updateOcc(QOccViewer *w);

protected:

    void resizeEvent(QResizeEvent *event) override;

private:

    void load();

    void clear();

private:

    QVector<QWidget *> _widgets;

    QString _scriptPath;

    QScriptEngine _engine;

    QScriptTimerManager _timerManager;

    friend QScriptValue setTimeout(QScriptContext *context, QScriptEngine *engine, void *window);
};

#endif //VTKOCC_QSCRIPTFRAMEWORK_H
