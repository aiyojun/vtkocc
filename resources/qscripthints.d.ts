interface QObject {
    readonly objectName: string;
}

interface QPoint {
    x: number;
    y: number;
}

interface QPointConstructor {
    readonly prototype: QPoint;

    new(): QPoint;

    new(x: number, y: number): QPoint;
}

declare var QPoint: QSizeConstructor;

interface QSize {
    width: number;
    height: number;
}

interface QSizeConstructor {
    readonly prototype: QSize;

    new(): QSize;

    new(width: number, height: number): QSize;
}

declare var QSize: QSizeConstructor;

interface QRect {
    x: number;
    y: number;
    width: number;
    height: number;
}

interface QRectConstructor {
    readonly prototype: QRect;

    new(): QRect;

    new(x: number, y: number, width: number, height: number): QRect;
}

declare var QRect: QRectConstructor;

type QBasicObject = QPoint | QSize | QRect;

interface QVariant {
}

declare function typecast(obj: QVariant): QSize | QRect;

declare function typecast(type: string, obj: QBasicObject): QVariant;

interface QWidget {
    show(): void;

    hide(): void;

    setGeometry(rect: QRect): void;
}

interface QLabel extends QWidget {
    setText(text: string): void;
}

interface QColorLabel extends QLabel {
}

interface QAbstractButton extends QWidget {
}

interface QPushButton extends QAbstractButton {
}

interface QToolButton extends QAbstractButton {
}

interface QNavigator extends QWidget {
}

interface QLineEdit extends QWidget {
}

interface QApplicationWindow extends QWidget {
    findChild(s: string): QWidget;

    place(w: QWidget, x: QVariant): void;

    loadStylesheet(filename: string): void;

    loadFont(filename: string): number;

    setDefaultFont(fontFamily: string): void;

    qLabel(id: string): QLabel;

    qColorLabel(id: string): QColorLabel;

    qPushButton(id: string): QPushButton;

    qToolButton(id: string): QToolButton;

    qNavigator(id: string): QNavigator;

    qLineEdit(id: string): QLineEdit;

    setLabelText(label: QLabel, text: string): void;

    setWidgetGeometry(widget: QWidget, geo: QRect): void;

    setWidgetVisible(widget: QWidget, visible: boolean): void;

    setButtonText(button: QAbstractButton, text: string): void;

    setButtonIcon(button: QAbstractButton, icon: string): void;

    setButtonIconSize(button: QAbstractButton, size: QSize): void;

    setLineEditText(edit: QLineEdit, text: string): void;

    setLineEditPlaceholder(edit: QLineEdit, text: string): void;
}

declare var qApplicationWindow: QApplicationWindow;