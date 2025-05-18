#include "application.h"

#include "logger.h"
#include "mainwindow.h"

#include <QSharedMemory>
#include <QSystemSemaphore>


Application::Application(int &argc, char **argv)
    : QApplication{argc, argv}
    , mainWindow_{new MainWindow}
{
    setApplicationName(PROGRAMM_NAME);
    setApplicationVersion(PROGRAMM_VERSION);
    setApplicationDisplayName(PROGRAMM_NAME);
}

int Application::execute()
{
    Logger::startLogging(Logger::LogToFile);

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
        qCritical() << "Application is already running";
        return 1;
    }

    mainWindow_->showMaximized();
    return exec();
}
