#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QMainWindow>
#include <QSettings>
#include <QLabel>

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
    void PlotConfig();
    void userStatusBar();
    void initSignalSlot();

private:
    Ui::MainWindow *ui;
    QSettings      *configIni;
    QLabel         *statusLabel;

    QVector<QCustomPlot *> m_UserPlot;

    UserPara m_user_para;
};
#endif  // MAINWINDOW_H
