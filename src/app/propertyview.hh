#pragma once

#include <QTabWidget>

namespace d1::level_editor
{
    
    class PropertyView
        : public QTabWidget
    {
        Q_OBJECT
    public:

        PropertyView(
            QWidget* parent = nullptr
        );
    };
}
