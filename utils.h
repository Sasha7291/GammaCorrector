#pragma once

#include <QMessageBox>
#include <QVector>


namespace utils
{

template<class T>
concept Number = std::integral<T> || std::floating_point<T>;

[[nodiscard]] QString getOpenFileName() noexcept;
[[nodiscard]] QString getSaveFileName() noexcept;
void showWarningMessage(const QString &message) noexcept;

template<class T>
[[nodiscard]] QVector<T> stdVectorToQVector(const std::vector<T> &data) noexcept
{
    return QVector(data.cbegin(), data.cend());
}

template<class T>
[[nodiscard]] QVector<QVector<T>> stdVectorToQVector(const std::vector<std::vector<T>> &data) noexcept
{
    QVector<QVector<T>> result;
    result.reserve(data.size());

    for (const auto &line : data)
        result << QVector<T>(line.cbegin(), line.cend());

    return result;
}

template<class T>
[[nodiscard]] std::vector<T> qVectorToStdVector(const QVector<T> &data) noexcept
{
    return std::vector(data.begin(), data.end());
}

template<class T>
[[nodiscard]] std::vector<std::vector<T>> qVectorToStdVector(const QVector<QVector<T>> &data) noexcept
{
    std::vector<std::vector<T>> result;
    result.reserve(data.size());

    for (const auto &line : data)
        result.push_back(std::vector<T>(line.cbegin(), line.cend()));

    return result;
}

}
