interface QRect {
    x: number; y: number; width: number; height: number;
}

interface QWidget {
    show(): void;
    resize(width: number, height: number): void;
    geometry(): QRect;
    setGeometry(rect: QRect): void;
}

interface QLabel extends QWidget {
    setText(text: string): void;
    text(): string;
}

interface QApplicationWindow extends QWidget {
    createWidget(type: string, id: string): QWidget | QLabel;
}

declare var qApplicationWindow: QApplicationWindow;