#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    statusLabel(new QLabel())
{
    ui->setupUi(this);

    configIni = new QSettings("./config.ini", QSettings::IniFormat);
    generateDefaultParameter();
    initParameter();

    initUI();
    PlotConfig();
    udpBind();

    userStatusBar();
    initSignalSlot();

    timer1s = startTimer(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::generateDefaultParameter()
{
    QFileInfo fileInfo("./config.ini");
    if(!fileInfo.exists())
    {
        QFile file("./config.ini");
        file.open(QIODevice::WriteOnly);
        file.write("\r\n[System]\r\n");
        file.write("; release or debug\r\n");
        file.write("mode=debug\r\n");
        file.write("winth=400\r\n");

        file.close();
    }
}

// configIni->value("System/oceanPort").toString()
// configIni->value("System/oceanPort").toInt()
void MainWindow::initParameter()
{
    if(configIni->value("System/mode").toString() == "debug")
    {
        localIP.append("127.0.0.1");
        QMessageBox::information(this, "通知", "当前为调试模式, IP addr:127.0.0.1");
        deviceIP = QHostAddress("127.0.0.1");
    }
    else
        localIP = read_ip_address();

    m_user_para.width = configIni->value("System/width").toUInt();
}

// configIni->setValue("Laser/freq", 1111);
void MainWindow::saveParameter()
{
    configIni->setValue("System/RadarType", "land");
    configIni->setValue("Laser/freq", 1111);
}

void MainWindow::initUI()
{
    setWindowTitle("xxx软件");
}

void MainWindow::udpBind()
{
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::Any, localPort);
    udpSocket->setSocketOption(QAbstractSocket::ReceiveBufferSizeSocketOption, 1024 * 1024 * 1);
}

void MainWindow::PlotConfig()
{
    QVBoxLayout *widget1VBox;
    widget1VBox = new QVBoxLayout;
    ui->frame_main->setStyleSheet("QWidget#widget{background-color:gray;}");
    ui->frame_main->setLayout(widget1VBox);
    for(int i = 0; i < 2; ++i)
    {
        QCustomPlot *customPlot = new QCustomPlot;
        m_UserPlot.append(customPlot);
        widget1VBox->addWidget(customPlot, 2);
    }
}

void MainWindow::userStatusBar()
{
    statusLabel->setText("软件版本：" + QString(SOFT_VERSION) + "_" + GIT_DATE + "_" + GIT_HASH);
    ui->statusbar->addPermanentWidget(statusLabel);
}

void MainWindow::initSignalSlot()
{
    //    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagram()));
    connect(udpSocket, &QUdpSocket::readyRead, this, [this]() {
        QByteArray datagram;
        int        len;
        while(udpSocket->hasPendingDatagrams())
        {
            len = udpSocket->pendingDatagramSize();
            datagram.resize(len);
            udpSocket->readDatagram(datagram.data(), datagram.size());
            emit socketDatagramReady(datagram);
        }
    });
}

QStringList MainWindow::read_ip_address()
{
    QStringList ips;
    QString     ip;

    const QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();

    QList<QNetworkAddressEntry> entrys;
    //    foreach(QNetworkInterface interface, interfaces)
    for(int i = 0; i < interfaces.size(); i++)
    {
        entrys = interfaces.at(i).addressEntries();
        for(auto entery : entrys)
        {
            switch(entery.ip().protocol())
            {
                case QAbstractSocket::IPv4Protocol:
                    ip = entery.ip().toString();
                    if(ip.contains("192.168."))
                        ips.append(ip);
                    break;
                case QAbstractSocket::IPv6Protocol:
                    break;
                case QAbstractSocket::AnyIPProtocol:
                    break;
                case QAbstractSocket::UnknownNetworkLayerProtocol:
                    break;
            }
        }
    }

    std::sort(ips.begin(), ips.end());
    return ips;
}

void MainWindow::processPendingDatagram()
{
    QByteArray datagram;
    int        len;
    while(udpSocket->hasPendingDatagrams())
    {
        len = udpSocket->pendingDatagramSize();
        datagram.resize(len);
        udpSocket->readDatagram(datagram.data(), datagram.size());

        // dispatch->parserFrame(datagram);
        emit socketDatagramReady(datagram);
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    //    saveParameter();
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    if(timer1s == event->timerId())
    {
    }
}
