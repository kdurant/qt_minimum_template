#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QMainWindow>
#include <QSettings>
#include <QLabel>

#include <QUdpSocket>
#include <QTcpSocket>
#include <QNetworkDatagram>
#include <QHostAddress>
#include <QNetworkInterface>

#include "common.h"
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
protected:
    void closeEvent(QCloseEvent *event);
    void timerEvent(QTimerEvent *event);

public:
    struct UserPara
    {
        int width;
    };
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void generateDefaultParameter();
    void initParameter();
    void saveParameter();

    void initUI();
    void udpBind();

    void PlotConfig();
    void userStatusBar();
    void initSignalSlot();

private:
    QStringList read_ip_address();

signals:
    void socketDatagramReady(QByteArray data);

public slots:
    void processPendingDatagram();


private:
    Ui::MainWindow *ui;
    QSettings      *configIni;
    QLabel         *statusLabel;

    QHostAddress deviceIP{QHostAddress("192.168.0.100")};
    quint16      devicePort{8888};
    QStringList  localIP;
    quint16      localPort{6666};
    QUdpSocket  *udpSocket;

    qint32 timer1s;

    QVector<QCustomPlot *> m_UserPlot;

    UserPara m_user_para;
};
#endif  // MAINWINDOW_H
