#include "application.h"

#include "mainwindow.h"
#include "utils.h"

#include <QSharedMemory>
#include <QSystemSemaphore>


Application::Application(int &argc, char **argv)
    : QApplication{argc, argv}
    , mainWindow_{new MainWindow}
{
    setApplicationName("Gamma correction");
}

int Application::execute()
{
    QSystemSemaphore semaphore("GCSemaphore", 1, QSystemSemaphore::Open);
    semaphore.acquire();

    bool isRunning = false;
    QSharedMemory sharedMemory("GMSharedMemory");
    if (sharedMemory.attach())
        isRunning = true;
    else
        sharedMemory.create(1);

    semaphore.release();

    if (isRunning)
    {
        utils::showWarningMessage("Application is already running");
        return 1;
    }

    mainWindow_->showMaximized();
    return exec();
}
