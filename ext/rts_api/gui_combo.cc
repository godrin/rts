/*
 * Copyright (c) 2005 by David Kamphausen. All rights reserved.
 *
 * ag_combo.cc
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

#include <gui_application.h>
#include <gui_button.h>
#include <gui_combo.h>
#include <basic_debug.h>
#include <gui_edit.h>
#include <gui_listbox.h>
#include <gui_theme.h>

#include <rice/Data_Type.hpp>

AGComboBox::AGComboBox(Rice::Object pSelf):
  AGWidget(pSelf),sigSelect(this,"sigSelect"),
  mEdit(Create<AGEdit>()),
  mButton(Create<AGButton>()),
  mListBox(Create<AGListBox>())
  {
    //mEdit=new AGEdit(Rice::Nil,getSelf(),AGRect2(0,0,width()-height(),height()));
    //mButton=new AGButton(Rice::Nil,getSelf(),AGRect2(width()-height(),0,height(),height()),"");

    mButton->setSurface(AGSurface::load("data/gui/arrow_down.png"));

    AGFont f=getTheme()->getFont("combobox.font");

    mEdit->setMutable(false);
    mEdit->setFont(f);
    addChild(mEdit);
    addChild(mButton);

    mButton->sigClick.connect(slot(this,&AGComboBox::eventButtonClicked));
    
    mListBox->sigSelect.connect(slot(this,&AGComboBox::eventSelected));

  }

AGComboBox::~AGComboBox() throw()
  {}
  
  
void AGComboBox::setRect(const AGRect2 &r) {
  AGWidget::setRect(r);
  float width=getRect().width();
  float height=getRect().height();
  mEdit->setRect(AGRect2(0,0,width-height,height));
  mButton->setRect(AGRect2(width-height,0,height,height));
}


void AGComboBox::insertItem(const AGString &pID,const AGStringUtf8 &pContent)
  {
    ops.push_back(std::make_pair(pID,pContent));
    if(ops.size()==1)
      mID=pID;
    update();
  }

void AGComboBox::update()
  {
    if(ops.size()>0)
      {
        // find
        AGStringUtf8 text;
        for(std::list<std::pair<AGString,AGStringUtf8> >::iterator i=ops.begin();i!=ops.end();i++)
          if(i->first==mID)
            {
              text=i->second;
              break;
            }

        mEdit->setText(text);
      }
  }

bool AGComboBox::eventButtonClicked(AGEvent *pEvent)
  {
    if(ops.size()==0)
      return true;

    AGRect2 sr=getScreenRect();

    cdebug(sr.x());
    cdebug(sr.y());
    cdebug(getRect().width());
    cdebug(getTheme()->getInt("listbox.item.height")*std::min(8,(int)ops.size()));

    float mItemHeight=getTheme()->getInt("listbox.item.height");
    if(mItemHeight<5)
      mItemHeight=25;


    mListBox->setRect(AGRect2(sr.x(),sr.y()+getRect().height(),getRect().width(),mItemHeight*8));

    mListBox->clearList();

    for(std::list<std::pair<AGString,AGStringUtf8> >::iterator i=ops.begin();i!=ops.end();i++)
      mListBox->insertItem(i->first,i->second);
    if(ops.size()>0)
      mListBox->selectItem(mID);

    getApp()->setOverlay(mListBox);
    return true;
  }

bool AGComboBox::eventSelected(AGEvent *pEvent)
  {
    CTRACE;
    mID=mListBox->getSelectedID();
    update();
    getApp()->setOverlay(0);

    sigSelect(new AGEvent(this,"sigSelect"));
    return true;
  }

AGString AGComboBox::getSelected() const
{
  return mID;
}
void AGComboBox::setSelected(const AGString &pID)
  {
    mID=pID;
    update();
  }

void AGComboBox::clear() throw()
  {
    ops.clear();
    mID="";
    update();
  }

