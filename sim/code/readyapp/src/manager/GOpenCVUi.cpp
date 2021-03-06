//===============================================
#include "GOpenCVUi.h"
#include "GOpenCVMg.h"
#include "GConfig.h"
#include "GProcess.h"
#include "GManager.h"
//===============================================
GOpenCVUi* GOpenCVUi::m_instance = 0;
//===============================================
GOpenCVUi::GOpenCVUi() {
    
}
//===============================================
GOpenCVUi::~GOpenCVUi() {
    
}
//===============================================
GOpenCVUi* GOpenCVUi::Instance() {
    if(m_instance == 0) {
        m_instance = new GOpenCVUi;
    }
    return m_instance;
}
//===============================================
void GOpenCVUi::run(int argc, char** argv) {
    G_STATE = "S_INIT";
    while(1) {
        if(G_STATE == "S_ADMIN") run_ADMIN(argc, argv);
        else if(G_STATE == "S_INIT") run_INIT(argc, argv);
        else if(G_STATE == "S_METHOD") run_METHOD(argc, argv);
        else if(G_STATE == "S_CHOICE") run_CHOICE(argc, argv);
        // image
        else if(G_STATE == "S_IMAGE_LOAD_IMAGE_PATH") run_IMAGE_LOAD_IMAGE_PATH(argc, argv);
        else if(G_STATE == "S_IMAGE_LOAD_IMAGE_NAME") run_IMAGE_LOAD_IMAGE_NAME(argc, argv);
        else if(G_STATE == "S_IMAGE_LOAD") run_IMAGE_LOAD(argc, argv);
        //
        else if(G_STATE == "S_IMAGE_INVERT_IMAGE_PATH") run_IMAGE_INVERT_IMAGE_PATH(argc, argv);
        else if(G_STATE == "S_IMAGE_INVERT_IMAGE_NAME") run_IMAGE_INVERT_IMAGE_NAME(argc, argv);
        else if(G_STATE == "S_IMAGE_INVERT") run_IMAGE_INVERT(argc, argv);
        // video
        else if(G_STATE == "S_VIDEO_LOAD_VIDEO_PATH") run_VIDEO_LOAD_VIDEO_PATH(argc, argv);
        else if(G_STATE == "S_VIDEO_LOAD_VIDEO_NAME") run_VIDEO_LOAD_VIDEO_NAME(argc, argv);
        else if(G_STATE == "S_VIDEO_LOAD") run_VIDEO_LOAD(argc, argv);
        //
        else if(G_STATE == "S_SAVE") run_SAVE(argc, argv);
        else if(G_STATE == "S_LOAD") run_LOAD(argc, argv);
        else if(G_STATE == "S_QUIT") run_QUIT(argc, argv);
        else break;
    }
}
//===============================================
void GOpenCVUi::run_ADMIN(int argc, char** argv) {
    GProcess::Instance()->run(argc, argv);
    G_STATE = "S_END";
}
//===============================================
void GOpenCVUi::run_INIT(int argc, char** argv) {
    printf("\n");
    printf("%s\n", "CPP_OPENCV !!!");
    printf("\t%-2s : %s\n", "-q", "quitter l'application");
    printf("\t%-2s : %s\n", "-i", "reinitialiser l'application");
    printf("\t%-2s : %s\n", "-a", "redemarrer l'application");
    printf("\t%-2s : %s\n", "-v", "valider les configurations");
    G_STATE = "S_LOAD";
}
//===============================================
void GOpenCVUi::run_METHOD(int argc, char** argv) {
    printf("\n");
    printf("%s\n", "CPP_OPENCV :");
    printf("\t%-2s : %s\n", "1", "charger une image");
    printf("\t%-2s : %s\n", "2", "inverser une image");
    printf("\n");
    printf("\t%-2s : %s\n", "10", "charger une video");
    printf("\n");
    G_STATE = "S_CHOICE";
}
//===============================================
void GOpenCVUi::run_CHOICE(int argc, char** argv) {
    std::string lLast = GConfig::Instance()->getData("G_OPENCV_ID").toStdString();
    printf("CPP_OPENCV (%s) ? : ", lLast.c_str());
    std::string lAnswer; std::getline(std::cin, lAnswer);
    if(lAnswer == "") lAnswer = lLast;
    if(lAnswer == "-q") G_STATE = "S_END";
    else if(lAnswer == "-i") G_STATE = "S_INIT";
    else if(lAnswer == "-a") G_STATE = "S_ADMIN";
    //
    else if(lAnswer == "1") {G_STATE = "S_IMAGE_LOAD_IMAGE_PATH"; GConfig::Instance()->setData("G_OPENCV_ID", lAnswer.c_str());}
    else if(lAnswer == "2") {G_STATE = "S_IMAGE_INVERT_IMAGE_PATH"; GConfig::Instance()->setData("G_OPENCV_ID", lAnswer.c_str());}
    //
    else if(lAnswer == "10") {G_STATE = "S_VIDEO_LOAD_VIDEO_PATH"; GConfig::Instance()->setData("G_OPENCV_ID", lAnswer.c_str());}
    //
}
//===============================================
void GOpenCVUi::run_IMAGE_LOAD_IMAGE_PATH(int argc, char** argv) {
    std::string lLast = GConfig::Instance()->getData("G_IMAGE_PATH").toStdString();
    printf("G_IMAGE_PATH (%s) ? : ", lLast.c_str());
    std::string lAnswer; std::getline(std::cin, lAnswer);
    if(lAnswer == "") lAnswer = lLast;
    if(lAnswer == "-q") G_STATE = "S_END";
    else if(lAnswer == "-i") G_STATE = "S_INIT";
    else if(lAnswer == "-a") G_STATE = "S_ADMIN";
    else if(lAnswer == "-v") G_STATE = "S_IMAGE_LOAD";
    else if(lAnswer != "") {G_STATE = "S_IMAGE_LOAD_IMAGE_NAME"; GConfig::Instance()->setData("G_IMAGE_PATH", lAnswer.c_str());}
}
//===============================================
void GOpenCVUi::run_IMAGE_LOAD_IMAGE_NAME(int argc, char** argv) {
    std::string lLast = GConfig::Instance()->getData("G_IMAGE_NAME").toStdString();
    printf("G_IMAGE_NAME (%s) ? : ", lLast.c_str());
    std::string lAnswer; std::getline(std::cin, lAnswer);
    if(lAnswer == "") lAnswer = lLast;
    if(lAnswer == "-q") G_STATE = "S_END";
    else if(lAnswer == "-i") G_STATE = "S_INIT"; 
    else if(lAnswer == "-a") G_STATE = "S_ADMIN";
    else if(lAnswer == "-v") G_STATE = "S_IMAGE_LOAD";
    else if(lAnswer != "") {G_STATE = "S_IMAGE_LOAD"; GConfig::Instance()->setData("G_IMAGE_NAME", lAnswer.c_str());}
}
//===============================================
void GOpenCVUi::run_IMAGE_LOAD(int argc, char** argv) {
    sGApp* lApp = GManager::Instance()->getData()->app;
    printf("\n");
    printf("%s\n", __FUNCTION__);
    QString lImagePath = "";
    lImagePath += GConfig::Instance()->getData("G_IMAGE_PATH");
    lImagePath += lApp->path_sep;
    lImagePath += GConfig::Instance()->getData("G_IMAGE_NAME");
    printf("%s\n", lImagePath.toStdString().c_str());
    GOpenCVMg::Instance()->loadImage(lImagePath);
    G_STATE = "S_SAVE";
}
//===============================================
void GOpenCVUi::run_IMAGE_INVERT_IMAGE_PATH(int argc, char** argv) {
    std::string lLast = GConfig::Instance()->getData("G_IMAGE_PATH").toStdString();
    printf("G_IMAGE_PATH (%s) ? : ", lLast.c_str());
    std::string lAnswer; std::getline(std::cin, lAnswer);
    if(lAnswer == "") lAnswer = lLast;
    if(lAnswer == "-q") G_STATE = "S_END";
    else if(lAnswer == "-i") G_STATE = "S_INIT";
    else if(lAnswer == "-a") G_STATE = "S_ADMIN";
    else if(lAnswer == "-v") G_STATE = "S_IMAGE_INVERT";
    else if(lAnswer != "") {G_STATE = "S_IMAGE_INVERT_IMAGE_NAME"; GConfig::Instance()->setData("G_IMAGE_PATH", lAnswer.c_str());}
}
//===============================================
void GOpenCVUi::run_IMAGE_INVERT_IMAGE_NAME(int argc, char** argv) {
    std::string lLast = GConfig::Instance()->getData("G_IMAGE_NAME").toStdString();
    printf("G_IMAGE_NAME (%s) ? : ", lLast.c_str());
    std::string lAnswer; std::getline(std::cin, lAnswer);
    if(lAnswer == "") lAnswer = lLast;
    if(lAnswer == "-q") G_STATE = "S_END";
    else if(lAnswer == "-i") G_STATE = "S_INIT"; 
    else if(lAnswer == "-a") G_STATE = "S_ADMIN";
    else if(lAnswer == "-v") G_STATE = "S_IMAGE_INVERT";
    else if(lAnswer != "") {G_STATE = "S_IMAGE_INVERT"; GConfig::Instance()->setData("G_IMAGE_NAME", lAnswer.c_str());}
}
//===============================================
void GOpenCVUi::run_IMAGE_INVERT(int argc, char** argv) {
    sGApp* lApp = GManager::Instance()->getData()->app;
    printf("\n");
    printf("%s\n", __FUNCTION__);
    QString lImagePath = "";
    lImagePath += GConfig::Instance()->getData("G_IMAGE_PATH");
    lImagePath += lApp->path_sep;
    lImagePath += GConfig::Instance()->getData("G_IMAGE_NAME");
    printf("%s\n", lImagePath.toStdString().c_str());
    GOpenCVMg::Instance()->invertImage(lImagePath);
    G_STATE = "S_SAVE";
}
//===============================================
void GOpenCVUi::run_VIDEO_LOAD_VIDEO_PATH(int argc, char** argv) {
    std::string lLast = GConfig::Instance()->getData("G_VIDEO_PATH").toStdString();
    printf("G_VIDEO_PATH (%s) ? : ", lLast.c_str());
    std::string lAnswer; std::getline(std::cin, lAnswer);
    if(lAnswer == "") lAnswer = lLast;
    if(lAnswer == "-q") G_STATE = "S_END";
    else if(lAnswer == "-i") G_STATE = "S_INIT";
    else if(lAnswer == "-a") G_STATE = "S_ADMIN";
    else if(lAnswer == "-v") G_STATE = "S_VIDEO_LOAD";
    else if(lAnswer != "") {G_STATE = "S_VIDEO_LOAD_VIDEO_NAME"; GConfig::Instance()->setData("G_VIDEO_PATH", lAnswer.c_str());}
}
//===============================================
void GOpenCVUi::run_VIDEO_LOAD_VIDEO_NAME(int argc, char** argv) {
    std::string lLast = GConfig::Instance()->getData("G_VIDEO_NAME").toStdString();
    printf("G_VIDEO_NAME (%s) ? : ", lLast.c_str());
    std::string lAnswer; std::getline(std::cin, lAnswer);
    if(lAnswer == "") lAnswer = lLast;
    if(lAnswer == "-q") G_STATE = "S_END";
    else if(lAnswer == "-i") G_STATE = "S_INIT"; 
    else if(lAnswer == "-a") G_STATE = "S_ADMIN";
    else if(lAnswer == "-v") G_STATE = "S_VIDEO_LOAD";
    else if(lAnswer != "") {G_STATE = "S_VIDEO_LOAD"; GConfig::Instance()->setData("G_VIDEO_NAME", lAnswer.c_str());}
}
//===============================================
void GOpenCVUi::run_VIDEO_LOAD(int argc, char** argv) {
    sGApp* lApp = GManager::Instance()->getData()->app;
    printf("\n");
    printf("%s\n", __FUNCTION__);
    QString lVideoPath = "";
    lVideoPath += GConfig::Instance()->getData("G_VIDEO_PATH");
    lVideoPath += lApp->path_sep;
    lVideoPath += GConfig::Instance()->getData("G_VIDEO_NAME");
    printf("%s\n", lVideoPath.toStdString().c_str());
    GOpenCVMg::Instance()->loadVideo(lVideoPath);
    G_STATE = "S_SAVE";
}
//===============================================
void GOpenCVUi::run_SAVE(int argc, char** argv) {
    GConfig::Instance()->saveData("G_OPENCV_ID");
    GConfig::Instance()->saveData("G_IMAGE_PATH");
    GConfig::Instance()->saveData("G_IMAGE_NAME");
    GConfig::Instance()->saveData("G_VIDEO_PATH");
    GConfig::Instance()->saveData("G_VIDEO_NAME");
    G_STATE = "S_QUIT";
}
//===============================================
void GOpenCVUi::run_LOAD(int argc, char** argv) {
    GConfig::Instance()->loadData("G_OPENCV_ID");
    GConfig::Instance()->loadData("G_IMAGE_PATH");
    GConfig::Instance()->loadData("G_IMAGE_NAME");
    GConfig::Instance()->loadData("G_VIDEO_PATH");
    GConfig::Instance()->loadData("G_VIDEO_NAME");
    G_STATE = "S_METHOD";
}
//===============================================
void GOpenCVUi::run_QUIT(int argc, char** argv) {
    printf("\n");
    printf("CPP_QUIT (Oui/[N]on) ? : ");
    std::string lAnswer; std::getline(std::cin, lAnswer);
    if(lAnswer == "-q") G_STATE = "S_END";
    else if(lAnswer == "-i") G_STATE = "S_INIT";
    else if(lAnswer == "-a") G_STATE = "S_ADMIN";
    else if(lAnswer == "o") G_STATE = "S_END";
    else if(lAnswer == "n") G_STATE = "S_INIT";
    else if(lAnswer == "") G_STATE = "S_INIT";
}
//===============================================
