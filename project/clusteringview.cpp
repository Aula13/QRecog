#include "clusteringview.h"
#include "ui_clusteringview.h"

ClusteringView::ClusteringView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClusteringView)
{
    ui->setupUi(this);

    ui->wgtSegFileChooser->asFileOpener();
}

ClusteringView::~ClusteringView()
{
    delete ui;
}

void ClusteringView::on_btnSegment_clicked()
{
    std::string filename = ui->wgtSegFileChooser->getSelectedFile();
    if(filename.empty())
    {
        QMessageBox::warning(this, "Error", "Target file is empty", QMessageBox::Ok);
        Logger::logWarning("Clustering target file is empty");
    }

    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZRGBA>), cloud_f (new pcl::PointCloud<pcl::PointXYZRGBA>);
    pcl::io::loadPCDFile(filename, *cloud);

    PCLFilterFunction* filterf = new PCLFilterFunction();

    filterf->leafSize=ui->wgtFilterOptionView->getLeafSize();

    ui->wgtPCLViewer->updateView(filterf->filter(cloud));
}
