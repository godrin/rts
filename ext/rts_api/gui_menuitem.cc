/*
 * Copyright (c) 2005 by David Kamphausen. All rights reserved.
 *
 * ag_menuitem.cc
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

#include <gui_menuitem.h>
#include <gui_draw.h>
#include <gui_theme.h>
#include <gui_image.h>
#include <gui_menu.h>

#include <rice/Data_Type.hpp>

AGMenuItem::AGMenuItem(Rice::Object pSelf):
  AGTable(pSelf),mText(""),mMouseOver(false),mSelected(false)
  {
    AGFont font(getTheme()->getFont("Font.menu"));


    //  adaptWidthFromChildren(); // so that parent can adapt to this

    //  addChild(new AGText(this,AGVector2(0,0),"X",AGFont("Arial.ttf",25))); // test
    AGSurface surface=getTheme()->getSurface("menu.item.image");//getScreen().loadSurface("/home/david/projects/oldantargis/graphics/menu_house_small.png");

    addFixedRow(surface.height());
    addFixedColumn(surface.width());
    addColumn(1);
    arrange();
    Rice::Data_Object<AGImage> image=Create<AGImage>();
    image->setSurface(surface);
    image->setTiling(false);
    addChild(0,0,image);//(Rice::Nil,getSelf(),getRect().origin(),surface,false));
    mTextWidget=Create<AGText>();
    (*mTextWidget)->setText(mText);
    (*mTextWidget)->setFont(font);
    addChild(1,0,*mTextWidget);

  }
AGMenuItem::~AGMenuItem() throw()
  {
  }

void AGMenuItem::setText(AGStringUtf8 pText) {
  mText=pText;
  (*mTextWidget)->setText(mText);
}

void AGMenuItem::draw(AGPainter &p)//const AGRect2 &pr)
  {
    //  AGRect2 r=pr.project(getRect());

    AGColor c1,c2,c3,c4;

    AGString style=".menu";
    if(mSelected)//MouseOver)
      {
        style+=".lighted";

        AGTheme *theme=getTheme();

        c1=theme->getColor(AGString("gradientColor1")+style);
        c2=theme->getColor(AGString("gradientColor2")+style);
        c3=theme->getColor(AGString("gradientColor3")+style);
        c4=theme->getColor(AGString("gradientColor4")+style);

        //      AGSurface s(getScreen());
        p.drawGradient(p.getRect(),c1,c2,c3,c4);
      }


  }

bool AGMenuItem::eventMouseEnter()
  {
    mMouseOver=true;
    mSelected=true;
    eventSelect();

    Nullable<Rice::Data_Object<AGMenu> > p=(*getParent())->casted<AGMenu>();
    //  cdebug(p);
    if(p)
      {
        (*p)->eventItemSelected(mText.toString());
      }
    return false;
  }

bool AGMenuItem::eventMouseLeave()
  {
    mMouseOver=false;
    return false;
  }

AGString AGMenuItem::getName() const
{
  return mText.toString();
}

bool AGMenuItem::getSelected() const
{
  return mSelected;
}
void AGMenuItem::unSelect()
  {
    mSelected=false;
    eventUnselect();
  }

void AGMenuItem::eventSelect()
  {
  }
void AGMenuItem::eventUnselect()
  {
  }

bool AGMenuItem::eventMouseClick(AGEvent *m)
  {
    Nullable<Rice::Data_Object<AGMenu> > me=(*getParent())->casted<AGMenu>();
    if(me)
      {
        (*me)->eventItemClicked(mText.toString());

        return true;
      }
    return false;
  }

// AGSubMenu

AGSubMenu::AGSubMenu(Rice::Object pSelf):
  AGMenuItem(pSelf)
  {
    AGSurface surface2=AGSurface::load("right_arrow.png");
    Rice::Data_Object<AGImage> cimage=Create<AGImage>();
    cimage->setSurface(surface2);
    cimage->setTiling(false);
    addChildBack(cimage); //new AGImage(Rice::Nil,getSelf(),getRect().origin(),surface2,false));

    mSubMenu=Create<AGMenu>();
    addChild(*mSubMenu);
    (*mSubMenu)->hide();
  }

AGSubMenu::~AGSubMenu() throw()
  {
  }

Rice::Data_Object<AGMenu> AGSubMenu::getMenu()
  {
    return *mSubMenu;
  }

void AGSubMenu::addChild(const GUIWidgetPtr&pWidget)
  {
    AGWidget::addChild(pWidget);
  }

void AGSubMenu::eventSelect()
  {
    AGRect2 r(getScreenRect());

    getMenu()->show(r.getV10());
  }
void AGSubMenu::eventUnselect()
  {
    getMenu()->hide();
  }

bool AGSubMenu::eventMouseClick(AGEvent *m)
  {
    return false;
  }
