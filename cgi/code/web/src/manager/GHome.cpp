//===============================================
#include "GHome.h"
#include "GWidget.h"
//===============================================
// constructor
//===============================================
GHome::GHome() {

}
//===============================================
GHome::~GHome() {
    
}
//===============================================
// method
//===============================================
void GHome::print() {    
    GWidget* lListBox = GWidget::Create("listbox");
    lListBox->start();
    lListBox->addItem("SQLite", "book");
    lListBox->addItem("OpenCV", "book");
    lListBox->end();    
}
//===============================================
