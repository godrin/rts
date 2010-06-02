#ifndef MESH_DATA_H
#define MESH_DATA_H

// INCLUDE_SWIG - used to filter, which files are included in swig-interfacing

#include <a3d_scenenode.h>
#include <a3d_mesh_data.h>
#include <a3d_vertex_array.h>
#include <gui_texture.h>

// Mesh organizing

class AGEXPORT MeshData
{
  VertexArray mArray;
  AGTexture mTexture;
  bool mWithTexture;
  bool mShadow;

  AGBox3 mBBox;

  bool mTransparent;

  bool overdraw;
  bool drawColors;
  bool mPickable;
  bool mLighting;
  bool mCulling;

 public:
  MeshData(const std::string &filename,float zoom,const std::string &pTexture="",bool pShadow=true);
  MeshData(const VertexArray &va,const std::string &pTexture,bool pShadow=true);
  ~MeshData() throw();

  void draw(const AGVector4 &pColor);
  void drawShadow();
  void drawDepth();
  void drawPick();

  /// test function "instancing"
  void makeInstances(const std::vector<AGMatrix4> &ts);


  AGBox3 bbox() const;

  void save(const std::string &pFilename);

  virtual size_t getTriangles() const;

  virtual AGVector4 lineHit(const AGLine3 &pLine) const
  {
    return mArray.lineHit(pLine);
  }
  void texCoordFromPos(float scale);
  void setPickable(bool p);

  void setTransparent(bool p);
  virtual bool transparent();
  void setLighting(bool l);

  void setOverdraw(bool o);
  void setCulling(bool c);
  void setColors(bool c);
};


#endif
