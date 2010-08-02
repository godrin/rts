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

using namespace std;

AGMenu::AGMenu(const GUIWidgetPtr&pParent,AGVector2 pWishPos,const AGStringUtf8 &pName):
  AGTable(pParent,AGRect2(pWishPos[0],pWishPos[1],1,1)),
  sigSelected(this,"sigSelected"),
  mName(pName.toString()),
  mWishPos(pWishPos)
  {
    mBg=AGTexture(getTheme()->getSurface("menu.background.image"));
    hide();
    addColumn(1);
    mW=0;
    mH=0;
  }

AGMenu::~AGMenu()  throw()
  {}

void AGMenu::show(AGVector2 pWishPos)
  {
    AGWidget::show();
    mWishPos=pWishPos;
    AGVector2 p=fromScreen(mWishPos);
    setTop(p[1]);
    setLeft(p[0]);
  }

void AGMenu::addItem(const AGStringUtf8 &pString)
  {
    AGMenuItem *i=new AGMenuItem(*self(),pString);
    addFixedRow(i->height());

    addChildOld(0,getRows()-1,i);

    mW=std::max(mW,i->width());
    setWidth(mW);
    setHeight(mW);
    arrange();
  }

AGMenu &AGMenu::addMenu(const AGStringUtf8 &pString)
  {
    AGSubMenu *s=new AGSubMenu(*self(),pString);
    addFixedRow(s->height());
    addChildOld(0,getRows()-1,s);

    mH+=s->height();
    setWidth(mW);
    setHeight(mW);
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
    Children::iterator i=mChildren.begin();
    for(;i!=mChildren.end();i++)
      {
        AGMenuItem *item=dynamic_cast<AGMenuItem*>(i->widget());
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

    AGMenuItem *mi=dynamic_cast<AGMenuItem*>(getParent().widget());
    if(mi)
      {
        AGMenu *m=dynamic_cast<AGMenu*>(mi->getParent().widget());
        if(m)
          m->eventItemClicked(pString);
      }
    hide();
    cdebug("hide");
  }
