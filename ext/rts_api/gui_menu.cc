/*
 * Copyright (c) 2005 by David Kamphausen. All rights reserved.
 *
 * ag_menu.cc
 * by David Kamphausen (david.kamphausen@web.de)
 *
 * The "Antargis" project, including all files needed to compile it,
 * is free software; you can redistribute it and/or use it and/or modify it
 * under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 2 of the License,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program.
 */

#include <gui_menu.h>
#include <gui_menuitem.h>
#include <gui_font.h>
#include <gui_text.h>
#include <gui_surface.h>
#include <gui_theme.h>

#include <basic_debug.h>

#include <rice/Data_Type.hpp>

using namespace std;

AGMenu::AGMenu(Rice::Object pSelf):
  AGTable(pSelf),
  sigSelected(this,"sigSelected")
  {
    mBg=AGTexture(getTheme()->getSurface("menu.background.image"));
    hide();
    addColumn(1);
    mW=0;
    mH=0;
  }

AGMenu::~AGMenu()  throw()
  {}
  
void AGMenu::setWishPos(const AGVector2 &pWishPos) {
  mWishPos=pWishPos;
  setRect(AGRect2(pWishPos[0],pWishPos[1],1,1));
}

void AGMenu::show(AGVector2 pWishPos)
  {
    AGWidget::show();
    mWishPos=pWishPos;
    AGVector2 p=fromScreen(mWishPos);
    setRect(getRect().setTop(p[1]).setLeft(p[0]));
  }

void AGMenu::addItem(const AGStringUtf8 &pString)
  {
    Rice::Data_Object<AGMenuItem> i=Create<AGMenuItem>();
    i->setText(pString);
    addFixedRow(i->getRect().height());

    addChild(0,getRows()-1,i);

    mW=std::max(mW,i->getRect().width());
    setRect(getRect().setWidth(mW).setHeight(mW));
    arrange();
  }

AGMenu &AGMenu::addMenu(const AGStringUtf8 &pString)
  {
    Rice::Data_Object<AGSubMenu> s=Create<AGSubMenu>();
    s->setText(pString);
    addFixedRow(s->getRect().height());
    addChild(0,getRows()-1,s);

    mH+=s->getRect().height();
    setRect(getRect().setWidth(mW).setHeight(mW));
    arrange();

    return *s->getMenu();
  }


void AGMenu::draw(AGPainter &p)
  {
    //  cdebug("draw");
    //  return;
    //  adaptWidthFromChildren();
    //  AGPainter p(getScreen());
    p.tile(mBg);//,r.project(getRect()));

    //  cdebug(r.project(getRect()).toString());
  }

void AGMenu::eventItemSelected(const AGString &pString)
  {
    ObjectList children=getChildren();
    for(ObjectIterator i=children.begin();i!=children.end();i++)
      {
        Rice::Data_Object<AGMenuItem> item=*i;
        //cdebug("item:"<<item);
        if(item)
          {
            //  cdebug(item->getName()<<" "<<pString);
            if(item->getSelected() && item->getName()!=pString)
              {
                //  cdebug("unSelect");
                item->unSelect();
              }
          }
      }
  }
void AGMenu::eventItemClicked(const AGString &pString)
  {
    sigSelected(new AGEvent(this,pString));

    Nullable<Rice::Data_Object<AGMenuItem> > mi=(*getParent())->casted<AGMenuItem>();
    if(mi)
      {
        Nullable<Rice::Data_Object<AGMenu> > m=(*(*mi)->getParent())->casted<AGMenu>();
        if(m)
          (*m)->eventItemClicked(pString);
      }
    hide();
    cdebug("hide");
  }
