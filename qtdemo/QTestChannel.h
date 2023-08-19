//
// Created by Administrator on 2023/8/19.
//

#ifndef VTKOCC_QTESTCHANNEL_H
#define VTKOCC_QTESTCHANNEL_H

#include "imp.h"

class QTestChannel : public QObject {
    Q_OBJECT
public:
    QTestChannel() {}
    ~QTestChannel() = default;
Q_SIGNALS:
    void sendMessage(QString text);
public Q_SLOTS:
    void receiveFromWeb(QString text);
    int add(int a, int b) {return a + b;}
};


#endif //VTKOCC_QTESTCHANNEL_H
