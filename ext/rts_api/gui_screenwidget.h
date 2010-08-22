/*
 * Copyright (c) 2005 by David Kamphausen. All rights reserved.
 *
 * ag_screenwidget.h
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

#ifndef AG_SCREENWIDGET_H
#define AG_SCREENWIDGET_H

// INCLUDE_SWIG - used to filter, which files are included in swig-interfacing

#include <gui_widget.h>
#include <gui_texture.h>

class AGEXPORT AGScreenWidget:public AGWidget
{
 public:
  AGScreenWidget(Rice::Object pSelf);
  virtual ~AGScreenWidget() throw();

  virtual void draw(AGPainter &p);
 private:
  AGTexture mTexture;
};

#endif
