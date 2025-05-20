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

QStringList getOpenFileNames() noexcept
{
    static auto fileDir = QDir::currentPath();
    const auto paths = QFileDialog::getOpenFileNames(
        nullptr,
        "Open files",
        fileDir,
        "CSV (*.csv)"
    );

    if (!paths.isEmpty())
        fileDir = paths[0].sliced(0, paths[0].lastIndexOf("/"));

    return paths;
}

}
