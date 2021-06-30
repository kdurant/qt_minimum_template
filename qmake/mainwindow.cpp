#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    statusLabel(new QLabel()),
    thread(new QThread())
{
    ui->setupUi(this);

    initParameter();
    initUI();
    userStatusBar();
    initSignalSlot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initParameter()
{
    QFileInfo fileInfo("./config.ini");
    if(!fileInfo.exists())
    {
        QFile file("./config.ini");
        file.open(QIODevice::WriteOnly);
        file.write("[System]\r\n");
        file.write("; release, debug, debug_network\r\n");
        file.write("mode = debug_network\r\n\r\n");
        file.close();
    }

    configIni = new QSettings("./config.ini", QSettings::IniFormat);
    //    sysPara.mode              = configIni->value("System/mode").toString();
}

void MainWindow::saveParameter()
{
    //    configIni->setValue("System/RadarType", "land");
    //    configIni->setValue("Laser/freq", 1111);
}

void MainWindow::initUI()
{
    setWindowTitle("xxx软件");
}

void MainWindow::userStatusBar()
{
    statusLabel->setText("软件版本：" + QString(SOFT_VERSION) + "_" + QString(GIT_DATE) + "_" + QString(GIT_HASH));
    ui->statusbar->addPermanentWidget(statusLabel);
}

void MainWindow::initSignalSlot()
{
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    //    saveParameter();
}
