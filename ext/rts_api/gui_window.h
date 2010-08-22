/*
 * Copyright (c) 2005 by David Kamphausen. All rights reserved.
 *
 * ag_window.h
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

// INCLUDE_SWIG - used to filter, which files are included in swig-interfacing

#ifndef AG_WINDOW_H
#define AG_WINDOW_H

#include <gui_table.h>

class AGCaption;

class AGEXPORT AGWindow:public AGTable
{
 public:
  AGWindow(Rice::Object pSelf);
  virtual ~AGWindow()  throw();

  Rice::Data_Object<AGWidget> getClient();

  virtual bool eventMouseButtonDown(AGEvent *m);
  bool eventDragBy(AGEvent *event,const AGVector2 &pDiff);

  void close();

  // slot
  virtual bool tryClose(AGEvent *m);

  AGRect2 getClientRect() const;

  AGSignal sigClose;
  void setTitle(const AGString &pTitle);

 private:
  Rice::Data_Object<AGWidget> image(const AGRect2 r,const AGTexture &t);

  Rice::Data_Object<AGTable> getTitleBar(int w,int h);

  AGStringUtf8 mTitle;
  Nullable<Rice::Data_Object<AGCaption> > mClient;
};

//AGWindow &toAGWindow(AGWidget &w);

#endif
