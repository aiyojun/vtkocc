#ifndef VTKOCC_QASYNC_H
#define VTKOCC_QASYNC_H

#include "imp.h"
#include <OSD_Thread.hxx>

class QRunnableLambda : public QObject, public QRunnable {
    Q_OBJECT
public:
    QRunnableLambda(std::function<void ()> lambda): _lambda(lambda) { }
    void run() override { _lambda(); emit finished(); }
Q_SIGNALS:
    void finished();
private:
    std::function<void ()> _lambda;
};

class QOSDTread : public QObject, public QRunnable {
    Q_OBJECT
public:
    QOSDTread(OSD_ThreadFunction const lambda) {
        _thread.SetFunction(lambda);
    }
    void run() override { _thread.Run(); emit finished(); }
Q_SIGNALS:
    void finished();
private:
    OSD_Thread _thread;
};

#endif //VTKOCC_QASYNC_H
