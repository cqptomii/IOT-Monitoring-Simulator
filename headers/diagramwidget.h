#ifndef DIAGRAMWIDGET_H
#define DIAGRAMWIDGET_H
#include <QPainter>
#include <QWidget>
#include <QObject>

class DiagramWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DiagramWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
    void add_arrow(bool scheduler,const QPoint &end,const QString &s);
    void remove_arrow(bool scheduler,const QString &s);
    void update_sensor_count(int t,int h,int s,int l);
    void draw_sensor_number(QPainter &painter,const QPoint &position, int number);
    QPoint& get_firstSensor_pos();
    QPoint& get_ellipse_heigth();
    QPoint& get_sensor_space();
private:
    QMap<QString,QLine> scheduler_arrows;
    QMap<QString,QLine> server_arrows;

    //Attributs pour l'affichages du nombre de capteurs
    unsigned int t_count = 0;
    unsigned int h_count =0;
    unsigned int s_count = 0;
    unsigned int l_count = 0;

    // Attribut pour l'affichage des fleches
    QPoint server;
    QPoint scheduler;
    QPoint firstSensor;
    QPoint ellipse_heigth;
    QPoint sensor_space;
    QPen pen;
};

#endif // DIAGRAMWIDGET_H
