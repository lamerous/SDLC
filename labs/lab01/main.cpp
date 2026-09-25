#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    window.setWindowTitle("Калькулятор населения мира (Вариант 7)");
    window.show();

    return app.exec();
}

#include "main.moc"