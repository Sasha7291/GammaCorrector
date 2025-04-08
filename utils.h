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

// template<class K, class T>
// [[nodiscard]] QVector<K> stdVectorToQVector(const std::vector<T> &data) noexcept
// {
//     if constexpr (Number<T>)
//     {
//         return QVector(data.cbegin(), data.cend());
//     }
//     else
//     {
//         QVector<K> result;
//         result.reserve(data.size());

//         for (const auto &line : data)
//             result << stdVectorToQVector<K, T>(line);

//         return result;
//     }
// }

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

// template<class K, class T>
// [[nodiscard]] std::vector<K> qVectorToStdVector(const QVector<T> &data) noexcept
// {
//     if constexpr (Number<T>)
//     {
//         return std::vector(data.begin(), data.end());
//     }
//     else
//     {
//         std::vector<K> result;
//         result.reserve(data.size());

//         for (const auto &line : data)
//             result.push_back(qVectorToStdVector<K, T>(line));

//         return result;
//     }
// }

}
