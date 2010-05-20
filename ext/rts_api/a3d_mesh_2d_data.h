#ifndef MESH_2D_DATA
#define MESH_2D_DATA

// INCLUDE_SWIG - used to filter, which files are included in swig-interfacing

#include <gui_texture.h>

class AGEXPORT Mesh2DData:public AGRubyObject
{
 public:
  Mesh2DData(AGTexture *pTexture);
  
  void mark() throw();

  AGTexture *getTexture();

  AGBox3 bbox() const;

 private:
  AGTexture *mTexture;
};

#endif
