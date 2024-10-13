#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QCheckBox>
#include <QRadioButton>
#include "headers/Scheduler.hpp"
#include "headers/diagramwidget.h"
#include "src/Sensor/Sensor.h"
#include <QTimer>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void onStartButtonClicked();  // Déclaration du slot
    void onStopButtonClicked();
    void addSensorClicked();
    void deleteSensorClicked();
    void HandleConsoleLog(bool checked);
    void HandleFileLog(bool checked);
    void onToggleButtonadd(bool checked);
    void onToggleButtondelete(bool checked);
    void update_add_name(const QString &s);
    void update_delete_name(const QString &s);
    void update_Arrow(unsigned int sensor_type);
    void print_data(const QString &data);
    void recieve_scheduler_message(const QString &message);
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
