#include <QtWidgets>
#include <QtMath>
#include <complex>

typedef std::complex<double> complexd;

template<typename T>
inline T lerp(T a, T b, T t)
{
    return a * (1 - t) + b * t;
}


#define RECALC_DELAY 200
#define SCROLL_SENSITIVITY 0.1

class MandelbrotWindow : public QWidget
{
private:
    QImage frame;
    QRect view_src_rect;
    complexd c_center, top_left, bottom_right;
    double half_width = 1.0;

    QPoint prev_mouse_pos;

    QTimer recalc_timer;

    void resizeEvent(QResizeEvent *event) override
    {
        QImage new_frame = QImage(width(), height(), QImage::Format_Grayscale8);
        new_frame.fill(0);
        frame = new_frame;

        update_corner_coords();
        recalc_timer.start();
    }

    void mousePressEvent(QMouseEvent *event) override
    {
        prev_mouse_pos = event->pos();
    }

    void mouseMoveEvent(QMouseEvent *event) override
    {
        if(!(event->buttons() & Qt::LeftButton)) return;

        prev_mouse_pos -= event->pos();
        complexd pan = frame_coords_to_complex(prev_mouse_pos) - top_left;
        c_center += pan;
        view_src_rect.moveTo(view_src_rect.topLeft() + prev_mouse_pos);
        prev_mouse_pos = event->pos();

        update();
    }

    void mouseReleaseEvent(QMouseEvent *event) override
    {
        update_corner_coords();
        recalculate();
    }

    void wheelEvent(QWheelEvent *event) override
    {
        complexd c_mouse = frame_coords_to_complex(event->pos());
        double scale_factor = qPow(2, (qreal)event->angleDelta().y() / 1200);

        c_center = (c_center - c_mouse) * scale_factor + c_mouse;
        half_width = half_width * scale_factor;

        view_src_rect.setTopLeft((view_src_rect.topLeft() - event->pos()) * scale_factor + event->pos());
        view_src_rect.setBottomRight((view_src_rect.bottomRight() - event->pos()) * scale_factor + event->pos());

        update_corner_coords();
        recalc_timer.start();
        update();
    }

    void paintEvent(QPaintEvent *event) override
    {
        QPainter p(this);

        p.drawImage(rect(), frame, view_src_rect);
    }

    void recalculate()
    {
        for(QPoint pt; pt.y() < frame.height(); pt.setY(pt.y() + 1))
        {
            for(pt.setX(0); pt.x() < frame.width(); pt.setX(pt.x() + 1))
            {
                char val = mandelbrot_iter(frame_coords_to_complex(pt), 150);
                frame.setPixel(pt, qRgb(val, val, val));
            }
            view_src_rect = frame.rect();
        }

        view_src_rect = frame.rect();

        update();
    }

    unsigned char mandelbrot_iter(complexd c, unsigned int max_iter)
    {
        complexd z = c;
        unsigned char result = 0;

        for(unsigned int i = 1; i <= max_iter; i++)
        {
            double re2 = z.real() * z.real();
            double im2 = z.imag() * z.imag();
            if(re2 + im2 > 4)
            {
                result = 1 + i * 254 / max_iter;
                break;
            }

            //(a+bi)^2 + c + di = a*a-b*b+c + (2*a*b+d)*i
            z.imag(2 * z.real() * z.imag() + c.imag());
            z.real(re2 - im2 + c.real());
        }

        return result;
    }

    void update_corner_coords()
    {
        complexd diag(half_width, half_width * frame.height() / frame.width());
        top_left = c_center - diag;
        bottom_right = c_center + diag;
    }

    complexd frame_coords_to_complex(QPoint point)
    {
        complexd result;
        result.real(lerp<double>(top_left.real(), bottom_right.real(), (double)point.x() / frame.width()));
        result.imag(lerp<double>(top_left.imag(), bottom_right.imag(), (double)point.y() / frame.height()));

        return result;
    }

    QPoint complex_coords_to_frame(complexd point)
    {
        point -= top_left;
        complexd b = bottom_right - top_left;
        QPoint result;
        result.setX((int)lerp<double>(0, frame.width(), point.real() / b.real()));
        result.setY((int)lerp<double>(0, frame.height(), point.imag() / b.imag()));

        return result;
    }

public:
    explicit MandelbrotWindow(QWidget *parent = nullptr)
        : QWidget(parent), recalc_timer(this)
    {
        setWindowTitle("Mandelbrot set");
        resize(800, 600);

        recalc_timer.setSingleShot(true);
        recalc_timer.setInterval(RECALC_DELAY);
        connect(&recalc_timer, &QTimer::timeout, this, [this](){ recalculate(); });
    }
};


int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    MandelbrotWindow window;
    window.show();

    return app.exec();
}
