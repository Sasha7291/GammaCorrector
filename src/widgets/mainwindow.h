#pragma once

#include <QMainWindow>

class MainWindow_Ui;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void approximate();
    void loadData();
    void saveData();

private:
    std::unique_ptr<MainWindow_Ui> ui;

};
