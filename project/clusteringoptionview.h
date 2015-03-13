#ifndef CLUSTERINGOPTION_H
#define CLUSTERINGOPTION_H

#include <QWidget>

namespace Ui {
class ClusteringOptionView;
}

class ClusteringOptionView : public QWidget
{
    Q_OBJECT

public:
    explicit ClusteringOptionView(QWidget *parent = 0);
    ~ClusteringOptionView();

private:
    Ui::ClusteringOptionView *ui;
};

#endif // CLUSTERINGOPTION_H
