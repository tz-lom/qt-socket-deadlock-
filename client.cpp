#include "client.h"

Client::Client(QObject *parent):
    QObject(parent)
{

}

void Client::readFromSocket(std::size_t size, char *memory)
{
    qint64 offset = 0;
    while(offset<(qint64)size)
    {
        if(socket->bytesAvailable()==0) socket->waitForReadyRead(500);
        qint64 o = socket->read(memory+offset, size-offset);
        if(o<0)
        {
            qDebug() << "Something bad in client socket";
            throw 0;
        }
        offset+=o;
    }
}

void Client::openSocket()
{
    socket = new QTcpSocket(this);
    socket->connectToHost("localhost", 1337);
    if(!socket->waitForConnected())
    {
        qDebug()<< "Client connection failed";
        return;
    }


    QByteArray ba(6,'@');
    readFromSocket(ba.size(), ba.data());
    qDebug() << "Received header" << ba;
}
