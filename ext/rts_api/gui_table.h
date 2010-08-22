/*
 * Copyright (c) 2005 by David Kamphausen. All rights reserved.
 *
 * ag_table.h
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

#ifndef AG_TABLE_H
#define AG_TABLE_H

#include <gui_widget.h>

#include <vector>

#include <rice/Data_Type.hpp>

/**
   Description:
   At first you can adjust rows/columns - then you can insert some children.
   after that rows and columns are fixed.

   Please call AGTable::arrange() whenever you changed extends and/or row/column-info.
*/

class AGEXPORT AGTable:public AGWidget
{
 public:
  AGTable(Rice::Object pSelf);
  virtual ~AGTable() throw();

  void addFixedColumn(float size);
  void addFixedRow(float size);

  void addColumn(float weight);
  void addRow(float weight);
  
  void modifyColumn(size_t index,float w);
  void modifyRow(size_t index,float w);
  
  float getColumn(size_t c) const;
  float getRow(size_t c) const;

  void addChild(int x,int y,GUIWidgetPtr pWidget);
  AGRect2 getClientRect(int x,int y) const;

  void arrange();

  virtual void setRect(const AGRect2 &r);

  size_t getRows() const;
  size_t getColumns() const;
  
  void structureFinished();
  class StructureWasFixed:public AGException{
    public:
     StructureWasFixed(const std::string& e):AGException(e) {}
  };
  class StructureNotFixed:public AGException {
    public:
     StructureNotFixed(const std::string& e):AGException(e) {}
  };
  class InvalidWeight:public AGException {
    public:
     InvalidWeight(const std::string& e):AGException(e) {}
  };

 private:
   
   
  int w,h;
  float xw,yw; // weights

  // definition
  std::vector<std::pair<float,bool> > rows,cols;
  
  // pre-computed sizes
  std::vector<float> rowSizes,colSizes;

  //std::vector<GUIWidgetPtr> children; //FIXME: What for ???
  
  class CellEntry {
    public:
    int x,y;
    std::list<GUIWidgetPtr> ptr;
    
    void setRect(const AGRect2 &p) {
      for(std::list<GUIWidgetPtr>::iterator i=ptr.begin();i!=ptr.end();++i) {
        (*i)->setRect(p);
      }
    }
  };

  std::list<CellEntry> children;

  void arrangeCell(CellEntry *ce);

  bool mStructurFixed;

  //bool mInserted;
  bool mRoundPositions;
};

#endif
