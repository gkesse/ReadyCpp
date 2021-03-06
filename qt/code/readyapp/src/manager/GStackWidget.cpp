//===============================================
#include "GStackWidget.h"
//===============================================
// constructor
//===============================================
GStackWidget::GStackWidget(QWidget* parent) : GWidget(parent)  {
    setObjectName("GStackWidget");
    
    QStackedWidget* lWorkspace = new QStackedWidget;
    m_workspace = lWorkspace;
    
    QHBoxLayout* lMainLayout = new QHBoxLayout;
    lMainLayout->addWidget(lWorkspace);
    lMainLayout->setMargin(0);
    lMainLayout->setSpacing(0);

    setLayout(lMainLayout);   

    m_defaultKeyFlag = true;
    m_defaultKey = "";
}
//===============================================
GStackWidget::~GStackWidget() {
    
}
//===============================================
// methods
//===============================================
void GStackWidget::addPage(QString key, QString title, QWidget* widget, bool isDefault) {
    int lPageId = m_workspace->count();
    m_pageId[key] = lPageId;
    m_titleMap[key] = title;
    m_workspace->addWidget(widget);
    
    if(m_defaultKeyFlag == true) {m_defaultKey = key;m_defaultKeyFlag = false;}
    
    if(isDefault == 1) {
        m_defaultKey = key;
        setPage(key);
    }
}
//===============================================
void GStackWidget::setPage(QString key) {
    int lPageId = m_pageId.value(key, -1);
    if(lPageId == -1) {return;}
    getPage(key)->loadPage();
    m_workspace->setCurrentIndex(lPageId);
}
//===============================================
GWidget* GStackWidget::getPage(QString key) {
    int lPageId = m_pageId.value(key, -1);
    if(lPageId == -1) {return 0;}
    QWidget* lWidget = m_workspace->widget(lPageId);
    GWidget* lPage = qobject_cast<GWidget*>(lWidget);
    return lPage;
}
//===============================================
int GStackWidget::getPageId(QString key) {
    int lPageId = m_pageId.value(key, -1);
    return lPageId;
}
//===============================================
QWidget* GStackWidget::getWidget(QString key) {
    int lPageId = m_pageId.value(key, -1);
    if(lPageId == -1) {return 0;}
    QWidget* lWidget = m_workspace->widget(lPageId);
    return lWidget;
}
//===============================================
QString GStackWidget::getTitle(QString key) {
    QString lTitle = m_titleMap.value(key, "");
    return lTitle;
}
//===============================================
QString GStackWidget::getDefaultKey() {
    return m_defaultKey;
}
//===============================================
// callback
//===============================================
QSize GStackWidget::sizeHint() const {
    if(m_workspace->count() == 0) return QSize(0, 0);
    return m_workspace->currentWidget()->sizeHint();
}
//===============================================
QSize GStackWidget::minimumSizeHint() const {
    if(m_workspace->count() == 0) return QSize(0, 0);
    return m_workspace->currentWidget()->minimumSizeHint();
}
//===============================================