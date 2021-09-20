#ifndef ANIMATEDCURSOR_H
#define ANIMATEDCURSOR_H

#include <QMovie>
#include <QCursor>
#include <QWidget>

class AnimatedCursor : public QObject
{
     Q_OBJECT
public:
     AnimatedCursor(QWidget *parent = 0, QString fileName = "");
     ~AnimatedCursor();

private:
     QMovie *movie;
};

#endif // ANIMATEDCURSOR_H
