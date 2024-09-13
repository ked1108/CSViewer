#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/resources/icon.png"));
    MainWindow mainWindow;
    if (argc > 1) {
        QString csvFilePath = argv[1];
        mainWindow.openCSVFileArg(csvFilePath);  // Open the CSV file
    }
    mainWindow.show();

    return app.exec();
}
