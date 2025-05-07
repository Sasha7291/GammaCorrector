#pragma once

#include <QWidget>


class SubWindowWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SubWindowWidget(QWidget *parent = nullptr);
    virtual ~SubWindowWidget() noexcept = default;

    void setSize(const QSize &size);
    void setSize(int w, int h);

protected:
    void resizeEvent(QResizeEvent *event) override;
    QSize sizeHint() const override;

private:
    bool manualResize_;

};
