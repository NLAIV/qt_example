#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_getAllPersonsButton_clicked();
    void on_getOneButton_clicked();
    void on_nameButton_clicked();
    void on_actionButton_clicked();

    void allPersonsSlot(QNetworkReply *reply);
    void onePersonSlot(QNetworkReply *reply);
    void fullNameSlot(QNetworkReply *reply);
    void raiseSlot(QNetworkReply *reply);



private:
    Ui::MainWindow *ui;

    QNetworkAccessManager *allPersonsManager;
    QNetworkReply *allPersonsReply;

    QNetworkAccessManager *onePersonManager;
    QNetworkReply *onePersonReply;

    QNetworkAccessManager *fullNameManager;
    QNetworkReply *fullNameReply;

    QNetworkAccessManager *raiseManager;
    QNetworkReply *raiseReply;
};
#endif // MAINWINDOW_H
