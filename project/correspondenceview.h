#ifndef CORRESPONDENCEVIEW_H
#define CORRESPONDENCEVIEW_H

#include <QWidget>

namespace Ui {
class CorrespondenceView;
}

class CorrespondenceView : public QWidget
{
    Q_OBJECT

public:
    explicit CorrespondenceView(QWidget *parent = 0);
    ~CorrespondenceView();

private slots:
    void on_chkDisableUpdate_stateChanged(int arg1);

private:
    Ui::CorrespondenceView *ui;
};

#endif // CORRESPONDENCEVIEW_H
