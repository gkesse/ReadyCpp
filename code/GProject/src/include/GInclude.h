//===============================================
#ifndef _GInclude_
#define _GInclude_
//===============================================
#if defined(__unix)
//===============================================
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
//===============================================
#include <QtWidgets>
#include <sqlite3.h>
#include <opencv2/opencv.hpp>
#include <gsl/gsl_spmatrix.h>
#include <gsl/gsl_poly.h>
//===============================================
#elif defined(__MSYS__)
//===============================================
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <pthread.h>
//===============================================
#include <sqlite3.h>
#include <opencv2/opencv.hpp>
#include <gsl/gsl_spmatrix.h>
#include <gsl/gsl_poly.h>
#include <QtWidgets>
//===============================================
#elif defined(__WIN32)
//===============================================
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <windows.h>
//===============================================
#include <sqlite3.h>
#include <opencv2/opencv.hpp>
#include <gsl/gsl_spmatrix.h>
#include <gsl/gsl_poly.h>
//===============================================
#endif
//===============================================
#endif
//===============================================
