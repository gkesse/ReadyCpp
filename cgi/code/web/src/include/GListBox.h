//===============================================
#ifndef _GListBox_
#define _GListBox_
//===============================================
#include "GWidget.h"
//===============================================
class GListBox : public GWidget {
public:
    GListBox();
    ~GListBox();
    // method
    void start();
    void end();
    void addItem(QString text);
    void addItem(QString text, QString link, QString icon);
};
//===============================================
#endif
//===============================================
