//#include "tcpserver.h"

//TcpSocket::TcpSocket()
//{
//    connect(this,SIGNAL(readyRead()),this,SLOT(dataReceived()));
//    connect(this,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));
//}

//void TcpSocket::dataReceived()
//{
//    while (this->bytesAvailable()>0)
//    {
//        QByteArray datagram;//����һ���ֽ����������
//        datagram.resize(this->bytesAvailable());//���ݻ������������ֽ������С
//        this->read(datagram.data(),datagram.size());//��ȡ������������
//        QString msg=datagram.data();
//        emit updateClients(msg,datagram.size());//�����źŸ�server
//    }
//}

//void TcpSocket::slotDisconnected()
//{
//    emit disconnected(this->socketDescriptor());
//}


////-----------------------------------------


//Server::Server(int port):QTcpServer()
//{
//    listen(QHostAddress::Any,port);
//}

//void Server::slotUpdateClients(QString msg, int length)
//{
//    emit updateServer(msg,length);
//    QTcpSocket *item=NULL;
//    for(int i=0;i<tcpSocketList.count();i++)
//    {
//        item=tcpSocketList.at(i);
//        //item->write(msg.toAscii(),length);
//        //Qt4
//        item->write(msg.toLatin1(),length);
//        //Qt5
//    }
//}

//void Server::incomingConnection(int socketDescriptor)
//{
//    //TcpSocket *tcpSocket=new TcpSocket(this);
//    TcpSocket *tcpSocket;
//    tcpSocket->setSocketDescriptor(socketDescriptor);
//    connect(tcpSocket,SIGNAL(updateClients(QString,int)),this,SLOT(slotUpdateClients(QString,int)));
//    connect(tcpSocket,SIGNAL(disconnected(int)),this,SLOT(slotDisconnected(int)));
//    tcpSocketList.append(tcpSocket);
//}

//void Server::slotDisconnected(int descriptor)
//{
//    QTcpSocket *item=NULL;
//    for(int i=0;i<tcpSocketList.count();i++)
//    {
//        item=tcpSocketList.at(i);
//        if(item->socketDescriptor()==descriptor)
//        {
//            tcpSocketList.removeAt(i);
//            return;
//        }
//    }
//}



////-----------------------------------------

//tcpServer::tcpServer()
//{
//    port=8080;
//    //ui->lineEditPort->setText(QString::number(port));
//}

////void Widget::on_pushButtonCreate_clicked()
////{
////    server=new Server(this,port);
////    connect(server,SIGNAL(updateServer(QString,int)),this,SLOT(slotUpdateServer(QString,int)));
////    ui->pushButtonCreate->setEnabled(false);
////}

//void tcpServer::slotUpdateServer(QString msg, int length)
//{
//    //ui->listWidgetContent->addItem(msg.left(length) );
//}
