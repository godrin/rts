/*
 * Copyright (c) 2005 by David Kamphausen. All rights reserved.
 *
 * ag_table.cc
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

#include <gui_table.h>
#include <basic_debug.h>

AGTable::AGTable(Rice::Object pSelf):
  AGWidget(pSelf),
  w(0),h(0),xw(0),yw(0),
  mStructurFixed(false),
  //mInserted(false),
  mRoundPositions(true)
  {
  }

AGTable::~AGTable() throw()
  {
  }

/// add a column with fixed size of 'size'
/// @param size gives to size of the column in pixels
void AGTable::addFixedColumn(float size)
  {
    /*
    if(mInserted)
      return;
    */
    if(mStructurFixed)
      throw StructureWasFixed("Structure was already fixed in addFixedColumn");
    cols.push_back(std::make_pair(size,true));
    w++;
  }
/// add a row with fixed size of 'size'
/// @param size gives to size of the row in pixels
void AGTable::addFixedRow(float size)
  {
    if(mStructurFixed)
      throw StructureWasFixed("Structure was already fixed in addFixedRow");
    rows.push_back(std::make_pair(size,true));
    h++;
  }

/// add a column with relative size.
/// @param weight
///  All weights of columns are summed up. After giving their space
///  to the fixed columns ( AGTable::addFixedColumn() ), each relative sized
///  column gets its relative size according the weight. (size_left*weight/sum(weights))
void AGTable::addColumn(float weight)
  {
    if(mStructurFixed)
      throw StructureWasFixed("Structure was already fixed in addColumn");

    if(weight<=0.0f)
      throw InvalidWeight("Weight was 0 or negative in addColumn");
    cols.push_back(std::make_pair(weight,false));
    w++;
    xw+=weight;
  }

/// add a row with relative size.
/// @param weight
///  All weights of rows are summed up. After giving their space
///  to the fixed rows ( AGTable::addFixedRow() ), each relative sized
///  row gets its relative size according the weight. (size_left*weight/sum(weights))
void AGTable::addRow(float weight)
  {
    if(mStructurFixed)
      throw StructureWasFixed("Structure was already fixed in addRow");

    if(weight<=0.0f)
      throw InvalidWeight("Weight was 0 or negative in AGTable::addRow()");
    rows.push_back(std::make_pair(weight,false));
    h++;
    yw+=weight;
  }


/// adds a widget to the given cell (px,py)
void AGTable::addChild(int px,int py,GUIWidgetPtr pWidget)
  {
    if(px>=w || py>=h || px<0 || py<0)
      {
        std::cerr<<"ERROR: wrong table-position:"<<px<<","<<py<<std::endl;
        std::cerr<<"table size is:"<<w<<","<<h<<std::endl;
        std::cerr<<"Name:"<<getName()<<std::endl;
        throw AGException("WARNING:wrong input position");
        return;
      }

    if(!mStructurFixed) 
    {
      throw StructureNotFixed("Structure was not fixed in AGTable::addChild");
    }


    CellEntry ce;
    ce.x=px;
    ce.y=py;
    ce.ptr.push_back(pWidget);
    children.push_back(ce);
      
    AGWidget::addChild(pWidget);
    pWidget->setRect(getClientRect(px,py));
  }

/// returns the Position and size of a given cell (x,y)
AGRect2 AGTable::getClientRect(int x,int y) const
{
  float fx=0,fy=0;
  
//  std::cout<<"getClientRect for "<<x<<","<<y<<std::endl;
  
  for(int mx=0;mx<x;mx++) {
  //  std::cout<<"col "<<mx<<":"<<colSizes[mx]<<std::endl;
    fx+=colSizes[mx];
    //std::cout<<"fx:"<<fx<<std::endl;
  }
  for(int my=0;my<y;my++) {
    //std::cout<<"row "<<my<<":"<<rowSizes[my]<<std::endl;
    fy+=rowSizes[my];
    //std::cout<<"fy:"<<fy<<std::endl;
  }
  AGRect2 mrect(fx,fy,colSizes[x],rowSizes[y]);
  
  return mrect;
}

void AGTable::arrangeCell(CellEntry *ce) {
  AGRect2 r=getClientRect(ce->x,ce->y);
  if(r.content()<1 || r.w()<1 || r.h()<1) {
    std::cout<<"Probably defect rectangle "<<r.toString()<<" in cell:"<<ce->x<<","<<ce->y<<" for element "<<std::endl;
    //<<ce->ptr->getName()<< " "<<typeid(*ce->ptr).name()<<std::endl;
  }
  else {
    std::cout<<"Setting rectangle "<<r.toString()<<"("<<r.w()<<";"<<r.h()<<" in cell:"<<ce->x<<","<<ce->y<<" for element "<<std::endl;
    //<<ce->ptr->getName()<< " "<<typeid(*ce->ptr).name()<<std::endl;
     
  }
  
  ce->setRect(r);
}

void AGTable::arrange() {
  for(std::list<CellEntry>::iterator i=children.begin();i!=children.end();i++) {
    arrangeCell(&*i);
  }
}
  


void AGTable::structureFinished()
{
  assert(rows.size()>0);
  assert(cols.size()>0);
  
  float fixedHeight=0,fixedWidth=0;
  
  
  for(int mx=0;mx<w;mx++) {
    if(cols[mx].second)
      fixedWidth+=cols[mx].first;
  }
  for(int my=0;my<h;my++) {
    if(rows[my].second)
      fixedHeight+=rows[my].first;
  }
  
  std::cout<<"Width:"<<getRect().width()<<std::endl;
  std::cout<<"height:"<<getRect().height()<<std::endl;
  std::cout<<"fixedWidth:"<<fixedWidth<<std::endl;
  std::cout<<"fixedheight:"<<fixedHeight<<std::endl;

    std::cout<<"NAME:"<<getName()<<std::endl;
      
    for(int px=0;px<w;px++) {
      std::cout<<"COL "<<px<<":"<<cols[px].first<<"  "<<cols[px].second<<std::endl;
    }
    for(int py=0;py<h;py++) {
      std::cout<<"ROW "<<py<<":"<<rows[py].first<<"  "<<rows[py].second<<std::endl;
    }

    colSizes=std::vector<float>(w,0.0);
    rowSizes=std::vector<float>(h,0.0);

    // assign width's and heights for all fixed !!!
    for(int mx=0;mx<w;mx++)
        {
          if(cols[mx].second)
            {
              colSizes[mx]=cols[mx].first;
            }
            else {
              float val=((getRect().width()-fixedWidth)*cols[mx].first/xw);
              colSizes[mx]=(int)val;
            }
        }
    for(int my=0;my<h;my++) {
          if(rows[my].second)
            {
              rowSizes[my]=rows[my].first;
            }
            else {
              float val=((getRect().height()-fixedHeight)*rows[my].first/yw);
              rowSizes[my]=(int)val;
            }
        }
    mStructurFixed=true;
    
    
    
    for(int mx=0;mx<w;mx++) {
      std::cout<<"COMPUTED col:"<<mx<<":"<<colSizes[mx]<<std::endl;
    }
    for(int my=0;my<h;my++) {
      std::cout<<"COMPUTED row:"<<my<<":"<<rowSizes[my]<<std::endl;
    }
}

/*
void AGTable::arrange()
  {
    CTRACE;
    int mx,my;

    // first get the fixed sizes
    int fx,fy;
    int mfx,mfy; // max
    fx=fy=0;
    mfx=mfy=0;
    

    // in y dir
    for(mx=0;mx<w;mx++)
      {
        fy=0;
        //      if(cols[mx]==0.0)
        for(my=0;my<h;my++)
          {
            if(rows[my].second)
              fy+=(int)(rows[my].first);
          }
        mfy=std::max(mfy,fy);
      }

    // x dir
    for(my=0;my<h;my++)
      {
        fx=0;
        //      if(rows[my]==0.0) // only check fixed
        for(mx=0;mx<w;mx++)
          {
            if(cols[mx].second)
              {
                fx+=(int)(cols[mx].first);
              }
          }
        mfx=std::max(mfx,fx);
      }
    std::cout<<"NAME:"<<getName()<<std::endl;
      
    for(int px=0;px<w;px++) {
      std::cout<<"COL "<<px<<":"<<cols[px].first<<"  "<<cols[px].second<<std::endl;
    }
    for(int py=0;py<h;py++) {
      std::cout<<"ROW "<<py<<":"<<rows[py].first<<"  "<<rows[py].second<<std::endl;
    }

    // TODO: assign width's and heights for all fixed !!!
    for(mx=0;mx<w;mx++)
      for(my=0;my<h;my++)
        {
          if(cols[mx].second)
            {
              GUIWidgetPtr wd=children[mx+my*w];
              if(wd)
                {
                  wd->setWidth(cols[mx].first);
                }
            }
          if(rows[my].second)
            {
              GUIWidgetPtr wd=children[mx+my*w];
              if(wd)
                {
                  wd->setHeight(rows[my].first);
                }
            }
        }

    // assign width's and height's for all non-fixed
    for(mx=0;mx<w;mx++)
      for(my=0;my<h;my++)
        {
          if(!cols[mx].second)
            {
              GUIWidgetPtr wd=children[mx+my*w];
              if(wd)
                {
                  wd->setWidth((int)((width()-mfx)*cols[mx].first/xw));
                }
            }
          if(!rows[my].second)
            {
              GUIWidgetPtr wd=children[mx+my*w];
              if(wd)
                {
                  wd->setHeight((int)((height()-mfy)*rows[my].first/yw));
                }
            }
        }

    // assign positions
    // first x
    float ax=0;
    for(mx=0;mx<w;mx++)
      {
        float maxx=0;
        for(my=0;my<h;my++)
          {
            GUIWidgetPtr wd=children[mx+my*w];
            if(wd)
              {
                wd->setLeft(ax);

                maxx=std::max(maxx,wd->width());
              }
          }
        ax+=maxx;
      }

    // now y
    float ay=0;
    for(my=0;my<h;my++)
      {
        float maxy=0;
        for(mx=0;mx<w;mx++)
          {
            GUIWidgetPtr wd=children[mx+my*w];
            if(wd)
              {
                wd->setTop(ay);

                maxy=std::max(maxy,wd->height());
              }
          }
        ay+=maxy;
      }

  }
*/

void AGTable::setRect(const AGRect2 &r) {
  AGWidget::setRect(r);
  arrange();
}

size_t AGTable::getRows() const
{
  return rows.size();
}
size_t AGTable::getColumns() const
{
  return cols.size();
}

float AGTable::getColumn(size_t c) const
{
  assert(c<cols.size());
  return cols[c].first;
}
float AGTable::getRow(size_t c) const
{
  assert(c<rows.size());
  return rows[c].first;
}


void AGTable::modifyColumn(size_t index,float w)
  {
    if(cols.size()>index)
      {
        cols[index].first=w;
      }
    arrange();
  }
void AGTable::modifyRow(size_t index,float w)
  {
    CTRACE;
    if(rows.size()>index)
      {
        rows[index].first=w;
      }
    arrange();
  }
