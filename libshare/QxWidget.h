#ifndef VTKOCC_QXWIDGET_H
#define VTKOCC_QXWIDGET_H

#include "imp.h"
#include "json.hpp"
using nlohmann::json;

class QxWidget;

class WidgetContext {
public:
    json&  _template;
    QWidget* _parent;
    std::map<std::string, QWidget *>& _pool;
    QPoint _begin;
    WidgetContext(json& t, QWidget* p, std::map<std::string, QWidget *>& pl, QPoint bp)
            : _template(t), _parent(p), _pool(pl), _begin(bp) {}
    ~WidgetContext() = default;
};

using WidgetHandle = std::function<QxWidget* (WidgetContext &)>;

class QxWidget : public QWidget {
    Q_OBJECT
Q_SIGNALS:
    void clicked();
public:
    explicit QxWidget(QWidget *parent);
    QxWidget(std::string type, QWidget *parent);
    virtual ~QxWidget();
    static QWidget *parse(json& root, QWidget *parent, std::map<std::string, QWidget *> &pool);
    inline std::string getType() {return type;}
    void setTemplate(json& json) {_template = json;}
    void setQxWidgetGeometryByTemplate();
    const std::vector<QWidget*>& getChildren() { return children; };
    inline static void registerQxWidget(const std::string& name, WidgetHandle hd)
    { handles[name] = hd; }
protected:
    json _template;
    std::string type;
    static QxWidget* uiParse(WidgetContext& context);
    QBoxLayout* buildFlex(QBoxLayout::Direction direction = QBoxLayout::Direction::LeftToRight);
    QLabel* buildLabel(const QString& text = "");
protected:
    void resizeEvent(QResizeEvent *event) override;
private:
    static std::map<std::string, WidgetHandle> handles;
protected:
    std::vector<QObject*> r_ptr;
    std::vector<QWidget*> children;
};


class QxBaseWidget : public QxWidget {
    Q_OBJECT
public:
    explicit QxBaseWidget(QWidget* parent): QxWidget(TO_STR(QxBaseWidget), parent) {}
    ~QxBaseWidget() = default;
    static QxBaseWidget* build(WidgetContext& context);
};


class QxStatusWidget : public QxWidget {
Q_OBJECT
public:
    explicit QxStatusWidget(QWidget* parent): QxWidget(TO_STR(QxStatusWidget), parent) {}
    ~QxStatusWidget() { if (statusBar != nullptr) delete statusBar; };
    static QxStatusWidget* build(WidgetContext& context);
public Q_SLOTS:
    void setStatus(QString message);
private:
    QLabel* statusBar;
};


class QxDockButton : public QxWidget {
    Q_OBJECT
public:
    explicit QxDockButton(QWidget* parent): QxWidget(TO_STR(QxDockButton), parent) {}
    ~QxDockButton() override = default;
    static QxDockButton* build(WidgetContext& context);
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif //VTKOCC_QXWIDGET_H
