#pragma once

#include <QTableWidgetItem>


class TableWidgetItem : public QTableWidgetItem
{

public:
    explicit TableWidgetItem(double value) noexcept;
    ~TableWidgetItem() noexcept = default;

};
