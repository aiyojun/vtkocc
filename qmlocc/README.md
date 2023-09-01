# qmlocc

QML这种声明式ui很像JSON view engine的模式。

JSON view engine还差很多功能，如动态操作，构造动画，交互式ui(如拖拽)等等。

QML具备很丰富的功能。

但是，QML也有问题，QML是完全隔离出来的环境，需要探究一下是否能够借助JavaScript完全控制QML？

JSON view engine依然是c++层面主导的，QML的控制权要是能完全交给编程语言(JavaScript)处理的话，那其实扩展性还是很强的。