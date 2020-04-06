//===============================================
#include "GWindow.h"
#include "GWindowMath.h"
//===============================================
GWindow::GWindow(QWidget* parent) {
	__CLASSNAME__ = __FUNCTION__;
}
//===============================================
GWindow::~GWindow() {

}
//===============================================
GWindow* GWindow::Create(string key) {
	if(key == "math") return new GWindowMath;
	return new GWindowMath;
}
//===============================================
