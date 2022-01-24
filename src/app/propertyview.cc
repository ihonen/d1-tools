#include "app//propertyview.hh"

// -----------------------------------------------------------------------------

PropertyView::PropertyView(QWidget* parent)
    : QTabWidget(parent)
{
    setTabPosition(QTabWidget::West);
    addTab(new QWidget, "AI");
    addTab(new QWidget, "BGND");
    addTab(new QWidget, "BOND");
    addTab(new QWidget, "BUIL");
    addTab(new QWidget, "CART");
    addTab(new QWidget, "DLGS");
    addTab(new QWidget, "ELEM");
    addTab(new QWidget, "FXBK");
    addTab(new QWidget, "JUMP");
    addTab(new QWidget, "LIFT");
    addTab(new QWidget, "MASK");
    addTab(new QWidget, "MAT");
    addTab(new QWidget, "MISC");
    addTab(new QWidget, "MOVE");
    addTab(new QWidget, "MSIC");
    addTab(new QWidget, "PAT");
    addTab(new QWidget, "SCRP");
    addTab(new QWidget, "SGHT");
    addTab(new QWidget, "SND");
    addTab(new QWidget, "WAYS");
}
