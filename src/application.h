#pragma once

#include <QApplication>
#include <QPointer>


class MainWindow;

class Application : public QApplication
{
    Q_OBJECT

public:
    explicit Application(int &argc, char **argv);
    ~Application() = default;

    int execute();

private:
    QPointer<MainWindow> mainWindow_;

};
