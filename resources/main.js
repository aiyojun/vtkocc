/**
 * Qt script ui management framework.
 */
var window = qApplicationWindow
var label0 = window.qLabel("label0")
var input0 = window.qLineEdit("input0")
var label1 = window.qLabel("label1")
var input1 = window.qLineEdit("input1")
var button0 = window.qPushButton("button0");
var button1 = window.qPushButton("button1");
// console.info("button : ", Object.keys(button0))
// console.info("input  : ", Object.keys(input1))
label0.setText("Username")
label1.setText("Password")
window.place(label0, typecast("QPoint", new QPoint(0, 0)))
window.place(input0, typecast("QPoint", new QPoint(80, 0)))
window.place(label1, typecast("QPoint", new QPoint(0, 32)))
window.place(input1, typecast("QPoint", new QPoint(80, 32)))
window.place(button0, typecast("QPoint", new QPoint(0, 64)))
window.place(button1, typecast("QPoint", new QPoint(80, 64)))

// input0.setGeometry(new QRect(80, 0, 120, 32))
window.setWidgetGeometry(input0, typecast("QRect", new QRect(80, 0, 200, 32)));
window.setLineEditPlaceholder(input0, "Please input username")
window.setLineEditPlaceholder(input1, "Please input password")
// input0.setPlaceholderText("Please input username")
// input1.setPlaceholderText("Please input password")
// button0.setText("OK")
window.setButtonText(button0, "OK")
window.setButtonText(button1, "Cancel")
console.info("button0 text :", button0.text)

// window.setWidgetGeometry(input0, typecast("QRect", new QRect(80, 0, 200, 32)));
// button1.setText("Cancel")
window.show()


// var xlabel = window.createWidget("QLabel", "xlabel")
// xlabel.setText("Hello World")
// console.info(xlabel.pos)
// console.info(typecast(xlabel.pos))
// window.place(xlabel, typecast("QPoint", new QPoint(50, 20)))
// window.show();
//
// console.info(JSON.stringify({"a": 12}))
//
