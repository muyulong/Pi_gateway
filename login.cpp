#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    QTextCodec *codec = QTextCodec::codecForName("GBK");//����"GBK",���ִ�Сд
    QTextCodec::setCodecForLocale(codec);
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_login_clicked()
{
    QString user;
    QString pwd;
    user = ui->username->text();//��ȡ�û���
    pwd = ui->password->text();//��ȡ����
    if(user == "")
        QMessageBox::warning(this,"","�û�������Ϊ�գ�");
    else if(pwd == "")
        QMessageBox::warning(this,"","���벻��Ϊ�գ�");
    else
    {
        //�����ݿ��н��в�ѯ��֤
        bool login = U.compareUser(user,pwd);
        if(login)
        {
            w.L.addLog(user,1);
            w.getLoginUser(user);
            w.show();
            w.taskViewer();
            this->close();
            emit exitWelcome();
        }
        else
            QMessageBox::warning(NULL,"Error","�û�����������󣡣���");
    }
}
void login::closeEvent(QCloseEvent *)
{
    emit exitLogin();
}
