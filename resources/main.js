/**
 * Qt script ui management framework.
 */
var xlabel = qApplicationWindow.createWidget("QLabel", "xlabel")
xlabel.setText("Hello World")
console.info(xlabel.pos)
// console.info(Object.keys(xlabel))
console.info(typecast(xlabel.pos))
qApplicationWindow.place(xlabel, typecast("QPoint", new QPoint(50, 20)))
qApplicationWindow.show();

console.info(JSON.stringify({"a": 12}))

