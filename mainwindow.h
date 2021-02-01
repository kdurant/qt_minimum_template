#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QMainWindow>
#include <QSettings>
#include <QLabel>

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
    QString         softwareVer{SOFT_VERSION};
};
#endif  // MAINWINDOW_H
