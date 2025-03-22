#pragma once

#include <QMainWindow>

class MainWindow_Ui;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void warningMessageHandler();

    std::unique_ptr<MainWindow_Ui> ui;

};
