/*
 * Copyright (c) 2005 by David Kamphausen. All rights reserved.
 *
 * ag_radio.cc
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


#include <gui_radio.h>
#include <gui_local.h>
#include <gui_theme.h>
#include <gui_image.h>
#include <gui_layoutfactory.h>
#include <gui_radiogroup.h>
#include <typeinfo>


AGRadio::AGRadio(const GUIWidgetPtr&pParent,AGRect2 pRect):
  AGCheckBox(pParent,pRect),mGroup(0)
  {
    // search mGroup
    GUIWidgetPtr w=pParent;
    AGRadioGroup *g=0;
    while(w && g==0)
      {
        g=dynamic_cast<AGRadioGroup*>(w.widget());
        w=w->getParent();
      }
    if(g)
      mGroup=g;

    if(mGroup)
      mGroup->add(this);
  }

AGRadio::~AGRadio() throw()
  {
    if(mGroup)
      mGroup->erase(this);
  }

void AGRadio::setChecked(bool pChecked)
  {
    bool c=isChecked();
    if(c!=pChecked)
      {
        AGCheckBox::setChecked(pChecked);

        if(pChecked)
          {
            if(mGroup)
              mGroup->eventChange(getName());
          }
      }
  }

void AGRadio::deselect()
  {
    setChecked(false);
  }

void AGRadio::setGroup(AGRadioGroup *pGroup)
  {
    mGroup=pGroup;
  }

bool AGRadio::eventMouseClick(AGEvent *m)
  {
    if(!isChecked())
      setChecked(true);

    return AGButton::eventMouseClick(m);
  }



