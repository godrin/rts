/*
 * Copyright (c) 2005 by David Kamphausen. All rights reserved.
 *
 * ag_caption.h
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

#ifndef AG_CAPTION_H
#define AG_CAPTION_H

#include <gui_text.h>
#include <gui_background.h>

class AGEXPORT AGCaption:public AGText
{
 public:
  AGCaption(Rice::Object pSelf);

  void draw(AGPainter &p);

  void setBackground(AGBackground pBG);
 private:
  AGBackground mBG;
};

#endif
