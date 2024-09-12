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

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    tableWidget->setColumnCount(0);
    tableWidget->setRowCount(0);
    layout->addWidget(tableWidget);

    setCentralWidget(centralWidget);

    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *fileMenu = new QMenu("File", menuBar);
    QAction *openAction = new QAction("Open CSV", fileMenu);
    fileMenu->addAction(openAction);
    menuBar->addMenu(fileMenu);
    setMenuBar(menuBar);

    connect(openAction, &QAction::triggered, this, &MainWindow::openCSVFile);

    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
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

        tableWidget->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
    }
}