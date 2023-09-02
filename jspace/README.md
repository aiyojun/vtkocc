# Javascript Qt ui Management

解决的问题：c++编写ui编译耗时太长，无法进行热更新。

## QScript的一些特性

c++暴露到script中的类并非所有属性和方法都可以访问的，只有使用Qt Q_SIGNALS/Q_SLOTS/Q_PROPERTY/Q_INVOKABLE等注册过的元信息可以访问。

## 设计

建立一种script管理ui的api底层调用框架。