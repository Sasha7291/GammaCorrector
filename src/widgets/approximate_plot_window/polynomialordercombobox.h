#pragma once

#include <QComboBox>


class PolynomialOrderComboBox : public QComboBox
{
    Q_OBJECT

public:
    explicit PolynomialOrderComboBox(QWidget *parent = nullptr) noexcept;
    ~PolynomialOrderComboBox() noexcept = default;

    [[nodiscard]] std::size_t currentPolynomialOrder() const noexcept;
    void setCurrentPolynomialOrder(std::size_t order) noexcept;
    void setMaximumPolynomialOrder(std::size_t order);

signals:
    void currentOrderChanged(std::size_t order);

};
