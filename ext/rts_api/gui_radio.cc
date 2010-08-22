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
#include <gui_radiogroup.h>
#include <typeinfo>

#include <rice/Data_Type.hpp>


AGRadio::AGRadio(Rice::Object pSelf):
  AGCheckBox(pSelf)
  {
  }

AGRadio::~AGRadio() throw()
  {
    if(mGroup)
      (*mGroup)->erase(getSelf());
  }

void AGRadio::eventGotParent(const Ptr &pWidget) {
  mGroup=seekParent<AGRadioGroup>();
  (*mGroup)->add(getSelf());
}
void AGRadio::eventLostParent(const Ptr &pWidget) {
  if(mGroup==pWidget) {
    (*mGroup)->erase(getSelf());
    mGroup=Nullable<Rice::Data_Object<AGRadioGroup> >();
  }
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
              (*mGroup)->eventChange(getName());
          }
      }
  }

void AGRadio::deselect()
  {
    setChecked(false);
  }

void AGRadio::setGroup(Nullable<Rice::Data_Object<AGRadioGroup> > pGroup)
  {
    mGroup=pGroup;
  }

bool AGRadio::eventMouseClick(AGEvent *m)
  {
    if(!isChecked())
      setChecked(true);

    return AGButton::eventMouseClick(m);
  }



