/*
 * Copyright (c) 2005 by David Kamphausen. All rights reserved.
 *
 * ag_caption.cc
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

#include "gui_caption.h"
#include "gui_screen.h"

#include "basic_debug.h"

static bool useVertexArrays()
  {
    AGString s=getConfig()->get("useVertexArrays");
    if(s!="true" && s!="false")
      {
        s="true";
        getConfig()->set("useVertexArrays",s);
      }
    return s=="true";
  }


AGCaption::AGCaption(Rice::Object pSelf):
  AGText(pSelf)
  {
  }



void AGCaption::draw(AGPainter &p)
  {
    // draw bg
    mBG.draw(getRect().origin(),p);
    AGText::draw(p);
  }

void AGCaption::setBackground(AGBackground pBG)
  {
    mBG=pBG;
  }
