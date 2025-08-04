#include "sgwhorizontalalignment.h"
#include <qnamespace.h>

Qt::AlignmentFlag SGWHorizontalAlignment::getQtFlag(Flag x){
    if(x == SGWHorizontalAlignment::Left){return Qt::AlignLeft;}
    if(x == SGWHorizontalAlignment::Right){return Qt::AlignRight;}
    return Qt::AlignHCenter;
}
