#pragma once

#include <QObject>

#include <memory>


class QFile;
class QString;

class Logger
{
    Q_GADGET

public:
    enum LogMode : bool
    {
        LogToConsole,
        LogToFile
    };
    Q_ENUM(LogMode)

    Logger() = delete;
    ~Logger() = delete;

    Logger(const Logger &) = delete;
    Logger(Logger &&) = delete;
    Logger &operator=(const Logger &) = delete;
    Logger &operator=(Logger &&) = delete;

    static void startLogging(const LogMode mode);

private:
    static void logToFile(QtMsgType type, const QMessageLogContext &context, const QString &msg);

    static std::unique_ptr<QFile> logFile_;
    static const QString _DIR_NAME_;
    static const QString _MESSAGE_PATTERN_;

};
