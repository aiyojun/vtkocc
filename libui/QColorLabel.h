#ifndef VTKOCC_QCOLORLABEL_H
#define VTKOCC_QCOLORLABEL_H

#include <QtCore/QObject>
#include <QtWidgets/QLabel>

class QColorLabel : public QLabel {

    Q_OBJECT

public:

    explicit QColorLabel(QWidget *parent = nullptr) : QLabel(parent) {}

    explicit QColorLabel(const QString &text, QWidget *parent = nullptr) : QLabel(text, parent) {}

    ~QColorLabel() override = default;

};

#endif //VTKOCC_QCOLORLABEL_H
