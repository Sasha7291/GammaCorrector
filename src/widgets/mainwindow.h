#pragma once

#include <QMainWindow>


class MainWindow_Ui;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr) noexcept;
    ~MainWindow() noexcept;

private:
    std::unique_ptr<MainWindow_Ui> ui;

};
