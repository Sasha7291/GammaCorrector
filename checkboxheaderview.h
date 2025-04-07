#pragma once

#include <QHeaderView>


class CheckBoxHeaderView : public QHeaderView
{
    Q_OBJECT

public:
    CheckBoxHeaderView(Qt::Orientation orientation, QWidget *parent = nullptr) noexcept;
    ~CheckBoxHeaderView() noexcept = default;

    [[nodiscard]] bool columnChecked(int column) const noexcept;
    void setColumnCheckable(int column, bool checkable = true) noexcept;

signals:
    void columnSectionClicked(int logicalIndex, bool checked);

protected:
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const override;

private:
    QMap<int, bool> columnCheckedMap_;

};

