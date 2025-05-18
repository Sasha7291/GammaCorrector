#pragma once

#include <QMessageBox>
#include <QVector>


namespace utils
{

template<class T>
concept Number = std::integral<T> || std::floating_point<T>;

[[nodiscard]] QString getOpenFileName() noexcept;
[[nodiscard]] QString getSaveFileName() noexcept;

QString sign(Number auto value) noexcept
{
    return (value > static_cast<decltype(value)>(0)) ? "+" : "-";
}

template<std::ranges::random_access_range T, std::ranges::random_access_range K>
[[nodiscard]] T stdVectorToQVector(const K &data) noexcept
{
    if constexpr (Number<typename T::value_type>)
    {
        return T(data.cbegin(), data.cend());
    }
    else
    {
        T result;
        result.reserve(data.size());

        for (const auto &line : data)
            result << stdVectorToQVector<typename T::value_type>(line);

        return result;
    }
}

template<std::ranges::random_access_range T, std::ranges::random_access_range K>
[[nodiscard]] T qVectorToStdVector(const K &data) noexcept
{
    if constexpr (Number<typename T::value_type>)
    {
        return T(data.cbegin(), data.cend());
    }
    else
    {
        T result;
        result.reserve(data.size());

        for (const auto &line : data)
            result.push_back(qVectorToStdVector<typename T::value_type>(line));

        return result;
    }
}

template<Number T>
[[nodiscard]] QVector<QVector<T>> transposeVector(const QVector<QVector<T>> &data)
{
    QVector<QVector<T>> result(data[0].size(), QVector<T>(data.size()));

    for (int i = 0; i < data.size(); ++i)
        for (int j = 0; j < data[0].size(); ++j)
            result[j][i] = data[i][j];

    return result;
}

}
