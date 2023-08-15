#ifndef FRONTEND_PAGE_SINGLEWORDINFO_H
#define FRONTEND_PAGE_SINGLEWORDINFO_H

#include "frontend/pages/Word.h"
#include "globalVars/globalVars.h"

class SingleWordInfo {
private:
    bool isInfo = false;
    Rectangle rec_box{50, 120, 1100, 460};
    Rectangle rec_def{50, 205, 1100, 300};
public:
    SingleWordInfo();
    ~SingleWordInfo() 
    {
    }
    void update();
    void draw();
};

#endif