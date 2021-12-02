#include "task.h"

task::task()
{
    //��ʼ�����ݿ�������
    QString  tableName="tasks";
    QString columnName[4]={"time","content","isActive"};
    QString dataType[4]={"varchar","varchar","bool"};
    int columnNum=4;
    //time varchar,user vachar,event varchar,type varchar
    initDatebase();
    createTable(tableName,columnName,dataType,columnNum);
}


//�������
void task::addTask(QDateTime dateTime,QTime time,int taskContentID,bool radioSelect)
{
    query=QSqlQuery(db);
    QString time_sql="ÿ��"+time.toString();
    QString dataTime_sql=dateTime.toString("yyyy-MM-dd hh:mm");
    QString content_sql;
    taskStatus = 0;
    switch (taskContentID) {
    case 0:
        content_sql="�򿪵���";
        break;
    case 1:
        content_sql="�رյ���";
        break;
    case 2:
        content_sql="�򿪷���";
        break;
    case 3:
        content_sql="�رշ���";
        break;
    case 4:
        content_sql="����¶�";
        break;
    default:
        break;
    }
    query.prepare("INSERT INTO tasks (time, content,isActive) "
                              "VALUES (?, ?, ?)");
    if(radioSelect)
    {
        query.addBindValue(time_sql);
        query.addBindValue(content_sql);
        query.addBindValue(taskStatus);
    }
    else
    {
        query.addBindValue(dataTime_sql);
        query.addBindValue(content_sql);
        query.addBindValue(taskStatus);
    }
    query.exec();
    //qDebug()<<time<<" "<<dateTime<<" "<<taskContentID<<" "<<radioSelect;
    //qDebug()<<time_sql<<" "<<dataTime_sql;
}
//��ȡ����
vector<vector<QString>> task::getTask()
{
    query=QSqlQuery(db);
    QString search_sql="select * from tasks";
    query.prepare(search_sql);
    query.exec();
    qDebug() << "����ȫ���ƻ�����";
    int row=0,col=3;
    vector<vector<QString> > tasks(sqlSize(query),vector<QString>(col,0));
    while(query.next()&&row<=sqlSize(query))
    {
        tasks[row][0]=query.value(0).toString();
        tasks[row][1]=query.value(1).toString();
        tasks[row][2]=query.value(2).toString();
        row++;
    }
    return tasks;
}
//ɾ������
bool task::delTask(int taskID)
{
    if(isTaskActive(taskID))
    {
        return 0;
    }
    else
    {
        query=QSqlQuery(db);
        QString del_sql=QString("delete from tasks where rowid =  '%1'"). arg(taskID);
        query.prepare(del_sql);
        query.exec();
        qDebug()<<"ִ����ɾ�����в���";
        query.exec("vacuum");
        qDebug()<<"ִ����ˢ�����ݿ����";
        return 1;
    }
}
//�ж������Ƿ�������״̬
bool task::isTaskActive(int taskID)
{
    query=QSqlQuery(db);
    QString find_sql=QString("select * from tasks where rowid =  '%1'"). arg(taskID);
    query.prepare(find_sql);
    query.exec();
    query.next();
    if(query.record().value(2).toBool())
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void task::setTask(int taskID,bool status)
{
    query=QSqlQuery(db);
    //UPDATE tasks SET isActive=0 WHERE ROWID = 1
    QString update_sql=QString("update tasks set isActive = '%1' where rowid = '%2' "). arg(status).arg(taskID);
    query.prepare(update_sql);
    query.exec();
}
