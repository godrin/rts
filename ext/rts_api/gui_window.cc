/*
 * Copyright (c) 2005 by David Kamphausen. All rights reserved.
 *
 * ag_window.cc
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

#include <gui_window.h>
#include <gui_surface.h>
#include <gui_theme.h>
#include <gui_image.h>
#include <gui_text.h>
#include <basic_debug.h>
#include <gui_button.h>
#include <gui_caption.h>
#include <gui_texturecache.h>

#include <rice/Data_Type.hpp>

#undef connect

AGWindow::AGWindow(Rice::Object pSelf):
  AGTable(pSelf),sigClose(this,"sigClose")

  {
    CTRACE;




    setTitle("");
  }
  
  void AGWindow::setTitle(const AGString &pTitle) {
        int titBarHeight=20;
    AGLocalTheme theme=getTheme()->getTheme(""); //FIXME mTheme);
    AGString borderImage="window.border.image";
    AGSurface s=theme.getSurface(borderImage);
    float bw=s.getRect().w()/3;



    std::vector<const AGTexture*> textures;

    // build textures
    for(int y=0;y<3;y++)
      for(int x=0;x<3;x++)
        {
          AGRect2 r(x*bw,y*bw,bw,bw);

          textures.push_back(&getTextureCache()->get(theme.getSurfaceName(borderImage),r));
        }


    clear();
    Nullable<Rice::Data_Object<AGTable> > t;

    if(pTitle.length())
      {
        // use 4 rows
        addFixedRow(bw); // upper border
        addFixedRow(titBarHeight); // titletext and button
        //      addFixedRow(bw); // lower border below titletext
        addRow(1.0);
        addFixedRow(bw); // lower lower below window
        addFixedColumn(bw);
        addColumn(1.0);
        addFixedColumn(bw);

        AGTable::addChild(0,0,image(AGRect2(0,0,bw,bw),*textures[0]));
        AGTable::addChild(1,0,image(AGRect2(0,0,bw,bw),*textures[1]));
        AGTable::addChild(2,0,image(AGRect2(0,0,bw,bw),*textures[2]));

        Nullable<Rice::Data_Object<AGImage> > i1,i2;

        AGTable::addChild(0,1,*(i1=image(AGRect2(0,0,bw,titBarHeight),*textures[3])));
        // title
        t=getTitleBar((int)(getRect().width()-2*bw),titBarHeight);

        AGTable::addChild(2,1,*(i2=image(AGRect2(0,0,bw,titBarHeight),*textures[5])));
        (*i1)->setRect((*i1)->getRect().setHeight((*t)->getRect().height()));
        (*i2)->setRect((*i2)->getRect().setHeight((*t)->getRect().height()));

        cdebug("i2:"<<(*i2)->getRect().width()<<"   "<<(*i2)->getRect().height());
        cdebug("bw:"<<bw);


        AGTable::addChild(0,2,image(AGRect2(0,0,bw,bw),*textures[3]));
        AGTable::addChild(2,2,image(AGRect2(0,0,bw,bw),*textures[5]));

        AGTable::addChild(0,3,image(AGRect2(0,0,bw,bw),*textures[6]));
        AGTable::addChild(1,3,image(AGRect2(0,0,bw,bw),*textures[7]));
        AGTable::addChild(2,3,image(AGRect2(0,0,bw,bw),*textures[8]));

        AGTable::addChild(1,2,*(mClient=Create<AGCaption>()));
        (*mClient)->setText("");
        (*mClient)->setFont(theme.getFont("window.title.font"));
        (*mClient)->setBackground(AGBackground(theme,"window.background"));

      }
    else
      {
        // use 3 rows
        addFixedRow(bw);
        addRow(1.0);
        addFixedRow(bw);
        addFixedColumn(bw);
        addColumn(1.0);
        addFixedColumn(bw);

        AGTable::addChild(0,0,image(AGRect2(0,0,bw,bw),*textures[0]));
        AGTable::addChild(1,0,image(AGRect2(0,0,bw,bw),*textures[1]));
        AGTable::addChild(2,0,image(AGRect2(0,0,bw,bw),*textures[2]));

        AGTable::addChild(0,1,image(AGRect2(0,0,bw,bw),*textures[3]));
        AGTable::addChild(2,1,image(AGRect2(0,0,bw,bw),*textures[5]));

        AGTable::addChild(0,2,image(AGRect2(0,0,bw,bw),*textures[6]));
        AGTable::addChild(1,2,image(AGRect2(0,0,bw,bw),*textures[7]));
        AGTable::addChild(2,2,image(AGRect2(0,0,bw,bw),*textures[8]));

        AGTable::addChild(1,1,*(mClient=Create<AGCaption>()));
        (*mClient)->setText("");
        (*mClient)->setFont(theme.getFont("window.title.font"));
        (*mClient)->setBackground(AGBackground(theme,"window.background"));
      }

    arrange();
  }

AGWindow::~AGWindow() throw()
  {}

Rice::Data_Object<AGWidget> AGWindow::image(const AGRect2 r,const AGTexture &t) {
  Rice::Data_Object<AGImage> i=Create<AGImage>();
  i->setRect(r);
  i->setTexture(t);
  return i;
}

Rice::Data_Object<AGWidget> AGWindow::getClient()
  {
    return *mClient;
  }

bool AGWindow::eventMouseButtonDown(AGEvent *e)
  {
    CTRACE;
    if(!hasFocus())
      {
        CTRACE;
        if(e->isSDLEvent())
          if(getScreenRect().contains(e->getMousePosition()))
            if(getParent())
              {
                (*getParent())->gainFocus(getSelf());
                return true;
              }
      }

    bool ret=AGTable::eventMouseButtonDown(e);

    if(e->isSDLEvent())
      if(getScreenRect().contains(e->getMousePosition()))
        return true; // eat - if it was here - always!!!
    return ret;

  }

bool AGWindow::eventDragBy(AGEvent *event,const AGVector2 &pDiff)
  {
    //  TRACE;
    setRect(getRect()+pDiff);
    return true;
  }

Rice::Data_Object<AGTable> AGWindow::getTitleBar(int w,int h)
  {
    cdebug("W:"<<w);
    Rice::Data_Object<AGTable> t=Create<AGTable>();
    t->setRect(AGRect2(0,0,0,20));//60,20));
    AGSurface closeSurface=getTheme()->getSurface("window.buttons.close");
    Nullable<Rice::Data_Object<AGButton> > closeButton;
    Nullable<Rice::Data_Object<AGCaption> > title;

    AGTable::addChild(1,1,t);

    t->addRow(1.0);

    t->addColumn(1.0);
    t->addFixedColumn(h);//close button

    //  t->addChild(0,0,title=new AGButton(t,AGRect2(0,0,0,0),mTitle));
    t->addChild(0,0,*(title=Create<AGCaption>()));
    (*title)->setRect(AGRect2(0,0,0,0));
    (*title)->setText(mTitle);
    (*title)->setFont(getTheme()->getFont("window.title.font"));
    (*title)->setBackground(AGBackground("window.title.background"));
    t->addChild(1,0,*(closeButton=Create<AGButton>()));
    (*closeButton)->setRect(AGRect2(0,0,20,20));
    (*closeButton)->setCaption("aa");
    (*closeButton)->setSurface(closeSurface,false);
    (*title)->setName("title"); // FIXME: maybe name getName()+".title"

    //  AGListener
    (*closeButton)->sigClick.connect(slot(this,&AGWindow::tryClose));
    //  t->arrange();
    return t;
  }

bool AGWindow::tryClose(AGEvent *m)
  {
    TRACE;
    hide();
    m->setCaller(this);
    sigClose(m);
    return false;
  }

void AGWindow::close()
  {
    hide();
  }

AGRect2 AGWindow::getClientRect() const
{
  return const_cast<AGWindow*>(this)->getClient()->getClientRect()+(*mClient)->getRect().getV0();
}

AGWindow &toAGWindow(AGWidget &w)
  {
    return dynamic_cast<AGWindow&>(w);
  }
