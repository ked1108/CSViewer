//
// Created by kedar on 9/12/24.
//
#include "mainwindow.h"
#include "parser.h"
#include <QMenuBar>
#include <QAction>
#include <QFileDialog>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QMimeData>
#include <QDrag>
#include <QApplication>
#include <QTableWidgetItem>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), tableWidget(new QTableWidget(this)) {
    setupUI();
}

MainWindow::~MainWindow() {
    // Destructor
}

void MainWindow::setupUI() {
    setWindowTitle("CSViewer");
    resize(800, 600);

    // Create a central widget and a layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    // Create and set up the table widget
    tableWidget->setColumnCount(0);
    tableWidget->setRowCount(0);
    layout->addWidget(tableWidget);

    setCentralWidget(centralWidget);

    // Create a menu bar with an 'Open' action
    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *fileMenu = new QMenu("File", menuBar);
    QAction *openAction = new QAction("Open CSV", fileMenu);
    fileMenu->addAction(openAction);
    menuBar->addMenu(fileMenu);
    setMenuBar(menuBar);

    connect(openAction, &QAction::triggered, this, &MainWindow::openCSVFile);

    // Set the resizing behavior of columns
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);

    // Enable drag and drop
    tableWidget->setDragEnabled(true);
    tableWidget->setAcceptDrops(true);
    tableWidget->setDropIndicatorShown(true);
    tableWidget->setDefaultDropAction(Qt::MoveAction);
}

void MainWindow::openCSVFile() {
    QString filename = QFileDialog::getOpenFileName(this, "Open CSV File", "", "CSV Files (*.csv)");
    if (!filename.isEmpty()) {
        std::vector<std::vector<std::string>> data = parseCSV(filename.toStdString());
        populateTable(data);
    }
}

void MainWindow::populateTable(const std::vector<std::vector<std::string>> &data) {
    tableWidget->setRowCount(data.size());
    if (!data.empty()) {
        tableWidget->setColumnCount(data[0].size());

        for (int row = 0; row < data.size(); ++row) {
            for (int col = 0; col < data[row].size(); ++col) {
                QTableWidgetItem *item = new QTableWidgetItem(QString::fromStdString(data[row][col]));
                tableWidget->setItem(row, col, item);
            }
        }

        // Resize columns based on the selected resize mode
        tableWidget->horizontalHeader()->resizeSections(QHeaderView::Interactive);
    }
}

QMimeData *MainWindow::mimeData(const QList<QTableWidgetItem *> items) const {
    QMimeData *mimeData = new QMimeData;
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);

    foreach (QTableWidgetItem *item, items) {
        dataStream << item->row() << item->column() << item->text();
    }

    mimeData->setData("application/x-table-widget-item", itemData);
    return mimeData;
}

void MainWindow::dropEvent(QDropEvent *event) {
    if (event->mimeData()->hasFormat("application/x-table-widget-item")) {
        QByteArray itemData = event->mimeData()->data("application/x-table-widget-item");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        int row, column;
        QString text;

        while (!dataStream.atEnd()) {
            dataStream >> row >> column >> text;
            QTableWidgetItem *item = new QTableWidgetItem(text);
            tableWidget->setItem(row, column, item);
        }

        event->acceptProposedAction();
    }
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasFormat("application/x-table-widget-item")) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::dragMoveEvent(QDragMoveEvent *event) {
    if (event->mimeData()->hasFormat("application/x-table-widget-item")) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::dragLeaveEvent(QDragLeaveEvent *event) {
    // Handle when the drag leaves the table widget
    event->accept();
}
