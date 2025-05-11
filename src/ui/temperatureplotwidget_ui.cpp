#include "temperatureplotwidget_ui.h"

#include "aspectratiocontainerwidget.h"
#include "mdiarea.h"
#include "temperatureplotwidget.h"

#include <QHBoxLayout>
#include <QMenu>


TemperaturePlotWidget_Ui::TemperaturePlotWidget_Ui(TemperaturePlotWidget *parent)
    : plot{new Plot{parent}}
    , parent_{parent}
    , settingsWindow{new TemperaturePlotSettingsWidget{parent}}
{
    auto layout = new QHBoxLayout{parent};
    layout->addWidget(new AspectRatioContainerWidget{plot, 4.0f / 3.0f, 400, parent}, 1);
    parent->setLayout(layout);
}

void TemperaturePlotWidget_Ui::showContextMenu(const QPoint &pos) const
{
    QMenu menu{parent_};

    menu.addAction(QIcon{":/icons/settings.png"}, "Settings", parent_, [this]() -> void {
        showSettingsWindow();
    });

    menu.exec(parent_->mapToGlobal(pos));
}

void TemperaturePlotWidget_Ui::showSettingsWindow() const
{
    auto parentSubWindow = qobject_cast<QMdiSubWindow *>(parent_->parentWidget());
    auto settingsSubWindow = qobject_cast<MdiSubWindow *>(settingsWindow->parentWidget());

    if (parentSubWindow->isMaximized())
    {
        if (settingsSubWindow != nullptr && settingsWindow->isVisible())
            settingsSubWindow->close();

        settingsWindow->setWindowFlag(Qt::Window, true);
        settingsWindow->show();
        auto position = (parent_->size() - settingsWindow->size()) / 2;
        settingsWindow->move(parent_->mapToGlobal(QPoint{position.width(), position.height()}));
    }
    else
    {
        auto subWindow = (parent_ == settingsWindow->parentWidget())
            ? MdiArea::openSubWindow(settingsWindow, "Settings [" + parent_->windowTitle() + "]", false)
            : settingsSubWindow;

        settingsWindow->setWindowFlag(Qt::Window, false);
        auto position = (MdiArea::instance()->size() - subWindow->size()) / 2;
        subWindow->move(MdiArea::instance()->mapTo(
            MdiArea::instance(),
            QPoint{position.width(), position.height()}
        ));

        parent_->disconnect(parentSubWindow, &QObject::destroyed, subWindow, nullptr);
        parent_->connect(parentSubWindow, &QObject::destroyed, subWindow, &QMdiSubWindow::close);
    }

    parent_->disconnect(parentSubWindow, &QMdiSubWindow::windowStateChanged, parent_, nullptr);
    parent_->connect(
        parentSubWindow, &QMdiSubWindow::windowStateChanged,
        parent_, [this](Qt::WindowStates oldState, Qt::WindowStates newState) -> void {
            if (newState & Qt::WindowMaximized && !(oldState & Qt::WindowMaximized)
                || !(newState & Qt::WindowMaximized) && oldState & Qt::WindowMaximized)
                showSettingsWindow();
        }
    );
}
