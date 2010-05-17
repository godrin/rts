/*
 * Copyright (c) 2005 by David Kamphausen. All rights reserved.
 *
 * map.h
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

#ifndef __MAP_H__
#define __MAP_H__

// INCLUDE_SWIG - used to filter, which files are included in swig-interfacing

#include "height_map.h"
#include "heuristic.h"

/**
 * \defgroup GameEngine BoA Game-Engine
 * \brief the C++ parts of the BoA game-engine
 *
*/

template<class T>
class QuadTree;

class AnimMesh;
class Mesh2D;
class MeshBase;

class AGEXPORT AntMap:public HeightMap
{
 public:
  typedef std::list<AntEntity*> EntityList;
  typedef AntEntity*PAntEntity;

  AntMap(SceneBase *pScene,int w,int h);
  ~AntMap() throw();

  virtual void insertEntity(AntEntity *e);
  virtual void removeEntity(AntEntity *p);
  void clear() throw();

  int getNewID();
  void useID(int id);

  void newMap(int w,int h);

  EntityList getEntities(const AGRect2&r);
  std::list<AntEntity*> getAllEntities();
  std::vector<AntEntity*> getEntities(const AGString &pName);


  //AntEntity *getEntity(const MeshBase &pMesh);
  
  AntEntity *getEntity(const Mesh &pMesh);
  AntEntity *getEntity(const AnimMesh &pMesh);
  AntEntity *getEntity(const Mesh2D &pMesh);
   
  AntEntity *getEntity(int id) const;
  AntEntity *getByName(const AGString &pName);

  AntEntity *getNext(AntEntity *me,const AGString &pType,size_t atLeast=0);
  std::vector<PAntEntity> getNextList(AntEntity *me,const AGString &pType,size_t atLeast=0);

  void setHeuristic(HeuristicFunction *pFunction);

  virtual void processXMLNode(const Node &node);

  void saveXML(Node &node) const;
  bool loadXML(const Node &node);

  void saveMap(const AGString &pFilename);
  virtual bool loadMap(const AGString &pFilename);
  virtual bool loadMapFromMemory(const AGString &Memory);

  void move(float pTime);

  AGVector3 getPos(const AGVector2 &pPos) const;


  virtual void mapChanged();

 protected:
#ifndef SWIG
  virtual void mark() throw();
#endif
 private:
  typedef std::map<size_t,AntEntity*> EntityMap;

  EntityList mEntities;
  EntityMap mEntityMap;
  QuadTree<AntEntity> *mEntQuad;

  EntityList mToDel;

  int maxID;

  HeuristicFunction *mHeuristicFunction;


};


#endif
