#include "headers/diagramwidget.h"
#include <QTimer>

DiagramWidget::DiagramWidget(QWidget *parent)
    : QWidget{parent}
{}
void DiagramWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    pen.setColor(Qt::white);
    pen.setWidth(3);
    painter.setPen(pen);

    int widget_width = width();  // Largeur de la zone de dessin
    int widget_height = height();  // Hauteur de la zone de dessin

    int rect_width = width()/5;  // Taille des carrés
    int rect_heigth = height()/5;
    int ellipse_width = rect_width;  // Diamètre des cercles
    this->ellipse_heigth = QPoint(0,rect_heigth);

    int margin = 20;  // Espace entre les formes
    int total_rect_width = rect_width + margin;
    int total_rect_height = rect_heigth + margin;
    int total_circle_width = 4* ellipse_width + 3 * margin;

    // Calculer les positions x pour centrer les carrés
    int square_x_start = (widget_width - total_rect_width) / 2;

    // Calculer les positions x pour centrer les cercles
    int circle_x_start = (widget_width - total_circle_width) / 2;

    // Position y pour les carrés et les cercles
    int server_y = (widget_height - total_rect_height);
    int schedule_y = (server_y - 2*rect_heigth - ellipse_heigth.ry() - 2 * margin) / 2;
    int circle_y = (server_y - schedule_y) / 2 ;

    this->scheduler = QPoint(square_x_start + rect_width/2,schedule_y + rect_heigth);
    this->server = QPoint(square_x_start + rect_width/2,server_y);

    QRect Scheduler(square_x_start,schedule_y,rect_width,rect_heigth);
    QRect Server(square_x_start,server_y,rect_width,rect_heigth);

    // Dessiner le Scheduler
    painter.drawRect(Scheduler);
    painter.drawText(Scheduler,Qt::AlignCenter, "Scheduler");

    // Dessiner le Server
    painter.drawRect(Server);
    painter.drawText(Server,Qt::AlignCenter, "Server");

    this->firstSensor = QPoint(circle_x_start + ellipse_width/2,circle_y);
    this->sensor_space = QPoint(ellipse_width + margin,0);
    QRect tsensor(circle_x_start,circle_y,ellipse_width,ellipse_heigth.ry());
    QRect hsensor(circle_x_start+ellipse_width+margin,circle_y,ellipse_width,ellipse_heigth.ry());
    QRect ssensor(circle_x_start + 2 * (ellipse_width + margin), circle_y, ellipse_width, ellipse_heigth.ry());
    QRect lsensor(circle_x_start + 3 * (ellipse_width + margin), circle_y, ellipse_width, ellipse_heigth.ry());
    // Dessiner les cercles pour les capteurs
    painter.drawEllipse(tsensor);  // Cercle 1
    painter.drawText(tsensor,Qt::AlignCenter, "Capteurs de température");

    painter.drawEllipse(hsensor);  // Cercle 2
    painter.drawText(hsensor,Qt::AlignCenter, "Capteurs d'humidité");

    painter.drawEllipse(ssensor);  // Cercle 3
    painter.drawText(ssensor,Qt::AlignCenter, "Capteurs de son");

    painter.drawEllipse(lsensor);  // Cercle 4
    painter.drawText(lsensor,Qt::AlignCenter, "Capteurs de lumière");

    ///
    /// Affichage du nombre de capteurs
    ///

    this->draw_sensor_number(painter,firstSensor+ellipse_heigth,t_count);
    this->draw_sensor_number(painter,firstSensor+sensor_space + ellipse_heigth,h_count);
    this->draw_sensor_number(painter,firstSensor+2*sensor_space + ellipse_heigth,s_count);
    this->draw_sensor_number(painter,firstSensor+3*sensor_space + ellipse_heigth,l_count);

    ///
    /// Affichage des lignes entre le diagramme
    ///
    pen.setWidth(2);
    pen.setColor(Qt::red);
    painter.setPen(pen);
    for(QMap<QString,QLine>::Iterator it = scheduler_arrows.begin(); it != scheduler_arrows.end(); it++){
        painter.drawLine(it.value());
    }
    pen.setColor(Qt::blue);
    painter.setPen(pen);
    for(QMap<QString,QLine>::Iterator it = server_arrows.begin(); it != server_arrows.end(); it++){
        painter.drawLine(it.value());
    }
}
void DiagramWidget::add_scheduler_Arrow(const QPoint &end,const QString &s){
    scheduler_arrows.insert(s,QLine(this->scheduler,end));
    update();
    QTimer::singleShot(1000,this, [this,s](){remove_scheduler_arrow(s);} );
}
void DiagramWidget::add_server_Arrow(const QPoint &end,const QString &s){
    server_arrows.insert(s,QLine(this->server,end));
    update();
    QTimer::singleShot(1000,this, [this,s](){remove_server_arrow(s);} );
}
void DiagramWidget::remove_scheduler_arrow(const QString &s){
    scheduler_arrows.remove(s);
    qDebug() << "Remove arrow";
    update();
}
void DiagramWidget::remove_server_arrow(const QString &s){
    server_arrows.remove(s);
    update();
}
QPoint& DiagramWidget::get_firstSensor_pos(){
    return this->firstSensor;
}
QPoint& DiagramWidget::get_ellipse_heigth(){
    return ellipse_heigth;
}
QPoint& DiagramWidget::get_sensor_space(){
    return sensor_space;
}
void DiagramWidget::update_sensor_count(int t,int h,int s,int l){
    t_count = t;
    h_count = h;
    s_count = s;
    l_count = l;
    update();
}
void DiagramWidget::draw_sensor_number(QPainter &painter, const QPoint &position, int number) {
    // Position du texte (juste en dessous du capteur)
    QPoint text_position = position + QPoint(0, - 50); // Décalage de 20 pixels vers le bas
    QString number_text = QString::number(number);
    painter.drawText(text_position, number_text);
}
