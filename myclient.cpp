#include "myclient.h"
#include <QWidget>
#include <QMessageBox>

const QString MyClient::constNameUnknown = QString(".Unknown");

MyClient::MyClient(int desc, MyServer *serv, QObject *parent) :QObject(parent)
{
    //храниим указатель на объект-сервер
    _serv = serv;
    //клиент не прошел авторизацию
    _isAutched = false;
    _name = constNameUnknown;
    //размер принимаемого блока 0
    _blockSize = 0;
    //создаем сокет
    _sok = new QTcpSocket(this);
    //устанавливаем дескриптор из incomingConnection()
    _sok->setSocketDescriptor(desc);
    //подключаем сигналы
    connect(_sok, SIGNAL(connected()), this, SLOT(onConnect()));
    connect(_sok, SIGNAL(disconnected()), this, SLOT(onDisconnect()));
    connect(_sok, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(_sok, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));

    qDebug() << "Client connected" << desc;
}
