#ifndef VTKOCC_QLINEARSPINNER_H
#define VTKOCC_QLINEARSPINNER_H

#include <QtWidgets/QWidget>
#include <QtCore/QAbstractAnimation>

class QRepaintAnimation : public QAbstractAnimation {
    Q_OBJECT
    Q_PROPERTY(int duration READ duration WRITE setDuration)

public:
    explicit QRepaintAnimation(QWidget* companion);
    ~QRepaintAnimation() override = default;
    int duration() const override;
    void setDuration(int d) { _duration = d; }

protected:
    void updateCurrentTime(int currentTime) override;

private:
    int _duration;
    QWidget* _companion;
};

class QLinearSpinner : public QWidget {
    Q_OBJECT
    Q_PROPERTY(int spinnerRadius READ spinnerRadius WRITE setSpinnerRadius)
    Q_PROPERTY(int spinnerDistance READ spinnerDistance WRITE setSpinnerDistance)
    Q_PROPERTY(QString spinnerColor READ spinnerColor WRITE setSpinnerColor)
    Q_PROPERTY(QString spinnerBackgroundColor READ spinnerBackgroundColor WRITE setSpinnerBackgroundColor)
    Q_PROPERTY(int spinnerBackgroundRadius READ spinnerBackgroundRadius WRITE setSpinnerBackgroundRadius)

public:
    explicit QLinearSpinner(QWidget *parent = nullptr);
    ~QLinearSpinner() override;

    int spinnerRadius() const { return _spinnerRadius; }
    void setSpinnerRadius(int r) { _spinnerRadius = r; }
    int spinnerDistance() const { return _spinnerDistance; }
    void setSpinnerDistance(int d) { _spinnerDistance = d; }
    QString spinnerColor() const { return _spinnerColor; }
    void setSpinnerColor(const QString& c) { _spinnerColor = c; }
    QString spinnerBackgroundColor() const { return _spinnerBackgroundColor; }
    void setSpinnerBackgroundColor(const QString& c) { _spinnerBackgroundColor = c; }
    int spinnerBackgroundRadius() const { return _spinnerBackgroundRadius; }
    void setSpinnerBackgroundRadius(int d) { _spinnerBackgroundRadius = d; }

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int _spinnerRadius    = 12;
    int _spinnerDistance  = 50;
    int _spinnerBackgroundRadius = 8;
    QString _spinnerColor = "#E0C3FC";
    QString _spinnerBackgroundColor = "#FFFFFF";
    QRepaintAnimation* _animation;
};


#endif //VTKOCC_QLINEARSPINNER_H
