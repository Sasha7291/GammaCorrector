#pragma once

#include <QHeaderView>


class CheckBoxHeaderView : public QHeaderView
{
    Q_OBJECT

public:
    CheckBoxHeaderView(Qt::Orientation orientation, QWidget *parent = nullptr) noexcept;
    ~CheckBoxHeaderView() noexcept = default;

    [[nodiscard]] bool isCheckable(int index) const noexcept;
    [[nodiscard]] bool isChecked(int index) const noexcept;
    void setCheckable(int index, bool checkable = true) noexcept;
    void setChecked(int index, bool checked = true) noexcept;

signals:
    void sectionChecked(int index, bool checked);

protected:
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const override;

private:
    QMap<int, bool> checkedMap_;

};

