#include "utils.h"

#include <QDir>
#include <QFileDialog>


namespace utils
{

QString getOpenFileName() noexcept
{
    static auto fileDir = QDir::currentPath();
    const auto path = QFileDialog::getOpenFileName(
        nullptr,
        "Load file",
        fileDir,
        "CSV (*.csv)"
    );

    if (!path.isEmpty())
        fileDir = path.sliced(0, path.lastIndexOf("/"));

    return path;
}

QString getSaveFileName() noexcept
{
    static auto fileDir = QDir::currentPath();
    const auto path = QFileDialog::getSaveFileName(
        nullptr,
        "Save file",
        fileDir,
        "CSV (*.csv)"
    );

    if (!path.isEmpty())
        fileDir = path.sliced(0, path.lastIndexOf("/"));

    return path;
}

void showWarningMessage(const QString &message) noexcept
{
    QMessageBox::warning(
        nullptr,
        "Warning!",
        message,
        QMessageBox::Ok,
        QMessageBox::NoButton
    );
}

}
