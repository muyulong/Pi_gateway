#include "regist.h"
#include "ui_regist.h"

regist::regist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::regist)
{
    QTextCodec *codec = QTextCodec::codecForName("GBK");//����"GBK",���ִ�Сд
    QTextCodec::setCodecForLocale(codec);
    ui->setupUi(this);
}

regist::~regist()
{
    delete ui;
}

void regist::on_pushButton_register_clicked()
{
    QString user;
    QString pwd,pwd2;
    user = ui->username->text();
    pwd = ui->password->text();
    pwd2=ui->password_2->text();
    if(user == "")
        QMessageBox::warning(this,"","�û�������Ϊ�գ�");
    else if(pwd == "")
        QMessageBox::warning(this,"","���벻��Ϊ�գ�");
    else if(pwd2== "")
        QMessageBox::warning(this,"","ȷ�����벻��Ϊ�գ�");
    else if(!(pwd==pwd2))
        QMessageBox::warning(this,"","�����������������ͬ��");
    else
    {
        int reg = U.setUser(user,pwd);
        if(reg==1)
        {
            QMessageBox::information(NULL, "ע��ɹ�", "ע��ɹ�������", QMessageBox::Yes);
            this->close();
        }
        else if(reg==2)
            QMessageBox::warning(NULL,"Error","�û����ظ�������");
        else if (reg==0)
            QMessageBox::warning(NULL,"Error","ע��ʧ�ܣ������ԣ�����");
    }
}
void regist::closeEvent(QCloseEvent *)
  {
     emit exitRegist();
 }
