#include <QtCore>

#define CONCAT_(x, y) x##y
#define CONCAT(x, y) CONCAT_(x, y)

#define CHECKTIME(x)                     \
    QElapsedTimer CONCAT(sb_, __LINE__); \
    CONCAT(sb_, __LINE__).start();       \
    x qDebug() << __FUNCTION__ << ":" << __LINE__ << " Elapsed time: " << CONCAT(sb_, __LINE__).elapsed() << " ms."

class Common
{
public:
    /**
     * @brief 整型数据转换为length=4的QByteArray
     * @param data
     * @return 
     */
    static QByteArray int2ba(quint32 data)
    {
        QByteArray ba;
        ba.resize(4);
        ba[3] = static_cast<int8_t>(0x000000ff & data);
        ba[2] = static_cast<int8_t>((0x0000ff00 & data) >> 8);
        ba[1] = static_cast<int8_t>((0x00ff0000 & data) >> 16);
        ba[0] = static_cast<int8_t>((0xff000000 & data) >> 24);
        return ba;
    }

    static quint32 ba2int(QByteArray ba)
    {
        quint32 ret = ba.toHex().toUInt(nullptr, 16);
        return ret;
    }

    static void sleepWithoutBlock(quint32 ms)
    {
        QEventLoop waitLoop;
        QTimer::singleShot(ms, &waitLoop, &QEventLoop::quit);
        waitLoop.exec();
    }
};
