//#ifndef TCPSOCKET_H
//#define TCPSOCKET_H

//#include <QTcpSocket>
//#include <QObject>
//#include <string.h>
//#include <QtNetwork>

//class TcpSocket:public QTcpSocket
//{
//    Q_OBJECT
//public:
//    TcpSocket();

//signals:
//    void updateClients(QString,int);
//    void disconnected(int);
//protected slots:
//    void dataReceived();
//    void slotDisconnected();
//};

//#endif // TCPSOCKET_H

////-----------------------------------------

//#ifndef SERVER_H
//#define SERVER_H

//#include  <QTcpServer>

//class Server : public QTcpServer
//{
//    Q_OBJECT
//public:
//    Server(int port=0);
//    QList <TcpSocket*> tcpSocketList;//���ڱ�������ͻ��˵�TCP����

//signals:
//    void updateServer(QString,int);//���ڷ��͸���������½���

//public slots:
//    void slotUpdateClients(QString,int);//���ڽ���Ϣ����ÿ���ͻ���
//    void slotDisconnected(int); //�����Ƴ��Ͽ����ӵĿͻ���socket

//protected:
//    void incomingConnection(int socketDescriptor);//�麯����������ͼ���ӵĿͻ���
//    //�������Ӿ����������ת����Ϣ��
//};

//#endif // SERVER_H


////-----------------------------------------


//#ifndef TCPSERVER_H
//#define TCPSERVER_H

//class tcpServer:
//{
//public:
//     explicit tcpServer();
//    ~tcpServer();
//    int port;
//    Server *server;

//private:

//public slots:
//void slotUpdateServer(QString msg, int length);
////�ɵ���Ϣ����½���. msgΪ�յ�����Ϣ��lengthΪ�䳤��

//private slots:
//    //void on_pushButtonCreate_clicked();
//};

//#endif // TCPSERVER_H
