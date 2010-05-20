/*
 * Copyright (c) 2005 by David Kamphausen. All rights reserved.
 *
 * ag_checkbox.cc
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

#include <gui_checkbox.h>
#include <gui_image.h>
#include <gui_text.h>
#include <gui_theme.h>
#include <basic_debug.h>
#include <gui_layoutfactory.h>
#include <gui_local.h>

AGCheckBox::AGCheckBox(AGWidget *pParent,AGRect2 pRect):
  AGButton(pParent,pRect,"")
  {
    mSurfaces[0]=mSurfaces[1]=0;
  }

bool AGCheckBox::eventMouseClick(AGEvent *m)
  {
    CTRACE;
    setChecked(!isChecked());
    return AGButton::eventMouseClick(m);//false;//true; // eat
  }



void AGCheckBox::setSurfaces(AGSurface pDisabledSurface,AGSurface pEnabledSurface)
  {
    saveDelete(mSurfaces[0]);
    saveDelete(mSurfaces[1]);
    mSurfaces[0]=new AGSurface(pDisabledSurface);
    mSurfaces[1]=new AGSurface(pEnabledSurface);

    //  setState(getState());
    queryRedraw();
  }

void AGCheckBox::setState(const State &pState)
  {
    if(mSurfaces[0])
      {
        if(pState==NORMAL || pState==LIGHTED || pState==PRESSED)
          setSurface(*(mSurfaces[0]));
        else
          setSurface(*(mSurfaces[1]));
      }

    AGButton::setState(pState);
  }


