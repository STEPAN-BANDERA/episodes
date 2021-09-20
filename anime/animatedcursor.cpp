#include "animatedcursor.h"

AnimatedCursor::AnimatedCursor(QWidget *parent, QString fileName)
{
     movie = new QMovie(fileName);
     movie->start();
     connect(movie, &QMovie::frameChanged, [=]{
         if (parent)
             parent->setCursor(QCursor(movie->currentPixmap(), 0, 0));
     });
}

AnimatedCursor::~AnimatedCursor()
{

}
