#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QDebug>
#include <cmath>
#include <QPainter>
#include <QtMath>


std::vector<double> x_pos;
std::vector<double> y_pos;
void simulate(int &num, double velocity, double mass, double p, double alpha, double delta_t,double distance)
{
    std::vector<double> r;
    r.resize(num);
    std::vector<double> phi;
    phi.resize(num);

    r[0]=sqrt(distance * distance + p * p);
    r[1]= sqrt((distance-velocity*delta_t) * (distance-velocity * delta_t) + p * p);

    phi[0]= atan(p/distance);
    phi[1]= asin(p/r[1]);


    for(int i = 2 ; i < num; ++i){
        r[i] =(-alpha*delta_t*delta_t)/(mass*r[i-2]*r[i-2]) + 2*r[i-1] - r[i-2];
        qDebug()<<r[i];

        phi[i] = 2* phi[i-1] - phi[i-2];
    }
    for(int i=0; i < num; ++i){
        double x = -r[i]*cos(phi[i]);
        x_pos.push_back(x);

        double y = r[i]*sin(phi[i]);
        y_pos.push_back(y);
    }
}

class mainWindow: public QFrame
{
public:
    explicit mainWindow();
    void paintEvent(QPaintEvent *event) override;
    
private:

};

//обработка события перерисования окна
void mainWindow::paintEvent(QPaintEvent *event)
{

    QPainter painter(this); //объект для рисования
    int x=this->width()/2, y=this->height()/2; //центр окан
    painter.setPen (QPen(Qt::blue, Qt::SolidLine)); //цвет и тип пера
    painter.drawLine(0, y, 2 * x, y); painter.drawLine(x, 0, x, 2 * y); //координатные оси
    QRect rect(x-20, y, 20, 20); //прямоугольник для текста
    painter.setPen (QPen(Qt::red, Qt::SolidLine));
    painter.setFont(QFont("Arial", -1, -1, false)); //зададим свойства шрифта
    painter.drawText(rect, Qt::AlignCenter, "0");
    painter.setPen (QPen(QColor(0, 100, 50, 255), Qt::SolidLine * 2));
/*построение графика*/

    for(int i =0;i<x_pos.size()-1;i++){
        painter.drawLine(x_pos[i] + x, y - y_pos[i], x_pos[i + 1] + x, y - y_pos[i + 1]);
    }
}


mainWindow::mainWindow()
{
    auto m_layout = new QVBoxLayout(this);

/* определяем свойства окна */
    this->resize(1000,600);
    this->setWindowTitle("Model");
    QPalette pl; //объект палитра необходим для заданимя фона окна
    pl.setColor(QPalette::Background, QColor(226, 226, 226)); //определить цвет
    this->setAutoFillBackground(true); //фон окна заливается автоматически
    this->setPalette(pl); //устанавливаем фон окна
    this->setLayout(m_layout);
    
   
}


int main(int argc, char *argv[]) {

    double velocity=150,
            mass=1000,
            p=100,
            alpha=0,
            delta_t=0.1,
            distance=500;
    int num=10000;

    simulate(num, velocity, mass, p, alpha, delta_t, distance);


    QApplication app(argc, argv);
    auto * sw = new mainWindow();

    sw->show();
    return QApplication::exec();
}

