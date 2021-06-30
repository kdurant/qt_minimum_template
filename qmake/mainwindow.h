#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QMainWindow>
#include <QSettings>
#include <QLabel>

#include "common.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    struct _sys_para_
    {
        QString mode;
    } sysPara;

protected:
    void closeEvent(QCloseEvent *event);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initParameter();
    void saveParameter();

    void initUI();
    void userStatusBar();
    void initSignalSlot();

private:
    Ui::MainWindow *ui;
    QSettings *     configIni;
    QLabel *        statusLabel;

    QThread *thread;
};
#endif  // MAINWINDOW_H
