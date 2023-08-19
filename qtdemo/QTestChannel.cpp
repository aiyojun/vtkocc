//
// Created by Administrator on 2023/8/19.
//

#include "QTestChannel.h"

void QTestChannel::receiveFromWeb(QString text) {
    LOG("-- from web : " + text.toStdString());
}
