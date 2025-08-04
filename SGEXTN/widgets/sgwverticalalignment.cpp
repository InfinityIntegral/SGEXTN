#include "sgwverticalalignment.h"
#include <qnamespace.h>

Qt::AlignmentFlag SGWVerticalAlignment::getQtFlag(Flag x){
    if(x == SGWVerticalAlignment::Top){return Qt::AlignTop;}
    if(x == SGWVerticalAlignment::Bottom){return Qt::AlignBottom;}
    return Qt::AlignVCenter;
}
