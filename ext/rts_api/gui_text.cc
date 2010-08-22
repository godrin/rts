/*
 * Copyright (c) 2005 by David Kamphausen. All rights reserved.
 *
 * ag_text.cc
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


#include <gui_text.h>
#include <basic_debug.h>
#include <gui_surface.h>
#include <gui_fontengine.h>
#include <gui_geometry.h>

#include <iostream>


using namespace std;

AGText::AGText(Rice::Object pSelf):
  AGWidget(pSelf)
  {
    mFixedSize=true;
  }


AGText::~AGText() throw()
  {}


void AGText::draw(AGPainter &p)
  {
    float x=(getRect().width()-mFont.getWidth(mText))/2;
    float y=(getRect().height()-mFont.getHeight(mText))/2;
    p.renderText(mText,AGVector2((int)x,(int)y),mFont);
  }

void AGText::setDeriveRect()
  {
    setRect(AGRect2(getRect().x(),getRect().y(),mFont.getWidth(mText),mFont.getHeight(mText)));
  }

void AGText::setText(const AGStringUtf8 &pText)
  {
    mText=pText;
    if(!mFixedSize)
      {
        setRect(getRect().
        setWidth(mFont.getWidth(pText)).
        setHeight(mFont.getHeight(pText)));
      }
  }
AGStringUtf8 AGText::getText() const
{
  return mText;
}

void AGText::setFont(const AGFont &f)
  {
    mFont=f;
  }
