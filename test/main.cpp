#include "QTaskLoop.h"
#include <QtCore/QDebug>

int main(int argc, char* argv[]) {

    QTaskLoop td;
    td.start(QThread::HighPriority);
    int count = 0;
    while (count < 5) {
        QThread::sleep(1);
        qDebug() << "[Main] count : " << count << " ";
        td.post([count]() {
            qDebug() << "[task] " << count;
        });
        count++;
    }
    qDebug() << "[Main] waiting ui thread ...";
    td.close();
    td.wait();

    return 0;
}