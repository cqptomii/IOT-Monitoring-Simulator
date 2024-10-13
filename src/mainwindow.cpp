#include "headers/mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QLabel>
#include <QGroupBox>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),Mainprocess(new Scheduler(this)),server_process(new Server(this,true,false)){

    *this->Mainprocess << server_process;

    ///
    /// Allocation des attributs de la classe
    ///

    QPushButton *start = new QPushButton("Start Simulation", this);
    QPushButton *stop = new QPushButton("Stop Simulation", this);
    start->setStyleSheet("background-color: lightblue; color: black;");
    stop->setStyleSheet("background-color: red; color: black;");

    connect(start, &QPushButton::clicked, this, &MainWindow::onStartButtonClicked);
    connect(stop, &QPushButton::clicked,this, &MainWindow::onStopButtonClicked);
    ///
    ///   Gestion du layout bouton
    ///

    QVBoxLayout *buttonLayout = new QVBoxLayout();
    buttonLayout->addWidget(start);
    buttonLayout->addWidget(stop);


    QCheckBox *console_log = new QCheckBox("log Console",this);
    console_log->setChecked(true);
    QCheckBox *file_log = new QCheckBox("log fichier",this);
    file_log->setChecked(false);
    connect(console_log, &QCheckBox::clicked, this, &MainWindow::HandleConsoleLog);
    connect(file_log, &QCheckBox::clicked, this,&MainWindow::HandleFileLog);


    ///
    ///  Gestion du layout options
    ///

    QHBoxLayout *optionsLayout = new QHBoxLayout();
    optionsLayout->addWidget(console_log);
    optionsLayout->addWidget(file_log);


    ///
    /// \brief Creation du Widget pour ajouter des capteurs
    ///

    QLineEdit *nameadd = new QLineEdit(this);
    nameadd->setMaximumWidth(150);
    nameadd->setMaximumHeight(25);
    connect(nameadd,&QLineEdit::textChanged,this,&MainWindow::update_add_name);

    QRadioButton *TempButton = new QRadioButton("Temperature ",this);
    QRadioButton *HumButton = new QRadioButton("Humidité ",this);
    QRadioButton *SoundButton = new QRadioButton("Son ",this);
    QRadioButton *LightButton = new QRadioButton("Lumière ",this);
    connect(TempButton,&QRadioButton::toggled,this,&MainWindow::onToggleButtonadd);
    connect(HumButton,&QRadioButton::toggled,this,&MainWindow::onToggleButtonadd);
    connect(SoundButton,&QRadioButton::toggled,this,&MainWindow::onToggleButtonadd);
    connect(LightButton,&QRadioButton::toggled,this,&MainWindow::onToggleButtonadd);

    QPushButton *pbAdd = new QPushButton("Ajouter",this);
    connect(pbAdd,&QPushButton::clicked,this,&MainWindow::addSensorClicked);


    ///
    /// gestion du layout add
    ///

    QVBoxLayout *addLayout = new QVBoxLayout();
    addLayout->addWidget(nameadd);
    addLayout->addWidget(TempButton);
    addLayout->addWidget(HumButton);
    addLayout->addWidget(SoundButton);
    addLayout->addWidget(LightButton);
    addLayout->addWidget(pbAdd);
    addLayout->addStretch();

    QGroupBox *addGBox = new QGroupBox("Server and Sensors", this);
    addGBox->setLayout(addLayout);
    addGBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    addGBox->setMaximumWidth(225);


    ///
    /// \brief Creation du Widget pour supprimer des capteurs
    ///

    QLineEdit *namedelete = new QLineEdit(this);
    namedelete->setMaximumWidth(150);
    namedelete->setMaximumHeight(25);
    connect(namedelete,&QLineEdit::textChanged,this,&MainWindow::update_delete_name);

    QRadioButton *TempButtonD = new QRadioButton("Temperature ", this);
    QRadioButton *HumButtonD = new QRadioButton("Humidité ", this);
    QRadioButton *SoundButtonD = new QRadioButton("Son ", this);
    QRadioButton *LightButtonD = new QRadioButton("Lumière ", this);
    connect(TempButtonD,&QRadioButton::toggled,this,&MainWindow::onToggleButtondelete);
    connect(HumButtonD,&QRadioButton::toggled,this,&MainWindow::onToggleButtondelete);
    connect(SoundButtonD,&QRadioButton::toggled,this,&MainWindow::onToggleButtondelete);
    connect(LightButtonD,&QRadioButton::toggled,this,&MainWindow::onToggleButtondelete);

    QPushButton *pbDelete = new QPushButton("Supprimer", this);
    connect(pbDelete,&QPushButton::clicked,this,&MainWindow::deleteSensorClicked);
    ///
    /// gestion du layout delete
    ///

    QVBoxLayout *deleteLayout = new QVBoxLayout();
    deleteLayout->addWidget(namedelete);
    deleteLayout->addWidget(TempButtonD);
    deleteLayout->addWidget(HumButtonD);
    deleteLayout->addWidget(SoundButtonD);
    deleteLayout->addWidget(LightButtonD);
    deleteLayout->addWidget(pbDelete);
    deleteLayout->addStretch();

    QGroupBox *deleteGBox = new QGroupBox("Server and Sensors", this);
    deleteGBox->setLayout(deleteLayout);
    deleteGBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    deleteGBox->setMaximumWidth(225);

    ///
    ///  Layout properties et creation du widget
    ///

    QVBoxLayout *propertiesLayout = new QVBoxLayout();
    propertiesLayout->addItem(buttonLayout);
    propertiesLayout->addItem(optionsLayout);
    propertiesLayout->addWidget(addGBox);
    propertiesLayout->addWidget(deleteGBox);



    sensor_diagram = new DiagramWidget;

    QVBoxLayout *painterLayout = new QVBoxLayout();
    painterLayout->addWidget(sensor_diagram);

    ///
    /// \brief schemaGroupBox groupbox de visualisation des capteurs
    ///

    QGroupBox *schemaGroupBox = new QGroupBox("Server and Sensors", this);
    schemaGroupBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    schemaGroupBox->setLayout(painterLayout);

    ///
    /// \brief userPannel pannel de travail
    ///

    QHBoxLayout *userPannel = new QHBoxLayout();
    userPannel->addWidget(schemaGroupBox);
    userPannel->addItem(propertiesLayout);
    userPannel->setContentsMargins(0, 0, 0, 0);
    userPannel->setSpacing(0);

    ///
    /// Creation de la console
    ///

    // Utilisation de l'attribut de classe consoleTextEdit
    consoleTextEdit = new QTextEdit(this);
    consoleTextEdit->setReadOnly(true);
    consoleTextEdit->setStyleSheet("background-color: lightgrey; color: black;");

    QScrollArea *console = new QScrollArea(this);
    console->setWidget(consoleTextEdit);
    console->setWidgetResizable(true);
    console->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    ///
    /// Creation du widget principale
    ///

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addItem(userPannel);
    mainLayout->addWidget(console);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    console->setMaximumHeight(150);
    consoleTextEdit->append("Bienvenue dans la console du IOT Manager");

    connect(server_process,&Server::data_to_display,this,&MainWindow::print_data);
    connect(Mainprocess,&Scheduler::drawArrow,this,&MainWindow::update_Arrow);
    connect(Mainprocess,&Scheduler::send_message,this,&MainWindow::recieve_scheduler_message);
}
void MainWindow::onStartButtonClicked() {
    if(!is_started){
        this->is_started = true;
        this->consoleTextEdit->clear();
        consoleTextEdit->append("Début de la simulation :");

        this->Mainprocess->start();
    }
}
void MainWindow::onStopButtonClicked(){
    this->Mainprocess->stop();
    this->consoleTextEdit->clear();
    this->consoleTextEdit->append("Fin de la simulation");
    this->is_started = false;
    update();
}
void MainWindow::addSensorClicked(){
    if(!is_started){
        if(this->sensor_add_name == "" || this->sensor_add_type > 4){
            this->consoleTextEdit->append("Erreur : Veuillez entrez l'ensemble des configurations avant d'ajouter un capteur");
            return;
        }
        switch(this->sensor_add_type){
            case 1 :{
                Temperature addT(this->sensor_add_name.toStdString());
                *Mainprocess << addT;
                this->t_count++;
                break;
            }
            case 2:{

                Humidity addH(this->sensor_add_name.toStdString());
                *Mainprocess << addH;
                this->h_count++;
                break;
            }
            case 3:{
                Sound addS(this->sensor_add_name.toStdString());
                *Mainprocess << addS;
                this->s_count++;
                break;
            }
            case 4:{
                Light addL(this->sensor_add_name.toStdString());
                *Mainprocess << addL;
                this->l_count++;
                break;
            }
        }
        this->sensor_diagram->update_sensor_count(t_count,h_count,s_count,l_count);
    }
}
void MainWindow::deleteSensorClicked(){
    if(!is_started){
        if(this->sensor_add_name == "" || this->sensor_add_type > 4){
            this->consoleTextEdit->append("Erreur : Veuillez entrez l'ensemble des configurations avant de supprimer un capteur");
            return;
        }
        switch(this->sensor_add_type){
            case 1 :{
                break;
            }
            case 2:{
                break;
            }
            case 3:{
                break;
            }
            case 4:{
                break;
            }
        }
        this->sensor_diagram->update_sensor_count(t_count,h_count,s_count,l_count);
    }
}
void MainWindow::HandleConsoleLog(bool checked){
    if(!is_started){
        if(checked)
            this->server_process->enableConsoleLog();
        else
            this->server_process->disableConsoleLog();
    }else{
        QCheckBox *tempCheck = qobject_cast<QCheckBox*>(sender());
        if (tempCheck) {
            // Rétablir l'état précédent de la checkbox
            tempCheck->blockSignals(true);  // Bloquer les signaux pour éviter une boucle infinie
            tempCheck->setChecked(!checked); // Rétablir l'état précédent
            tempCheck->blockSignals(false); // Réactiver les signaux
        }
    }
}
void MainWindow::HandleFileLog(bool checked){
    if(!is_started){
        if(checked)
            this->server_process->enableFileLog();
        else
            this->server_process->disableFileLog();
    }else{
        QCheckBox *tempCheck = qobject_cast<QCheckBox*>(sender());
        if (tempCheck) {
            // Rétablir l'état précédent de la checkbox
            tempCheck->blockSignals(true);  // Bloquer les signaux pour éviter une boucle infinie
            tempCheck->setChecked(!checked); // Rétablir l'état précédent
            tempCheck->blockSignals(false); // Réactiver les signaux
        }
    }
}
void MainWindow::update_add_name(const QString &s){
    this->sensor_add_name = s;
}
void MainWindow::update_delete_name(const QString &s){
    this->sensor_delete_name = s;
}
void MainWindow::onToggleButtonadd(bool checked){
    if(!checked){
        return;
    }
    QRadioButton *tempButton = qobject_cast<QRadioButton*>(sender());

    if(tempButton){
        if (tempButton->text() == "Temperature ") {
            this->sensor_add_type = 1;
        } else if (tempButton->text() == "Humidité ") {
            this->sensor_add_type = 2;
        } else if (tempButton->text() == "Son ") {
            this->sensor_add_type = 3;
        } else if (tempButton->text() == "Lumière ") {
            this->sensor_add_type = 4;
        }
    }
}
void MainWindow::onToggleButtondelete(bool checked){
    if(!checked){
        return;
    }
    QRadioButton *tempButton = qobject_cast<QRadioButton*>(sender());

    if(tempButton){
        if (tempButton->text() == "Temperature ") {
            this->sensor_add_type = 1;
        } else if (tempButton->text() == "Humidité ") {
            this->sensor_add_type = 2;
        } else if (tempButton->text() == "Son ") {
            this->sensor_add_type = 3;
        } else if (tempButton->text() == "Lumière ") {
            this->sensor_add_type = 4;
        }
    }
}
void MainWindow::update_Arrow(unsigned int sensor_type){
    QPoint first_sensor = this->sensor_diagram->get_firstSensor_pos();
    QPoint space = this->sensor_diagram->get_sensor_space();
    QPoint heigth = this->sensor_diagram->get_ellipse_heigth();

    switch(sensor_type){
        case 1:{ // Temperature
            this->sensor_diagram->add_scheduler_Arrow(first_sensor,"t");
            QTimer::singleShot(500,this,[this,first_sensor,heigth](){
                this->sensor_diagram->add_server_Arrow(first_sensor + heigth,"t");
            });
            break;
        }
        case 2:{ // Humidité
            this->sensor_diagram->add_scheduler_Arrow(first_sensor + space,"h");
            QTimer::singleShot(500,this,[this,first_sensor,space,heigth](){
                this->sensor_diagram->add_server_Arrow(first_sensor + space + heigth,"h");
            });
            break;
        }
        case 3:{ // Son
            this->sensor_diagram->add_scheduler_Arrow(first_sensor + 2*space,"s");
            QTimer::singleShot(500,this,[this,first_sensor,space,heigth](){
               this->sensor_diagram->add_server_Arrow(first_sensor + 2*(space) + heigth,"s");
            });
            break;
        }
        case 4:{ // Lumière
            this->sensor_diagram->add_scheduler_Arrow(first_sensor + 3*space,"l");
            QTimer::singleShot(500,this,[this,first_sensor,space,heigth](){
                this->sensor_diagram->add_server_Arrow(first_sensor + 3*(space) + heigth,"l");
            });
            break;
        }
    }
}
void MainWindow::recieve_scheduler_message(const QString &message){
    this->consoleTextEdit->append(message);
}
void MainWindow::print_data(const QString &data){
    this->consoleTextEdit->append(data);
}
MainWindow::~MainWindow() {
}
