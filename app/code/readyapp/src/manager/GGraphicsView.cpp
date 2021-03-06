//===============================================
#include "GGraphicsView.h"
#include "GOpenCV.h"
#include "GManager.h"
//===============================================
// constructor
//===============================================
GGraphicsView::GGraphicsView(QWidget* parent) : GWidget(parent) {
    setObjectName("GGraphicsView");
    
    sGApp* lApp = GManager::Instance()->getData()->app;
    
    QPushButton* lSetting = new QPushButton;
    m_setting = lSetting;
    lSetting->setObjectName("GButton");
    lSetting->setIcon(GManager::Instance()->loadPicto(fa::cog, lApp->picto_color));
    lSetting->setText("Paramètres");
    lSetting->setCursor(Qt::PointingHandCursor);
    m_widgetId[lSetting] = "setting";
        
    QHBoxLayout* lHeaderLayout = new QHBoxLayout;
    lHeaderLayout->addWidget(lSetting);
    lHeaderLayout->setAlignment(Qt::AlignRight);
    lHeaderLayout->setMargin(0);
    lHeaderLayout->setSpacing(10);

    QMenu* lSettingMenu = new QMenu(this);
    m_settingMenu = lSettingMenu;
    lSettingMenu->addAction(GManager::Instance()->loadPicto(fa::book, lApp->picto_color), "Ouvrir une image")->setData("open_image");
    lSettingMenu->addAction(GManager::Instance()->loadPicto(fa::book, lApp->picto_color), "Enregistrer une image")->setData("save_image");
    lSettingMenu->addAction(GManager::Instance()->loadPicto(fa::book, lApp->picto_color), "Zoomer en avant (+)")->setData("zoom_in");
    lSettingMenu->addAction(GManager::Instance()->loadPicto(fa::book, lApp->picto_color), "Zoomer en arrière (-)")->setData("zoom_out");
    lSettingMenu->addAction(GManager::Instance()->loadPicto(fa::book, lApp->picto_color), "Image suivante (+)")->setData("next_image");
    lSettingMenu->addAction(GManager::Instance()->loadPicto(fa::book, lApp->picto_color), "Image précédente (-)")->setData("previous_image");
    lSettingMenu->addAction(GManager::Instance()->loadPicto(fa::book, lApp->picto_color), "Flouter une image")->setData("blur_image");
    lSettingMenu->addAction(GManager::Instance()->loadPicto(fa::book, lApp->picto_color), "Transformation affine")->setData("affine_transform");
    lSettingMenu->setCursor(Qt::PointingHandCursor);
    
    QGraphicsScene* lScene = new QGraphicsScene(this);
    m_scene = lScene;
    
    QGraphicsView* lWorkspace = new QGraphicsView(lScene);
    m_workspace = lWorkspace;
    lWorkspace->setObjectName("workspace");
    
    QVBoxLayout* lMainLayout = new QVBoxLayout;
    lMainLayout->addLayout(lHeaderLayout);
    lMainLayout->addWidget(lWorkspace);
    lMainLayout->setMargin(10);
    lMainLayout->setSpacing(10);

    setLayout(lMainLayout);

    m_state = "none";
    
    connect(lSetting, SIGNAL(clicked()), this, SLOT(slotItemClick()));
    connect(lSettingMenu, SIGNAL(triggered(QAction*)), this, SLOT(slotItemClick(QAction*)));
}
//===============================================
GGraphicsView::~GGraphicsView() {

}
//===============================================
// method
//===============================================
void GGraphicsView::showImage(QString filename) {
    if(filename == "") return;
    m_scene->clear();
    m_workspace->resetMatrix();
    QPixmap lPixmap(filename);
    m_pixmapItem = m_scene->addPixmap(lPixmap);
    m_scene->update();
    m_workspace->setSceneRect(lPixmap.rect());
    m_filename = filename;
    m_state = "open";
}
//===============================================
void GGraphicsView::showImage(const QPixmap& pixmap) {
    m_scene->clear();
    m_workspace->resetMatrix();
    m_pixmapItem = m_scene->addPixmap(pixmap);
    m_scene->update();
    m_workspace->setSceneRect(pixmap.rect());
}
//===============================================
// slot
//===============================================
void GGraphicsView::slotItemClick() {
    sGApp* lApp = GManager::Instance()->getData()->app;
    QWidget* lWidget = qobject_cast<QWidget*>(sender());
    lApp->widget_id = m_widgetId[lWidget];
    if(lApp->widget_id == "setting") {
        QPoint lPos = QCursor::pos();
        m_settingMenu->exec(lPos);
    }
}
//===============================================
void GGraphicsView::slotItemClick(QAction* action) {
    sGApp* lApp = GManager::Instance()->getData()->app;
    lApp->widget_id = action->data().toString();

    if(lApp->widget_id == "open_image") {
        QString lFilename = GManager::Instance()->openFile("Ouvrir une image", lApp->img_filter);
        showImage(lFilename);
    }
    else if(lApp->widget_id == "save_image") {
        if(m_state == "none") {return;}
        QString lFilename = GManager::Instance()->saveFile("Enregistrer une image", lApp->img_filter);
        m_pixmapItem->pixmap().save(lFilename);
    }
    else if(lApp->widget_id == "zoom_in") {
        if(m_state == "none") {return;}
        m_workspace->scale(1.2, 1.2);
    }
    else if(lApp->widget_id == "zoom_out") {
        if(m_state == "none") {return;}
        m_workspace->scale(1/1.2, 1/1.2);
    }
    else if(lApp->widget_id == "next_image") {
        if(m_state == "none") {return;}
        QString lFilename = GManager::Instance()->nextFile(
        m_filename, lApp->img_filters, "Cette image est la dernière");
        showImage(lFilename);
    }
    else if(lApp->widget_id == "previous_image") {
        if(m_state == "none") {return;}
        QString lFilename = GManager::Instance()->previousFile(
        m_filename, lApp->img_filters, "Cette image est la première");
        showImage(lFilename);
    }
    else if(lApp->widget_id == "blur_image") {
        if(m_state == "none") {return;}
        cv::Mat lMat, lTmp; QPixmap lPixmap; QImage lImg;
        lPixmap = m_pixmapItem->pixmap();
        GManager::Instance()->convertImage(lPixmap, lImg, lMat);
        cv::blur(lMat, lTmp, cv::Size(8, 8));
        GManager::Instance()->convertImage(lTmp, lImg, lPixmap);
        showImage(lPixmap);
    }
    else if(lApp->widget_id == "affine_transform") {
        if(m_state == "none") {return;}
        cv::Mat lMat, lTmp; QPixmap lPixmap; QImage lImg;
        lPixmap = m_pixmapItem->pixmap();
        GManager::Instance()->convertImage(lPixmap, lImg, lMat);
        GOpenCV::Instance()->affineTransform(lMat, lTmp);
        GManager::Instance()->convertImage(lTmp, lImg, lPixmap);
        showImage(lPixmap);
    }
}
//===============================================
