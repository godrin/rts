/*
 * Copyright (c) 2005 by David Kamphausen. All rights reserved.
 *
 * ag_image.h
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

#ifndef AG_IMAGE_H
#define AG_IMAGE_H

#include <gui_widget.h>
#include <gui_texture.h>

class AGEXPORT AGImage:public AGWidget
{
 public:
  AGImage(Rice::Object pSelf);
  virtual ~AGImage() throw();

  virtual void draw(AGPainter &p);
  
  void setFilename(AGString fn);

  void setSurface(const AGSurface &pSurface);
  void setTexture(const AGTexture &pTexture);

  void useTextures();

  void setCenter(bool c);
  void setScale(bool s);
  bool getCenter();
  void setTiling(bool b);

 private:
  AGTexture mTexture;
  bool mTile;
  bool mScale;
  bool mCenter;
};

#endif
