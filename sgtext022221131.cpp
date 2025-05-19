#include "sgtext022221131.h"
#include "sggenerallibrary.h"
#include "sgcentralmanagement.h"

SGText022221131::SGText022221131(QWidget *parent, QString s, float x, float y){
    (*this).setParent(parent);
    (*this).x = x;
    (*this).y = y;
    (*this).show();
    (*this).setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    (*this).setFont(*SGGeneralLibrary::SingScriptSG);
    SGGeneralLibrary::SetUIStyle(this, SGGeneralLibrary::stylesheetfieldtextcolour, SGCentralManagement::colour2);
    SGGeneralLibrary::SetUIStyle(this, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour0);
    (*this).setAutoFillBackground(true);
    (*this).setText(s);
    (*this).ResizeObj();
}

void SGText022221131::ResizeObj(){
    (*this).move(QPoint(x * SGCentralManagement::sizeunit, y * SGCentralManagement::sizeunit));
    (*this).resize((*parentWidget()).size());
    SGGeneralLibrary::updatefontsize(this);
}
