#ifndef FRONTEND_PAGE_SINGLEWORDINFO_H
#define FRONTEND_PAGE_SINGLEWORDINFO_H

#include "frontend/pages/Word.h"
#include "globalVars/globalVars.h"

class SingleWordInfo {
private:
    bool isInfo = false;
public:
    SingleWordInfo();
    ~SingleWordInfo() 
    {
    }
    void update();
    void draw();
};

#endif