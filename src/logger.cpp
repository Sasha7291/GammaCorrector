#include "logger.h"

#include <QDateTime>
#include <QDir>
#include <QErrorMessage>
#include <QFile>
#include <QtLogging>


std::unique_ptr<QFile> Logger::logFile_ = nullptr;
const QString Logger::_DIR_NAME_ = QDir::currentPath() + "/logs/";
const QString Logger::_MESSAGE_PATTERN_ = "[%{time yyyy.MM.dd h:mm:ss.zzz} %{time process} c %{type}] %{file}::%{function}:%{line} - %{message}\n";

void Logger::startLogging(const LogMode mode)
{
    if (mode == LogToFile)
    {
        if (!QDir(_DIR_NAME_).exists())
            QDir().mkdir(_DIR_NAME_);

        logFile_ = std::make_unique<QFile>(
            Logger::_DIR_NAME_
                + QDateTime::currentDateTime().toString("dd.MM.yyyy_hh-mm-ss_")
                + "log_file.txt"
        );
        logFile_->open(QFile::WriteOnly);

        qInstallMessageHandler(logToFile);
    }
    else if (mode == LogToConsole)
    { ; }

    qSetMessagePattern(_MESSAGE_PATTERN_);
}

void Logger::logToFile(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    auto errorMessage = new QErrorMessage;
    errorMessage->showMessage(msg);

    QTextStream out(logFile_.get());
    out << qFormatLogMessage(type, context, msg);
    out.flush();
}
