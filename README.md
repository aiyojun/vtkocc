# vtkocc

learning opencascade, try to develop a opensource project based on VTK and OCCT.

Most code is in a mess, and in developing stage. After several days, I will refactor them.


## Build

Clion open the project, directly! Click 'Build' and 'Run'.

Or:

```shell
# Now, only support windows, linux will soon
# Make sure Visual Studio 2022 Community, OpenCASCADE, Qt5.12.0 in your computer!
env.bat
build_occviewer.bat
```

## OCCT Resources

```txt
https://gitlab.com/ssv/lessons
```

## Construct GUI by Qt

Two ways of constructing graphic interface by Qt:

1.   Qt original approach, we will reap ugly UI;
2.   Use QWebEngineView, good idea, front-end developer friendly, but trashy UI painting mechanism.

Therefore, we are supposed to rebuild UI design system first!

QSS is a good and useful tool, to beatify Qt application GUI.

At current stage(8.22.2023), I implemented a simple rendering framework based on Qt, located on occviewer/QJsonWidget.  The graphic user interface is described by a json file(resoureces/_ui.json).  The step makes UI design easier.

### Supported Plugins

- QLabel
- QFrame: useless, just for testing
- QPushButton: icon and text are defined in (.qss) file
- QLineEdit
- QVBoxLayout: same functions like QVBoxLayout, but not it!
- QHBoxLayout
- QOccWidget

More getWidget plugin expected!

## Collect

```text
https://techoverflow.net/2019/06/14/how-to-export-colored-step-files-in-opencascade/
```

Good-looking Code fragments duplicated from web:

```c++
#include <occutils/ExtendedSTEP.hxx>
#include <occutils/Primitive.hxx>
TopoDS_Shape cube = Primitive::MakeCube(5 /* mm */);
STEP::ExtendedSTEPExporter stepExporter;
stepExporter.AddShapeWithColor(cube, Quantity_NOC_RED);
stepExporter.Write("ColoredCube.step");
```