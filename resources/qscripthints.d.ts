interface QObject {
    readonly objectName: string;
}

interface QVariantObject {
}

interface QPoint extends QVariantObject {
    x: number;
    y: number;
}

interface QPointConstructor {
    readonly prototype: QPoint;

    new(): QPoint;

    new(x: number, y: number): QPoint;
}

declare var QPoint: QSizeConstructor;

interface QSize extends QVariantObject {
    width: number;
    height: number;
}

interface QSizeConstructor {
    readonly prototype: QSize;

    new(): QSize;

    new(width: number, height: number): QSize;
}

declare var QSize: QSizeConstructor;

interface QRect extends QVariantObject {
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


interface QVariant<T extends QVariantObject> {
}

declare function typecast(obj: QVariant<QVariantObject>): QSize | QRect | QPoint;

declare function typecast(type: string, obj: QVariantObject): QVariant<QVariantObject>;

interface QWidget {
    show(): void;

    hide(): void;

    setGeometry(rect: QRect): void;
}

interface QLabel extends QWidget {
    text: string;
    alignment: number;

    setText(text: string): void;
}

interface QColorLabel extends QLabel {
}

interface QAbstractButton extends QWidget {
    text: string;

    setText(text: string): void;
}

interface QPushButton extends QAbstractButton {
}

interface QToolButton extends QAbstractButton {
}

interface QNavigator extends QWidget {
}

interface QLineEdit extends QWidget {
    text: string;

    setText(text: string): void;
}

interface QLinearSpinner extends QWidget {
}

interface QOccRender {
    importModelFile(filename: string): void;

    makeBevel(): void;

    makeCube(): void;

    switchFrontView(): void;

    switchTopView(): void;

    switchLeftView(): void;
}

interface QOccViewer extends QWidget {
    qRenderThread(): QOccRender;
}

interface QApplicationWindow extends QWidget {
    findChild(objectName: string): QWidget;

    setWindowTitle(title: string): void;

    setWindowIcon(filename: string): void;

    place(w: QWidget, x: QVariant<QVariantObject>): void;

    setSize(w: QWidget, size: QVariant<QVariantObject>): void;

    loadStylesheet(filename: string): void;

    loadFont(filename: string): number;

    setDefaultFont(fontFamily: string): void;

    qLabel(id: string): QLabel;

    qColorLabel(id: string): QColorLabel;

    qPushButton(id: string): QPushButton;

    qToolButton(id: string): QToolButton;

    qNavigator(id: string): QNavigator;

    qLineEdit(id: string): QLineEdit;

    qLinearSpinner(id: string): QLinearSpinner;

    qOccViewer(id: string): QOccViewer;

    setLabelText(label: QLabel, text: string): void;

    setWidgetGeometry(widget: QWidget, geo: QVariant<QVariantObject>): void;

    setWidgetVisible(widget: QWidget, visible: boolean): void;

    setButtonText(button: QAbstractButton, text: string): void;

    setButtonIcon(button: QAbstractButton, icon: string): void;

    setButtonIconSize(button: QAbstractButton, size: QSize): void;

    setLineEditText(edit: QLineEdit, text: string): void;

    setLineEditPlaceholder(edit: QLineEdit, text: string): void;

    updateOcc(occ: QOccViewer): void;

    createOcc(occ: QOccViewer): void;

}

declare var qApplicationWindow: QApplicationWindow;