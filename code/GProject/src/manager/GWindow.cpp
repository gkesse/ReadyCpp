//===============================================
#include "GWindow.h"
#include "GAdminQt.h"
#include "GSQLiteQt.h"
#include "GOpenCVQt.h"
#include "GJson.h"
#include "GManager.h"
//===============================================
GWindow::GWindow(QWidget* parent) : 
QFrame(parent) {
    sGManager* lMgr = GManager::Instance()->dataGet();
    sGQt* lQt = lMgr->qt;
    createPage();
    setWindowTitle(lQt->title);
    resize(lQt->width, lQt->height);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);
}
//===============================================
GWindow::~GWindow() {

}
//===============================================
void GWindow::createPage() {
    sGManager* lMgr = GManager::Instance()->dataGet();
    sGQt* lQt = lMgr->qt;
    lQt->page = new QStackedWidget;
    QVBoxLayout* lMainL = new QVBoxLayout;
    GAdminQt* lAdmin = new GAdminQt;
    GSQLiteQt* lSQLite = new GSQLiteQt;
    GOpenCVQt* lOpenCV = new GOpenCVQt;
    lQt->page->addWidget(lAdmin);
    lQt->page->addWidget(lSQLite);
    lQt->page->addWidget(lOpenCV);
    lMainL->addWidget(lQt->page);
    setLayout(lMainL);
}
//===============================================