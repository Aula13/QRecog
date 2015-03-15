#include "filteroptionview.h"
#include "ui_filteroptionview.h"

FilterOptionView::FilterOptionView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FilterOptionView)
{
    ui->setupUi(this);
}

float FilterOptionView::getLeafSize()
{
    return ui->spnLeafSize->value();
}

bool FilterOptionView::isFilteringEnabled()
{
    return ui->chkEnableFiltering->isChecked();
}

FilterOptionView::~FilterOptionView()
{
    delete ui;
}
