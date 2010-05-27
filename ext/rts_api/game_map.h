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

#include "rice/Data_Object.hpp"


#include <game_height_map.h>
#include <game_heuristic.h>

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

class AGEXPORT AntMap:public GameHeightMap
{
 public:
   
   class EntityNotFound {
   };
   
  typedef Rice::Data_Object<AntEntity> PAntEntity;
  typedef std::list<PAntEntity> EntityList;

  AntMap(SceneBase *pScene,int w,int h);
  ~AntMap() throw();

  virtual void insertEntity(PAntEntity e);
  virtual void removeEntity(PAntEntity p);
  void clear() throw();

  int getNewID();
  void useID(int id);

  void newMap(int w,int h);

  EntityList getEntities(const AGRect2&r);
  EntityList getAllEntities();
  EntityList getEntities(const AGString &pName);


  //AntEntity *getEntity(const MeshBase &pMesh);
  
  PAntEntity getEntity(const Mesh &pMesh) throw (EntityNotFound);
  PAntEntity getEntity(const AnimMesh &pMesh) throw (EntityNotFound);
   
  PAntEntity getEntity(int id) const throw (EntityNotFound);
  PAntEntity getByName(const AGString &pName) throw (EntityNotFound);

  PAntEntity getNext(PAntEntity me,const AGString &pType,size_t atLeast=0) throw (EntityNotFound);
  EntityList getNextList(PAntEntity me,const AGString &pType,size_t atLeast=0);

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
  virtual void mark() throw();
 private:
  typedef std::map<size_t,PAntEntity> EntityMap;

  EntityList mEntities;
  EntityMap mEntityMap;
  QuadTree<PAntEntity> *mEntQuad;

  EntityList mToDel;

  int maxID;

  HeuristicFunction *mHeuristicFunction;


};


#endif
