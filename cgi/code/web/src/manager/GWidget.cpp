//===============================================
#include "GWidget.h"
#include "GHeader.h"
#include "GFooter.h"
//===============================================
// constructor
//===============================================
GWidget::GWidget() {

}
//===============================================
GWidget::~GWidget() {
    
}
//===============================================
GWidget* GWidget::Create(std::string key) {
    if(key =="widget") {return new GWidget;}
    if(key =="header") {return new GHeader;}
    if(key =="footer") {return new GFooter;}
    return new GWidget;
}
//===============================================
// method
//===============================================
void GWidget::print() {}
//===============================================
