#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_getAllPersonsButton_clicked()
{
    QString site_url="http://localhost:3000/example/allpersons";
    QString credentials="Automaatti123:Salasana123";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader( "Authorization", headerData.toLocal8Bit() );
    allPersonsManager = new QNetworkAccessManager(this);
    connect(allPersonsManager, SIGNAL(finished (QNetworkReply*)),
    this, SLOT(allPersonsSlot(QNetworkReply*)));
    allPersonsReply = allPersonsManager->get(request);
}

void MainWindow::allPersonsSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    qDebug() << response_data;
    if(response_data.compare("-4078")==0)
    {
        ui->resultlabel->setText("Error in database connection.");
    }
    else
    {
        QJsonDocument json_doc=QJsonDocument::fromJson(response_data);
        QJsonArray json_array=json_doc.array();
        QString persons;
        foreach(const QJsonValue &value, json_array){
            QJsonObject json_obj=value.toObject();
            persons+=QString::number(json_obj["id_person"].toInt())+" "
                    +json_obj["fname"].toString()+" "
                    +json_obj["lname"].toString()+" "
                    +QString::number(json_obj["balance"].toDouble())+"\r\n"
                    ;
        }
        ui->resultlabel->setText(persons);
    }

    allPersonsReply->deleteLater();
    reply->deleteLater();
    allPersonsManager->deleteLater();
}

void MainWindow::on_getOneButton_clicked()
{
    QString id = ui->lineEditId->text();
    if(id=="")
    {
        ui->resultlabel->setText("Please give valid ID.");
    }
    else
    {
        QString site_url="http://localhost:3000/example/oneperson/"+id;
        QString credentials="Automaatti123:Salasana123";
        QNetworkRequest request((site_url));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        QByteArray data = credentials.toLocal8Bit().toBase64();
        QString headerData = "Basic " + data;
        request.setRawHeader( "Authorization", headerData.toLocal8Bit() );
        onePersonManager = new QNetworkAccessManager(this);
        connect(onePersonManager, SIGNAL(finished (QNetworkReply*)),
        this, SLOT(onePersonSlot(QNetworkReply*)));
        onePersonReply = onePersonManager->get(request);
    }

}

void MainWindow::onePersonSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    qDebug() << response_data;
    if(response_data.compare("-4078")==0)
    {
        ui->resultlabel->setText("Error in database connection.");
    }
    else if(response_data.compare("")==0)
    {
        ui->resultlabel->setText("Requesed person does not exist.");
    }
    else
    {
        QJsonDocument json_doc=QJsonDocument::fromJson(response_data);
        QJsonObject json_obj=json_doc.object();
        QString person=QString::number(json_obj["id_person"].toInt())+" "
                +json_obj["fname"].toString()+" "
                +json_obj["lname"].toString()+" "
                +QString::number(json_obj["balance"].toDouble())+"\r\n"
                ;
        ui->resultlabel->setText(person);
    }

    onePersonReply->deleteLater();
    reply->deleteLater();
    onePersonManager->deleteLater();
}

void MainWindow::on_nameButton_clicked()
{
    QString id = ui->lineEditId->text();
    if(id=="")
    {
        ui->resultlabel->setText("Please give valid ID.");
    }
    else
    {
    QString site_url="http://localhost:3000/example/fullname/"+id;
    QString credentials="Automaatti123:Salasana123";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader( "Authorization", headerData.toLocal8Bit() );
    fullNameManager = new QNetworkAccessManager(this);
    connect(fullNameManager, SIGNAL(finished (QNetworkReply*)),
    this, SLOT(fullNameSlot(QNetworkReply*)));
    fullNameReply = fullNameManager->get(request);
    }
}

void MainWindow::fullNameSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    qDebug() << response_data;
    if(response_data.compare("-4078")==0)
    {
        ui->resultlabel->setText("Error in database connection.");
    }
    else if(response_data.compare("")==0)
    {
        ui->resultlabel->setText("Requesed person does not exist.");
    }
    else
    {
        QJsonDocument json_doc=QJsonDocument::fromJson(response_data);
        QJsonObject json_obj=json_doc.object();
        QString name=json_obj["fullname"].toString()+"\r\n";
        ui->resultlabel->setText(name);
    }

    fullNameReply->deleteLater();
    reply->deleteLater();
    fullNameManager->deleteLater();
}


void MainWindow::on_actionButton_clicked()
{
    QString id = ui->lineEditId->text();
    QString amount = ui->lineEditAmount->text();
    if(id=="")
    {
        ui->resultlabel->setText("Please give valid ID.");
    }
    else if(amount=="")
    {
        ui->resultlabel->setText("Please give valid amount.");
    }
    else
    {
    QJsonObject json_obj;
    json_obj.insert("id",id);
    json_obj.insert("amount",amount);
    QString site_url="http://localhost:3000/person/money_action";
    QString credentials="Automaatti123:Salasana123";
    QNetworkRequest request(site_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader( "Authorization", headerData.toLocal8Bit() );
    raiseManager = new QNetworkAccessManager(this);
    connect(raiseManager, SIGNAL(finished (QNetworkReply*)),
    this, SLOT(raiseSlot(QNetworkReply*)));
    raiseReply = raiseManager->post(request, QJsonDocument(json_obj).toJson());
    }
}

void MainWindow::raiseSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    qDebug() << response_data;
    if(response_data.compare("-4078")==0)
    {
        ui->resultlabel->setText("Error in database connection.");
    }
    else if(response_data.compare("0")==0)
    {
        ui->resultlabel->setText("Request could not be completed.");
    }
    else
    {
        ui->resultlabel->setText("Request completed.");
    }

    raiseReply->deleteLater();
    reply->deleteLater();
    raiseManager->deleteLater();
}

