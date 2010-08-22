/*
 * Copyright (c) 2005 by David Kamphausen. All rights reserved.
 *
 * ag_radiogroup.cc
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
#include <gui_radiogroup.h>
#include <gui_local.h>
#include <gui_theme.h>
#include <gui_image.h>
#include <typeinfo>


AGRadioGroup::AGRadioGroup(Rice::Object pSelf):
  AGWidget(pSelf),
  sigChanged(this,"sigChanged")
  {
  }
AGRadioGroup::~AGRadioGroup() throw()
  {
    Nullable<Rice::Data_Object<AGRadioGroup> > nil;
    ObjectList children=getChildren();
    for(ObjectIterator i=children.begin();i!=children.end();i++) {
      (*(*i)->casted<AGRadio>())->setGroup(nil);
    }
  }

void AGRadioGroup::eventChange(const AGString &p)
  {
    ObjectList children=getChildren();
    for(ObjectIterator i=children.begin();i!=children.end();i++) {
        if((*i)->getName()!=p)
          (*(*i)->casted<AGRadio>())->deselect();
      }

  }

void AGRadioGroup::add(const Rice::Data_Object<AGRadio> &r)
  {
    mChildren.insert(r);
  }
void AGRadioGroup::erase(const Rice::Data_Object<AGRadio> &r)
  {
    mChildren.erase(r);
  }





