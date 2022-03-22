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

class mainWindow: public QFrame
{
public:
    explicit mainWindow();
    void paintEvent(QPaintEvent *event) override;
};

//обработка события перерисования окна
void mainWindow::paintEvent(QPaintEvent *event)
{

    QPainter p(this); //объект для рисования
    int x=this->width()/2, y=this->height()/2; //центр окан
    p.setPen (QPen(Qt::blue,Qt::SolidLine)); //цвет и тип пера
    p.drawLine(0, y, 2*x, y); p.drawLine(x, 0, x, 2*y); //координатные оси
    QRect rect(x-20, y, 20, 20); //прямоугольник для текста
    p.setPen (QPen(Qt::red,Qt::SolidLine));
    p.setFont(QFont("Arial",-1,-1, false)); //зададим свойства шрифта
    p.drawText(rect, Qt::AlignCenter, "0");
    p.setPen (QPen(QColor(0,100,50,255),Qt::SolidLine*2));
/*построение графика*/
    for(int i =0;i<x_pos.size()-1;i++){
        p.drawLine(x_pos[i]+x,y-y_pos[i],x_pos[i+1]+x,y-y_pos[i+1]);
    }
}


mainWindow::mainWindow()
{
/* определяем свойства окна */
    this->resize(1000,600);
    this->setWindowTitle("Model");
    QPalette pl; //объект палитра необходим для заданимя фона окна
    pl.setColor(QPalette::Background, QColor(226, 226, 226)); //определить цвет
    this->setAutoFillBackground(true); //фон окна заливается автоматически
    this->setPalette(pl); //устанавливаем фон окна
}
double abs_f(double a){
    if (a>0){
        return a;
    } else return -a;
}
void simulate(int &num, double velocity, double mass, double p, double alpha, double delta_t,double distance)
{
    std::vector<double> r;
    r.resize(num);
    std::vector<double> phi;
    phi.resize(num);

    r[0]=sqrt(distance * distance + p * p);
    r[1]= sqrt((distance-velocity*delta_t) * (distance-velocity * delta_t) + p * p);

    phi[0]=atan(distance/p)+M_PI/2;
    phi[1]= acos(p/r[1])+M_PI/2;


    for(int i = 2 ; i < num; ++i){
        r[i] =abs_f((-alpha / (r[i-2] * r[i-2]) * (delta_t *  delta_t) + (2 * r[i-1]) - r[i-2]) / mass) ;

        phi[i] = 2* phi[i-1] - phi[i-2];
    }
    for(int i=0; i < num; ++i){
        double x = r[i]*cos(phi[i]);
        x_pos.push_back(x);

        double y = r[i]*sin(phi[i]);
        y_pos.push_back(y);
    }
}


int main(int argc, char *argv[]) {

    double velocity=100,
            mass=1,
            p=50,
            alpha=0.005,
            delta_t=0.01,
            distance=500;
    int num=1000;

    simulate(num, velocity,mass,p,alpha,delta_t,distance);
    for(auto i:x_pos){
        qDebug()<<i;
    }

    QApplication app(argc, argv);
    auto * sw = new mainWindow();
    sw->show();
    return QApplication::exec();
}

