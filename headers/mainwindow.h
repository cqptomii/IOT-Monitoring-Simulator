#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "headers/Scheduler.hpp"
#include "headers/diagramwidget.h"
#include "src/Sensor/Sensor.h"
#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QCheckBox>
#include <QRadioButton>
#include <QTimer>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QLabel>
#include <QGroupBox>
#include <QLineEdit>
#include <QMessageBox>
#include <QCloseEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void onStartButtonClicked();  // Déclaration du slot
    void onStopButtonClicked();
    void sensor_clicked(bool add);
    void handle_log(bool checked,bool console);
    void onToggleButton(bool checked,bool add,const QString &type);
    void update_name(const QString &s,bool add);
    void update_Arrow(unsigned int sensor_type,bool server);
    void print_data(const QString &data);
    void recieve_scheduler_message(const QString &message);
protected:
    void closeEvent(QCloseEvent *event) override;
private:

    Scheduler *Mainprocess;
    Server *server_process;

    // Attribut lié aux widget
    DiagramWidget *sensor_diagram;
    QTextEdit *consoleTextEdit;

    // Attribut pour l'ajout et la suppression de capteurs
    bool is_started = false;
    QString sensor_add_name;
    unsigned int sensor_add_type;
    QString sensor_delete_name;
    unsigned int sensor_delete_type;

    //Attributs pour l'affichages du nombre de capteurs
    unsigned int t_count = 0;
    unsigned int h_count =0;
    unsigned int s_count = 0;
    unsigned int l_count = 0;
};
#endif // MAINWINDOW_H
