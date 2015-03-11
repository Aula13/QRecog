#ifndef PLCVIEWER_H
#define PLCVIEWER_H

#include <QWidget>

namespace Ui {
class PLCViewer;
}

class PLCViewer : public QWidget
{
    Q_OBJECT

public:
    explicit PLCViewer(QWidget *parent = 0);
    ~PLCViewer();

private:
    Ui::PLCViewer *ui;
};

#endif // PLCVIEWER_H
