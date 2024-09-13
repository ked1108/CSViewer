//
// Created by kedar on 9/12/24.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDragLeaveEvent>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void openCSVFileArg(const QString &filePath);
    private slots:
        void openCSVFile();

private:
    void setupUI();
    void populateTable(const std::vector<std::vector<std::string>> &data);

    QTableWidget *tableWidget;
};

#endif // MAINWINDOW_H
