#ifndef FILTERVIEW_H
#define FILTERVIEW_H

#include <QWidget>

namespace Ui {
class FilterOptionView;
}

class FilterOptionView : public QWidget
{
    Q_OBJECT

public:
    explicit FilterOptionView(QWidget *parent = 0);

    float getLeafSize();

    ~FilterOptionView();

private:
    Ui::FilterOptionView *ui;
};

#endif // FILTERVIEW_H
