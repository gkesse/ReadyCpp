//===============================================
#include "GListBox.h"
//===============================================
// constructor
//===============================================
GListBox::GListBox() {

}
//===============================================
GListBox::~GListBox() {
    
}
//===============================================
// method
//===============================================
void GListBox::start() {
    printf("<div class='listbox'>\n");
}
//===============================================
void GListBox::end() {
    printf("</div>\n");
}
//===============================================
void GListBox::addItem(std::string text) {
    printf("<div>%s</div>\n", text.c_str());
}
//===============================================
