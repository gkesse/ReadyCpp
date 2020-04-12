//================================================
#ifndef _GExprTk_
#define _GExprTk_
//================================================
#include "GInclude.h"
//===============================================
#if defined(_GUSE_EXPRTK_ON_)
//================================================
class GExprTk {
private:
	GExprTk();

public:
	~GExprTk();
	static GExprTk* Instance();
    void add(const char* symbol, double value);
    double run(const char* expression);

private:
    const char* __CLASSNAME__;
	static GExprTk* m_instance;
	exprtk::symbol_table<double> m_symbol;
};
//================================================
#endif
//================================================
#endif
//================================================
