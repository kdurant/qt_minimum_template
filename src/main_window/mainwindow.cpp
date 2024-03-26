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

    userStatusBar();
    initSignalSlot();
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
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    saveParameter();
}
