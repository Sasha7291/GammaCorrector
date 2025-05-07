#pragma once

#include <QWidget>


class QBoxLayout;

class AspectRatioContainerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AspectRatioContainerWidget(
        QWidget *content,
        float aspectRatio = 16.0f / 9.0f,
        int minimumWidth = 0,
        QWidget *parent = nullptr
    );
    ~AspectRatioContainerWidget() = default;

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    QBoxLayout *layout_;
    QWidget *widget_;
    float aspectRatio_;

};
