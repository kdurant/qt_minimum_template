#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QTime>
#include <QMessageBox>

const QString logFilePath = "debug.log";
// redirect qDebug to file
void customMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QHash<QtMsgType, QString> msgLevelHash({{QtDebugMsg, "Debug"}, {QtInfoMsg, "Info"}, {QtWarningMsg, "Warning"}, {QtCriticalMsg, "Critical"}, {QtFatalMsg, "Fatal"}});
    QByteArray                localMsg         = msg.toLocal8Bit();
    QTime                     time             = QTime::currentTime();
    QString                   formattedTime    = time.toString("hh:mm:ss.zzz");
    QByteArray                formattedTimeMsg = formattedTime.toLocal8Bit();
    QString                   logLevelName     = msgLevelHash[type];
    QByteArray                logLevelMsg      = logLevelName.toLocal8Bit();
#ifdef LOG2FILE
    QString txt = QString("%1 %2: %3 (%4)\n").arg(formattedTime, logLevelName, msg, context.file);
    QFile   outFile(logFilePath);
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << txt << "\n";
    outFile.close();
#endif
    fprintf(stderr, "%s %s: %s (%s:%u, %s)\n", formattedTimeMsg.constData(), logLevelMsg.constData(), localMsg.constData(), context.file, context.line, context.function);
    fflush(stderr);

    if(type == QtFatalMsg)
        abort();
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(customMessageOutput);

    QApplication a(argc, argv);
    QFile        qss(":/qss/ui.css");
    a.setWindowIcon(QIcon(":qss/app_icon.ico"));
    //    QFile qss("basic.qss");
    if(qss.open(QFile::ReadOnly))
    {
        //a.setWindowIcon(QIcon(":/qss/communication.ico"));
        a.setStyleSheet(qss.readAll());
    }
    else
        QMessageBox::warning(NULL, "warning", "没有主题文件");

    QFont font;
    font.setPixelSize(14);
    a.setFont(font);

    MainWindow w;
    w.show();
    return a.exec();
}
