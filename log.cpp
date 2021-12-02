#include "log.h"
#include "ui_log.h"

log::log(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::log)
{
    QTextCodec *codec = QTextCodec::codecForName("GBK");//����"GBK",���ִ�Сд
    QTextCodec::setCodecForLocale(codec);
    //��ʼ�����ݿ����־��
    QString  tableName="logs";
    QString columnName[4]={"time","user","event","type"};
    QString dataType[4]={"varchar","varchar","varchar","varchar"};
    int columnNum=4;
    //time varchar,user vachar,event varchar,type varchar
    initDatebase();
    createTable(tableName,columnName,dataType,columnNum);
    ui->setupUi(this);

    ui->radioButton_MutiSelect->setChecked(false);
    checkState=0;
}

log::~log()
{
    delete ui;
}

void log::logViewer(int typeId)
{
    QString type;
    switch (typeId) {
    case 1:
        type="ȫ��";
        break;
    case 2:
        type="��ʱ����";
        break;
    case 3:
        type="������־";
        break;
    case 4:
        type="����";
        break;
    default:
        break;
    }
    viewLog=getLog(type);

    size_row = viewLog.size();
    qDebug() << "���յ���־������"<<viewLog.size();
    tableCreator(size_row);
}
void log::tableCreator(int size_row)
{
    //��������������������������
    QStandardItemModel* standItemModel = new QStandardItemModel(this);
    QVBoxLayout *mainLayout = new QVBoxLayout;       //��ֱ����
    mainLayout->setSpacing(50);         //���ÿؼ����
    mainLayout->setMargin(70);          //���ñ�Ե���
    //mainLayout.
    //���QTableView����
    tableView = new QTableView;
    //��ӱ�ͷ
    standItemModel->setColumnCount(3);
    standItemModel->setHeaderData(0,Qt::Horizontal,QStringLiteral("ʱ��"));   //���ñ�ͷ����
    standItemModel->setHeaderData(1,Qt::Horizontal,QStringLiteral("�¼�"));
    standItemModel->setHeaderData(2,Qt::Horizontal,QStringLiteral("�û�"));
    //�����������
    for(int i=0;i<size_row;++i)
    {
        QString time=viewLog[i][0];
        QString user=viewLog[i][1];
        QString event=viewLog[i][2];
        standItemModel->setItem(i, 0, new QStandardItem(time));
        standItemModel->setItem(i, 1, new QStandardItem(event));
        standItemModel->setItem(i, 2, new QStandardItem(user));
        standItemModel->item(i,0)->setTextAlignment(Qt::AlignCenter);           //���ñ�����ݾ���
        standItemModel->item(i,1)->setTextAlignment(Qt::AlignCenter);           //���ñ�����ݾ���
        standItemModel->item(i,2)->setTextAlignment(Qt::AlignCenter);           //���ñ�����ݾ���
    }
    tableView->setModel(standItemModel);    //���ر��ģ��
    //���ñ������
    //tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);        //��ͷ��Ϣ��ʾ����
    tableView->setColumnWidth(0,100);       //�趨����0�п��
    tableView->setColumnWidth(1,200);
    //tableView->verticalHeader()->hide();    //����Ĭ����ʾ����ͷ
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows); //����ѡ��ʱ����ѡ��
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  //���ñ������ֻ�������ܱ༭
    /* �����п��ڿ��ӽ�������Ӧ��� */
    tableView->horizontalHeader()->setSectionResizeMode (QHeaderView::Stretch);
    //qDebug() <<tableView->horizontalHeader();
    /* ����ɫ������ʾ */
    tableView->setAlternatingRowColors(true);
    /* ��������ͼ�ν����޸����� */
    //    tableView->setContextMenuPolicy(Qt::CustomContextMenu);         //��Ҫ�ڱ��ʹ���Ҽ��˵�����Ҫ����������
    //    tableView->sortByColumn(0,Qt::AscendingOrder);                 //����0�У�����������
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    mainLayout->addWidget(tableView);    //��ӿؼ�
    this->ui->tabWidget->setLayout(mainLayout);
    //setLayout(mainLayout);        //��ʾ��ֱ����
    //��������������������������
}
void log::on_tabWidget_currentChanged(int index)
{
    delete ui->tabWidget->layout();
    currentTab=index+1;
    logViewer(currentTab);

}


void log::on_pushButton_delLog_clicked()
{
    //    int i = tableView->currentIndex().row()+1;
    //    qDebug()<<i;
    //    d.delLogs(i);
    //    delete ui->tabWidget->layout();
    //    logViewer(currentTab);
    //    QString dlgTitle=QString("ɾ��");
    //    QString strInfo=QString("��ɾ����%1����¼��"). arg(i);
    //    QMessageBox::information(this, dlgTitle, strInfo,QMessageBox::Ok,QMessageBox::NoButton);
    //    qDebug()<<tableView->selectionModel()->selectedRows();
    //    QModelIndexList indexList = tableView->selectionModel()->selectedRows();
    //    int row;
    //    int count=0;
    //    foreach (QModelIndex index, indexList) {
    //        row = index.row();
    //        count++;
    //        qDebug()<<row;
    //    }
    //    qDebug()<<count;
    QString dlgTitle=QString("ɾ��");
    QString strInfo;
    int clickState=0;
    if(ui->radioButton_MutiSelect->isChecked())
    {
        //��ѡ
        qDebug()<<tableView->selectionModel()->selectedRows();
        QModelIndexList indexList = tableView->selectionModel()->selectedRows();
        int count=0;
        vector<int> mutiRow;
        foreach (QModelIndex index, indexList) {
            //mutiRow[count] = index.row();
            mutiRow.push_back(index.row()+1);
            count++;
        }
        qDebug()<<mutiRow;
        qDebug()<<count;
        delLogs(mutiRow,2,count);
        strInfo=QString("��ɾ��%1����¼��"). arg(count);
        //QMessageBox::information(this, dlgTitle, strInfo,QMessageBox::Ok,QMessageBox::NoButton);
        if(count==0)
            clickState=0;
        else
            clickState=2;
    }
    else
    {
        //��ѡ
        // qDebug()<<i;
        //delete ui->tabWidget->layout();
        //logViewer(currentTab);
        //qDebug()<<tableView->currentIndex().row();
        //QString strInfo=QString("��ɾ����%1����¼��"). arg(i);
        //QMessageBox::information(this, dlgTitle, strInfo,QMessageBox::Ok,QMessageBox::NoButton);
        //=================
        int i;
        i= tableView->currentIndex().row()+1;
        qDebug()<<i;
        vector<int> singleRow(1,i);
        delLogs(singleRow,1,1);
        qDebug()<<singleRow;
        strInfo=QString("��ɾ����%1����¼��"). arg(singleRow[0]);
        //QMessageBox::information(this, dlgTitle, strInfo,QMessageBox::Ok,QMessageBox::NoButton);
        if(singleRow[0]==0)
            clickState=0;
        else
            clickState=1;
    }
    if(clickState==0)
    {
        strInfo="δѡ���κ��У�";
    }
    QMessageBox::information(this, dlgTitle, strInfo,QMessageBox::Ok,QMessageBox::NoButton);
    delete ui->tabWidget->layout();
    logViewer(currentTab);
    ui->radioButton_MutiSelect->setChecked(false);
    checkState=0;
}


void log::on_radioButton_MutiSelect_clicked()
{
    //������������������������
    //���ö�ѡ


    if(!checkState)
    {
        delete ui->tabWidget->layout();
        logViewer(currentTab);
        tableView->setSelectionMode(QAbstractItemView::MultiSelection);
        checkState=1;
    }
    else
    {
        delete ui->tabWidget->layout();
        logViewer(currentTab);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        checkState=0;
    }
    qDebug()<<checkState;
    //������������������������
}


void log::on_pushButton_delAllTab_clicked()
{
    if(checkState==0)
    {
        on_radioButton_MutiSelect_clicked();
        ui->radioButton_MutiSelect->setChecked(true);
    }
    for(int i=0;i<=size_row;i++)
    {
        tableView->selectRow(i);
    }
    //on_pushButton_delLog_clicked();
    //tableView->selectRow();
    //ɾ���������ݿ��ٶȺ���
}

void log::addLog(QString user,int eventId){
    //QString newLog = user+" do "+event+" at "+"time";
    QString time =QDateTime::currentDateTime() .toString("yyyy-MM-dd hh:mm:ss ddd");
    QString event;
    QString type;
    switch (eventId) {
    case 1:
        event="��¼ϵͳ";
        type="������־";
        break;
    case 2:
        event="�˳�ϵͳ";
        type="������־";
        break;
    case 3:
        event="��ʼ��ϵͳ";
        type="������־";
        break;
    default:
        event="δ֪�¼�";
        type="ȫ��";
        break;
    }
    query=QSqlQuery(db);
    query.prepare("INSERT INTO logs (time, user, event, type) "
                          "VALUES (?, ?, ?, ?)");
    query.addBindValue(time);
    query.addBindValue(user);
    query.addBindValue(event);
    query.addBindValue(type);
    query.exec();
}

vector<vector<QString>>  log::getLog(QString type)
{
    //�����ݿ��м�����Ӧ���͵���־
    query=QSqlQuery(db);
    QString search_sql="select * from logs where type=(?)";
    QString search_sql_all="select * from logs";
    if(type=="ȫ��")
    {
        query.prepare(search_sql_all);
        qDebug() << "����ȫ����־";
    }
    else
    {
        query.prepare(search_sql);
        query.addBindValue(type);
        qDebug() << "������־";
    }
    query.exec();
    //
    //    query.prepare(search_sql);
    //    query.addBindValue(type);
    //    query.exec();
    //qDebug()<<"ִ��query. exec()���Ϊ��"<<query.exec();
    //qDebug()<<"����query. next()���Ϊ��"<<query.next();
    //qDebug() << "һ����"<<sqlSize(query)<<"����־";
    int row=0,col=3;
    //    QString logs[i][3];
    vector<vector<QString> > logs(sqlSize(query),vector<QString>(col,0));
    while(query.next()&&row<=sqlSize(query))
    {
        //        logs[i-1][0]=query.value(0).toString();
        //        logs[i-1][1]=query.value(1).toString();
        //        logs[i-1][2]=query.value(2).toString();
        logs[row][0]=query.value(0).toString();
        logs[row][1]=query.value(1).toString();
        logs[row][2]=query.value(2).toString();
        row++;
        //qDebug() << "�����"<<row<<"����־";
        //QString line=QString(str("ѧ��")+��%1"+str("����")+��%2"+str("���")+��%3").arg(number).arg(name).arg(height);
        //QString line=QString("ѧ�� %1     ���� %2     ��� %3").arg(number,5).arg(name,10).arg(height,5);
        //qDebug()<<line;
        //ui->textEditList->append(line);


    }
    return logs;
}

//void Widget::on_listButton_clicked()//�б�ť
//{
//    int number;
//    QString name;
//    int height;
//    QString listStr=QString("select * from student");
//    QSqlQuery query;
//    query.exec(listStr);
//    ui->textEditList->clear();
//    while(query.next())
//    {
//        number=query.value(0).toInt();
//        name=query.value(1).toString();
//        height=query.value(2).toInt();
//        //QString line=QString(str("ѧ��")+��%1"+str("����")+��%2"+str("���")+��%3").arg(number).arg(name).arg(height);
//        QString line=QString("ѧ�� %1     ���� %2     ��� %3").arg(number,5).arg(name,10).arg(height,5);
//        //qDebug()<<line;
//        ui->textEditList->append(line);
//    }
//}


void log::delLogs(vector<int> row,int delType,int count)
{
    query=QSqlQuery(db);
    switch (delType) {
    case 1:
    {
        QString del_single_sql=QString("delete from logs where rowid =  '%1'"). arg(row[0]);
        query.prepare(del_single_sql);
        query.exec();
        qDebug()<<"ִ����ɾ�����в���";
        break;
    }
    case 2:
    {
        for(int i=0;i<count;i++)
        {
            QString del_muti_sql=QString("delete from logs where rowid =  '%1'"). arg(row[i]);
            query.prepare(del_muti_sql);
            query.exec();
        }
        qDebug()<<"ִ����ɾ�����в���";
        break;
    }
    default:
        break;
    }

    query.exec("vacuum");
    qDebug()<<"ִ����ˢ�����ݿ����";
}
