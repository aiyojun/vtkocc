# 问题记录

# Qt问题汇总

# QtWidgets相关

## 问：在Qt QWidget中设置WindowFlags为Qt::Window导致该Widget消失了，为什么？

答：WindowFlags设置为Qt::Window，表示该widget变为window类型，需要调用QWidget::show()方法。


## 问：Qt中WindowFlags Widget和Window的区别？

答：Widget的位置是相对于父widget的，Window的位置是相对于桌面的。


## 问：Qt中如何获取桌面大小？

答：QApplication::desktop()->width()/height()


## 问：Qt QWidget中，QWidget::setAutoFillBackground(bool)什么作用？

答：设置是否让Qt在QWidget::paintEvent(e)触发之前，使用QWidget::palette()来填充背景。
参考：https://doc.qt.io/qt-5/qwidget.html#autoFillBackground-prop


## 问：Qt中，如何让QWidget的背景变透明？

答：设置setAttribute(Qt::WA_TranslucentBackground)使QWidget支持半透明效果，然后可以将QWidget::setPalette(QColor)设置透明色，也可以在QSS中指定background: transparent。


## 问：使用Qt QWidget作为OpenGL渲染窗口时，其他QWidget(如QLabel等)位于OpenGL窗口上面时，Widget窗口会变黑，为什么？

答：原理上讲，是系统的窗口管理器无法将这几个窗口的像素进行blend混合，可以通过离屏渲染的方式解决。
参考1：https://blog.csdn.net/xiaoyafang123/article/details/129265541
参考2：https://blog.51cto.com/hongpangzi/3620559


## 问：如何在OpenGL类型的窗口上叠加具有透明效果的Widget控件。

答：将Widget提升为Window级别的控件，QWidget::setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint)。



## QtScript相关

## QScript对JavaScript的内置接口支持有哪些？

答：
支持 
JSON接口
parse()/stringify()
Object接口
keys()

不支持
console对象
window对象
setTimeout()
clearTimeout()
setInterval()
clearInterval()
