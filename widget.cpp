#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    QTextCodec *codec = QTextCodec::codecForName("GBK");//����"GBK",���ִ�Сд
    QTextCodec::setCodecForLocale(codec);
    ui->setupUi(this);

    buttonNameList.append("ss");
    buttonNameList.append("ss");
    buttonNameList.append("ss");
    buttonNameList.append("ss");

    ui->comboBox_event->addItems(QStringList()<<"�򿪵���"<<"�رյ���"<<"�򿪷���"<<"�رշ���"<<"����¶�");
    radioSelect=0;
    ui->radioButton_time->click();
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_2_clicked()
{
    //����ˮƽ����,�������ð�ť������˳��
    QHBoxLayout *hBoxLayout = new QHBoxLayout();
    hBoxLayout->setObjectName(hBoxLay);
    foreach(QString buttonName,buttonNameList)
    {
        QPushButton *pButton = new QPushButton(buttonName,ui->scrollArea);
        pButton->setObjectName(buttonName);
        pButton->setText(buttonName);
        hBoxLayout->addWidget(pButton);
    }
    ui->scrollArea->setLayout(hBoxLayout);

}


void Widget::on_pushButton_4_clicked()
{
    foreach(QString buttonName, buttonNameList)
    {
        //��ȡgroupBox�е�Pushbutton
        QPushButton *pushBt =  ui->scrollArea->findChild<QPushButton*>(buttonName);
        //ɾ��pushButton
        delete pushBt;
    }
    //ɾ��ˮƽ����,����˴���ɾ������ʹ�õڶ��������ͬ���Ƶ�QPushbuttonʱʧ��
    QHBoxLayout *HBoxlay = ui->scrollArea->findChild<QHBoxLayout*>(hBoxLay);
    delete HBoxlay;
}

void Widget::closeEvent(QCloseEvent *event)
{
    switch( QMessageBox::information(this,tr("��ʾ"),tr("ȷ���˳�ϵͳ?"),tr("ȷ��"), tr("ȡ��"),0,1))
    {
    case 0:
        this->L.addLog(usr,2);
        event->accept();
        break;
    case 1:
    default:
        event->ignore();
        break;
    }
}

void Widget::getLoginUser(QString user)
{
    usr=user;
}

void Widget::on_pushButton_viewLog_clicked()
{
    L.logViewer(1);
    L.setModal(false);
    L.show();
}


void Widget::on_pushButton_setTask_clicked()
{
    QDateTime datetime;
    QTime time;
    int taskContentID;
    datetime=ui->dateTimeEdit->dateTime();
    time=ui->timeEdit->time();
    taskContentID=ui->comboBox_event->currentIndex();
    T.addTask(datetime,time,taskContentID,radioSelect);
    taskViewer();
}


void Widget::on_radioButton_time_clicked()
{
    ui->dateTimeEdit->setEnabled(false);
    ui->timeEdit->setEnabled(true);
    radioSelect=1;
}


void Widget::on_radioButton_dateTime_clicked()
{
    ui->dateTimeEdit->setEnabled(true);
    ui->timeEdit->setEnabled(false);
    radioSelect=0;
}

void Widget::taskViewer()
{
    viewTask=T.getTask();
    size_row = viewTask.size();
    qDebug() << "���յ�����������"<<viewTask.size();
    taskTable(size_row);
}

void Widget::taskTable(int size_row)
{
    //��������������������������
    QStandardItemModel* standItemModel = new QStandardItemModel(this);
    standItemModel->setColumnCount(3);
    standItemModel->setHeaderData(0,Qt::Horizontal,QStringLiteral("ʱ��"));   //���ñ�ͷ����
    standItemModel->setHeaderData(1,Qt::Horizontal,QStringLiteral("����"));
    standItemModel->setHeaderData(2,Qt::Horizontal,QStringLiteral("״̬"));
    //�����������
    for(int i=0;i<size_row;++i)
    {
        QString time=viewTask[i][0];
        QString task=viewTask[i][1];
        QString status=viewTask[i][2];
        if(status=="0")
        {
            status="δ����";
        }
        if(status=="1")
        {
            status="������";
        }
        standItemModel->setItem(i, 0, new QStandardItem(time));
        standItemModel->setItem(i, 1, new QStandardItem(task));
        standItemModel->setItem(i, 2, new QStandardItem(status));
        standItemModel->item(i,0)->setTextAlignment(Qt::AlignCenter);           //���ñ�����ݾ���
        standItemModel->item(i,1)->setTextAlignment(Qt::AlignCenter);           //���ñ�����ݾ���
        standItemModel->item(i,2)->setTextAlignment(Qt::AlignCenter);           //���ñ�����ݾ���
    }
    ui->tableView_task->setModel(standItemModel);    //���ر��ģ��
    //���ñ������
    //tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);        //��ͷ��Ϣ��ʾ����
    ui->tableView_task->setColumnWidth(0,150);       //�趨�����
    ui->tableView_task->setColumnWidth(1,80);
    ui->tableView_task->setColumnWidth(2,75);
    //tableView->verticalHeader()->hide();    //����Ĭ����ʾ����ͷ
    ui->tableView_task->setSelectionBehavior(QAbstractItemView::SelectRows); //����ѡ��ʱ����ѡ��
    ui->tableView_task->setEditTriggers(QAbstractItemView::NoEditTriggers);  //���ñ������ֻ�������ܱ༭
    /* �����п��ڿ��ӽ�������Ӧ��� */
    //ui->tableView_task->horizontalHeader()->setSectionResizeMode (QHeaderView::Stretch);
    //qDebug() <<tableView->horizontalHeader();
    /* ����ɫ������ʾ */
    ui->tableView_task->setAlternatingRowColors(true);
    /* ��������ͼ�ν����޸����� */
    //    tableView->setContextMenuPolicy(Qt::CustomContextMenu);         //��Ҫ�ڱ��ʹ���Ҽ��˵�����Ҫ����������
    //    tableView->sortByColumn(0,Qt::AscendingOrder);                 //����0�У�����������
    ui->tableView_task->setSelectionMode(QAbstractItemView::SingleSelection);
    //��������������������������
}

void Widget::on_pushButton_startTask_clicked()
{
    int i=0;
    i= ui->tableView_task->currentIndex().row()+1;
    T.setTask(i,1);
    taskViewer();
}


void Widget::on_pushButton_stopTask_clicked()
{
    int i=0;
    i= ui->tableView_task->currentIndex().row()+1;
    T.setTask(i,0);
    taskViewer();
}


void Widget::on_pushButton_delTask_clicked()
{
    QString dlgTitle=QString("ɾ��");
    QString strInfo;
    int i=0;
    i= ui->tableView_task->currentIndex().row()+1;
    qDebug()<<i;
    if(i==0)
    {
        strInfo="δѡ���κ��У�";
    }
    else
    {
        bool dT=T.delTask(i);
        if(!dT)
        {
            strInfo=QString("�޷�ɾ�����������е�����");
        }
        if(dT)
        {
            strInfo=QString("��ɾ����%1����¼��"). arg(i);
        }
    }
    QMessageBox::information(this, dlgTitle, strInfo,QMessageBox::Ok,QMessageBox::NoButton);
    taskViewer();
}

