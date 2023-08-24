#ifndef VTKOCC_QLINEARSPINNER_H
#define VTKOCC_QLINEARSPINNER_H

#include <QtWidgets/QWidget>
#include <QtCore/QAbstractAnimation>

class QLinearSpinner;
class QSpinnerAnimation;

class QSpinnerAnimation : public QAbstractAnimation {
    Q_OBJECT

public:
    explicit QSpinnerAnimation(QLinearSpinner* spinner);
    ~QSpinnerAnimation() override = default;
    int duration() const override;

protected:
    void updateCurrentTime(int currentTime) override;

private:
    QLinearSpinner* _spinner;
};

class QLinearSpinner : public QWidget {
    Q_OBJECT
    Q_PROPERTY(int spinnerRadius READ spinnerRadius WRITE setSpinnerRadius)

public:
    explicit QLinearSpinner(QWidget *parent = nullptr);
    ~QLinearSpinner() override;

    int spinnerRadius() const { return _spinnerRadius; }
    void setSpinnerRadius(int r) { _spinnerRadius = r; }

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QSpinnerAnimation* _animation;
    QVector<QRect> rects;
    int _spinnerRadius = 12;
};


#endif //VTKOCC_QLINEARSPINNER_H
