#include "aboutdialog.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>


AboutDialog::AboutDialog(QWidget *parent)
    : QDialog{parent}
{
    setWindowTitle("About");
    // setFixedSize(200, 250);

    auto layout = new QVBoxLayout{this};

    auto logoLabel = new QLabel{this};
    logoLabel->setPixmap(QPixmap{":/icons/main_icon.png"}.scaled(32, 32));
    logoLabel->setAlignment(Qt::AlignCenter);

    auto titleLabel = new QLabel{"<h2>Gamma corrector</h2>", this};
    titleLabel->setAlignment(Qt::AlignCenter);

    auto versionLabel = new QLabel{QString{"Version: "} + PROGRAMM_VERSION, this};
    auto companyLabel = new QLabel{"Developer: Terentev Aleksandr", this};
    auto dateLabel = new QLabel{QString{"Date: "} + PROGRAMM_DATE, this};

    auto closeButton = new QPushButton{"OK", this};
    connect(closeButton, &QPushButton::clicked, this, &QDialog::accept);

    auto githubIconLabel = new QLabel{this};
    githubIconLabel->setPixmap(QPixmap{":/icons/github.png"}.scaled(20, 20));
    auto githubRefLabel = new QLabel{this};
    githubRefLabel->setText(R"(<a href="https://github.com/Sasha7291/GammaCorrector.git">GitHub</a>)");
    githubRefLabel->setTextFormat(Qt::RichText);
    githubRefLabel->setOpenExternalLinks(true);
    auto layout_1 = new QHBoxLayout;
    layout_1->addWidget(githubIconLabel);
    layout_1->addWidget(githubRefLabel, 1);

    layout->addWidget(logoLabel);
    layout->addWidget(titleLabel);
    layout->addWidget(versionLabel);
    layout->addWidget(companyLabel);
    layout->addWidget(dateLabel);
    layout->addLayout(layout_1);
    layout->addWidget(closeButton);

    setLayout(layout);
    setWindowFlag(Qt::MSWindowsFixedSizeDialogHint, true);
}
