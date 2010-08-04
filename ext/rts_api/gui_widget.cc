/*
 * Copyright (c) 2005 by David Kamphausen. All rights reserved.
 *
 * ag_widget.cc
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

#include <basic_debug.h>

#include <gui_widget.h>
#include <gui_screen.h>
#include <gui_main.h>
#include <gui_menu.h>
#include <map>
#include <iostream>
#include <algorithm>
#include <typeinfo>
#include <gui_tooltip.h>
#include <gui_application.h>
#include <gui_config.h>
#include <gui_clip.h>
#include <gui_painter.h>
#include <basic_algebra.h>


#define FOCUS_BY_SORT
#include <rice/Data_Type_defn.hpp>
#include <rice/Data_Type.hpp>


using namespace std;

static bool gNewClippingTechnique=true;

void setNewClippingTechnique ( bool f ) {
  gNewClippingTechnique=f;
}
bool getNewClippingTechnique() {
  return gNewClippingTechnique;
}




AGWidget::AGWidget ( const GUIWidgetPtr &pParent,const AGRect2 &r ) :
    sigMouseEnter ( this,"sigMouseEnter" ),
    sigMouseLeave ( this,"sigMouseLeave" ),
    sigClick ( this,"sigClick" ),
    sigDragBy ( this,"sigDragBy" ),
    mApp ( 0 ),
    mRect ( r ),mClientWorld ( r.origin() ),mUseClientRect ( false ),
    mParent ( pParent ),mChildrenEventFirst ( false ),mChildrenDrawFirst ( false ),mMouseIn ( false ),mButtonDown ( false ),
    mFixedWidth ( false ),mFixedHeight ( false ),mVisible ( true ),mCaching ( false ),
    mHasFocus ( false ),mFocus ( 0 )

{
  pseudoSelf=0;
  CTRACE;
  mEventsInited=false;
  if ( mParent )
    mParent->addChildRef ( this );

  mChangeRect=AGRect2 ( 0,0,0,0 );
  mCache=0;
  mCacheTouched=false;
  mTooltipWidget=0;
  mModal=false;

}

AGWidget::~AGWidget() throw() {
  CTRACE;
  Children::iterator i=mChildren.begin();
  for ( ;i!=mChildren.end();i++ ) {
    std::cout<<"Trying to setParent of "<<*i<<std::endl;
    if(*i)
      ( *i )->setParent ( GUIWidgetPtr(0) );
  }
  for ( ChildrenSet::iterator i=mRefChildren.begin();i!=mRefChildren.end();i++ ) {
    if(*i)
      (*i)->setParent ( GUIWidgetPtr() );
  }

  if ( getParent() ) {
    std::cout<<"parent->eventChildDeleted:"<<getParent().widget()<<std::endl;
    getParent()->eventChildrenDeleted ( *self() );
  }
  delete pseudoSelf;
  
  for(std::set<GUIWidgetPtr*>::iterator i=mPtrs.begin();i!=mPtrs.end();i++) {
    if(**i)
      (*i)->clear();
  }

}

void AGWidget::regPtr(GUIWidgetPtr *p) {
  if(pseudoSelf) {
    CTRACE;
    //throw int();
  }
  CTRACE;
  mPtrs.insert(p);
}
void AGWidget::unregPtr(GUIWidgetPtr *p)  {
  CTRACE;
  mPtrs.erase(p);
}

  
GUIWidgetPtr *AGWidget::self() {
  // lookout for ruby-"selfs" 
  std::set<GUIWidgetPtr*>::iterator i=mPtrs.begin();
  for(;i!=mPtrs.end();i++) {
    if((*i)->isRuby())
      return *i;
  }
  
  if(pseudoSelf) {
    if(mPtrs.size()>0) {
      std::cout<<"mPtrs found, but pseudoSelf is defined !!????"<<std::endl;
      //throw std::runtime_error("); // when pseudo self is generated, then mPtr should be created
    }
    return pseudoSelf;
  }
  std::cout<<"creating pseudoself for:"<<getName()<<"  "<<typeid(*this).name()<<"  "<<this<<std::endl;
  
  //*((char*)0)=12; // crash
  
  
  pseudoSelf=new GUIWidgetPtr(this);
  return pseudoSelf;
}



AGWidget::Children AGWidget::getChildren() {
  return mChildren;
}


void AGWidget::removeChild ( GUIWidgetPtr w ) {
  Children::iterator i=std::find ( mChildren.begin(),mChildren.end(),w );
  if ( i!=mChildren.end() ) {
    mChildren.erase ( i );
    w->setParent ( GUIWidgetPtr(0) );
  }
}


void AGWidget::eventChildrenDeleted ( GUIWidgetPtr pWidget ) {
  CTRACE;
  Children::iterator i=mChildren.begin();
  for ( ;i!=mChildren.end();i++ ) {
    if ( *i==pWidget ) {
      std::cout<<"erase one"<<std::endl;
      i=mChildren.erase ( i );
      std::cout<<"eraseddd one"<<std::endl;
      //break; // do not break, beacuse a list could have this child more than once ???
    }
  }
  i=mToClear.begin();
  for ( ;i!=mToClear.end();i++ ) {
    if ( *i==pWidget ) {
      i=mToClear.erase ( i );
      // break; // same as above
    }
  }
  mRefChildren.erase ( pWidget.widget());
}


void AGWidget::draw ( AGPainter &p ) {
}

void AGWidget::delObjects() {
  // clearing widgets
  if ( mToClear.size() ) {
    Children::iterator i=mToClear.begin();
    for ( ;i!=mToClear.end();i++ ) {
      ( *i )->setParent ( GUIWidgetPtr(0) ); // lets play it safe
      delete i->widget();
    }
    mToClear.clear();
  }
}

void AGWidget::drawAll ( AGPainter &p ) {
  delObjects();

  if ( !mVisible )
    return;

  if ( mCache ) {
    std::cout<<"blt..."<<std::endl;
    p.blit ( *mCache,getRect(),getRect().origin() );
    std::cout<<"blt!"<<std::endl;
  } else {
    std::cout<<"drawAll 0"<<std::endl;
    p.pushMatrix();
    std::cout<<"drawAll 01"<<std::endl;

    p.clip ( getRect() );
    std::cout<<"drawAll 02"<<std::endl;
    //p.transform(getRect());
    AGMatrix3 tmp=innerToOuter().getMatrix();
    std::cout<<"drawAll 03"<<std::endl;
    p.transform ( tmp );
    std::cout<<"drawAll 1"<<std::endl;

    if ( !mChildrenDrawFirst )
      draw ( p );
    std::cout<<"drawAll 2"<<std::endl;

    Children::reverse_iterator i=mChildren.rbegin(); // draw from back to front
    std::cout<<"drawAll 3"<<std::endl;

    for ( ;i!=mChildren.rend();i++ ) {
      std::cout<<"DrawChild:"<<(i->widget())<<std::endl;
      drawChild ( p,i->widget() );
      std::cout<<"DrawChild - ok "<<(i->widget())<<std::endl;
    }
    std::cout<<"drawAll 4"<<std::endl;

    if ( mChildrenDrawFirst ) {
      std::cout<<"Draw me "<<this<<":"<<typeid(*this).name()<<std::endl;
      draw ( p );
      std::cout<<"Draw me ok "<<this<<":"<<typeid(*this).name()<<std::endl;
    }
    std::cout<<"drawAll 5"<<std::endl;

    drawAfter ( p );
    std::cout<<"drawAll 6"<<std::endl;

    p.popMatrix();
        std::cout<<"drawAll 7"<<std::endl;

    setDrawn();
        std::cout<<"drawAll 8"<<std::endl;

  }
}

void AGWidget::drawChild ( AGPainter &p,AGWidget *pWidget ) {
  pWidget->drawAll ( p );
}

AGProjection2D AGWidget::getClientProjection() const {
  return mClientProj;
}

AGRect2 AGWidget::getClientWorld() const {
  return mClientWorld;
}


AGRect2 AGWidget::getRect() const {
  std::cout<<"AGWidget::getRect:"<<mRect.toString()<<std::endl;
  return mRect;
}

AGRect2 AGWidget::getClientRect() const {
  if ( mUseClientRect )
    return mClientWorld;
  return mRect.origin();
}

void AGWidget::setClient ( const AGRect2 &pWorld,const AGProjection2D &pProjection ) {
  mClientWorld=pWorld;
  mClientProj=pProjection;
  assert ( isInvertable ( mClientProj.getMatrix() ) );
  mUseClientRect=true;
}

SignalWrapper AGWidget::getSigMouseEnter() {
  return SignalWrapper ( &sigMouseEnter );
}
SignalWrapper AGWidget::getSigMouseLeave() {
  return SignalWrapper ( &sigMouseLeave );
}
SignalWrapper AGWidget::getSigClick() {
  return SignalWrapper ( &sigClick );
}
SignalWrapper AGWidget::getSigDragBy() {
  return SignalWrapper ( &sigDragBy );
}


bool AGWidget::processEvent ( AGEvent *event ) {
  //CTRACE;
  if ( !mVisible )
    return false;

  bool processed = false;
  // do i have a capturehook set ? (modal)
  // i will send that event to my children

  Children::iterator i;

  Children children=mChildren; // copy children, so that changes do not affect iteration
  for ( i=children.begin();i!=children.end() && !processed; i++ )
    processed=letChildProcess ( i->widget(),event );

  if ( processed )
    return processed;

  event->setCaller ( this );

  // let me see if i can process it myself
  if ( AGMessageObject::processEvent ( event ) )
    return true;

  checkFocus();
  if ( mModal )
    return true;
  return false;
}

bool AGWidget::letChildProcess ( AGWidget *pChild,AGEvent *event ) {
  bool retValue;
  AGVector2 old=event->getRelMousePosition();
  AGVector2 newP=outerToInner().project ( old );
  /*
  if(mUseClientRect)
    newP=mClientProj.inverse().project(old-mRect.getV0()); //FIXME - mRect must influence this, too (????)
  else
    newP=old-getRect().getV0();
   */
  event->setRelMousePosition ( newP );
  bool wasClipped=event->isClipped();

  event->setClipped ( wasClipped || ( !getRect().contains ( old ) ) );

  retValue=pChild->processEvent ( event );

  event->setClipped ( wasClipped );
  event->setRelMousePosition ( old );

  return retValue;
}


bool AGWidget::eventShow() {
  return false;
}
bool AGWidget::eventHide() {
  return false;
}

bool AGWidget::eventMouseEnter() {
  if ( mTooltip.length() ) {
    mTooltipWidget=new AGTooltip ( getScreenRect(),mTooltip );
    getApp()->setTooltip ( mTooltipWidget );
  }

  return false;
}
bool AGWidget::eventMouseLeave() {
  if ( mTooltipWidget ) {
    getApp()->resetTooltip ( mTooltipWidget );
    mTooltipWidget=0;
  }
  return false;
}

bool AGWidget::hovered() const {
  return mMouseIn;
}


bool AGWidget::eventMouseMotion ( AGEvent *e ) {
  if ( !visible() )
    return false;

  if ( e->isSDLEvent() ) {
    //cdebug(e->isFocusTaken()<<"::"<<getName());
    if ( getRect().contains ( e->getRelMousePosition() ) && !e->isClipped() ) {
      if ( !mMouseIn ) {
        mMouseIn=true;
        eventMouseEnter() || sigMouseEnter ( e );
      }
    } else {
      if ( mMouseIn ) {
        mMouseIn=false;
        eventMouseLeave() || sigMouseLeave ( e );
      }
    }
    if ( mButtonDown ) {
      AGVector2 v=e->getMousePosition()-mOldMousePos;
      e->setVector ( v );
      eventDragBy ( e,v ) || sigDragBy ( e );
      mOldMousePos=e->getMousePosition();
    }
  }
  return false;
}

bool AGWidget::eventMouseButtonDown ( AGEvent *e ) {
  CTRACE;
  if ( e->isSDLEvent() ) {
    if ( getRect().contains ( e->getRelMousePosition() ) ) {
      cdebug ( getName() );
      mButtonDown=true;
      mOldMousePos=e->getMousePosition();
      return false;
    }
  }
  return false;
}

bool AGWidget::eventMouseButtonUp ( AGEvent *e ) {
  bool was=mButtonDown;

  mButtonDown=false;

  if ( e->isSDLEvent() ) {
    if ( getRect().contains ( e->getRelMousePosition() ) ) {
      if ( was ) {
        e->setName ( "sigClick" );
        AGApplication *app=getApp();
        assert ( app );
        if ( app ) {
          AGWidget *overlay=getApp()->getOverlay();

          if ( !isParent (GUIWidgetPtr( overlay ) ))
            app->setOverlay ( 0 );
        }
        if ( !isParent ( getApp()->getOverlay() ) )
          getApp()->setOverlay ( 0 );

        if ( canFocus() )
          gainFocus();

        return doClick ( e );

      }
    }
  }
  return false;
}

bool AGWidget::eventMouseButtonDownClipped ( AGEvent *pEvent,const AGVector2 &pPosition ) {
  AGProjection2D inv=mClientProj.inverse();
  AGVector2 cPos=inv.project ( pPosition );
  for ( Children::iterator i=mChildren.begin();i!=mChildren.end();i++ ) {
    if ( containsPoint ( i->widget(),pPosition ) ) {
      if ( ( *i )->eventMouseButtonDownClipped ( pEvent,cPos ) )
        return true;
    }
  }
  return false;
}
bool AGWidget::eventMouseButtonUpClipped ( AGEvent *pEvent,const AGVector2 &pPosition ) {
  return false;
}
bool AGWidget::eventMouseMotionClipped ( AGEvent *pEvent,const AGVector2 &pPosition ) {
  return false;
}


bool AGWidget::doClick ( AGEvent *e ) {
  return ( eventMouseClick ( e ) || sigClick ( e ) );
}

bool AGWidget::eventMouseClick ( AGEvent *m ) {
  return false;
}


void AGWidget::addChildRef ( AGWidget *pWidget ) {
  assert ( pWidget );

  mRefChildren.insert ( pWidget );
}


void AGWidget::addChild ( GUIWidgetPtr w ) {
  assert(w);
  if ( w->getParent() )
    w->getParent()->mRefChildren.erase ( w.widget() );
  mRefChildren.erase ( w.widget() );

  mChildren.push_front ( w ); // set on top
  if ( mHasFocus && w->canFocus() ) {
    gainFocus ( w );
  }
  if ( !w->getParent() )
    w->setParent ( *self() );
  queryRedraw();
}

void AGWidget::clear() throw() {
  // delay it till be draw everything - so this doesn't kill widgets while processing events
  std::copy ( mChildren.begin(),mChildren.end(),std::back_inserter ( mToClear ) );
  mChildren.clear();
}

void AGWidget::erase ( const GUIWidgetPtr &w ) {
  Children::iterator i=std::find ( mChildren.begin(),mChildren.end(),w );
  if ( i!=mChildren.end() ) {
    mToClear.push_back ( w );

    mChildren.erase ( i );
  }
}

void AGWidget::addChildBack ( GUIWidgetPtr w ) {
  assert(w);
  if ( w->getParent() )
    w->getParent()->mRefChildren.erase ( w.widget() );
  mRefChildren.erase ( w.widget() );

  // check if children already exists
  Children::iterator i;
  do {
    i=std::find ( mChildren.begin(),mChildren.end(),w );
    if ( i!=mChildren.end() )
      mChildren.erase ( i );
  } while ( i!=mChildren.end() );


  mChildren.push_back ( w ); // set on top

  if ( mHasFocus && w->canFocus() ) {
    gainFocus ( w );
  }
  if ( !w->getParent() )
    w->setParent ( *self() );
  queryRedraw();
}

void AGWidget::regChange() {
  AGRect2 t=getScreenRect().grow ( 5 );

  pushChangeRect ( t );

  if ( mChangeRect.width() ==0 || mChangeRect.height() ==0 )
    mChangeRect=t;
  else {
    mChangeRect.include ( t[0] );
    mChangeRect.include ( t[1] );
  }
}

void AGWidget::setRectInterface ( AGRect2 pRect ) {
  setRect(pRect);
}


void AGWidget::setRect ( const AGRect2 &pRect ) {
  if(!(pRect.w()>=0)) {
    std::cout<<"Invalid height in setRect"<<std::endl;
  }
  
  if ( mCache&& ( width() !=pRect.width() ||height() !=pRect.height() ) )
    setCaching ( true );

  
  
  regChange();
  mRect=pRect;
  regChange();
  if ( mParent )
    mParent->redraw();

}

float AGWidget::minWidth() const {
  // accumulate max
  Children::const_iterator i=mChildren.begin();
  float m=0;

  for ( ;i!=mChildren.end();i++ ) {
    GUIWidgetPtr p=*i;
    m=std::max ( m, p->minWidth() );
  }

  return m;
}

float AGWidget::minHeight() const {
  // accumulate max
  Children::const_iterator i=mChildren.begin();
  float m=0;

  for ( ;i!=mChildren.end();i++ ) {
    GUIWidgetPtr p=*i;
    m=std::max ( m, p->minHeight() );
  }

  return m;
}

float AGWidget::width() const {
  return mRect.w();
}

float AGWidget::height() const {
  return mRect.h();
}

bool AGWidget::fixedWidth() const {
  return mFixedWidth;
}

bool AGWidget::fixedHeight() const {
  return mFixedHeight;
}

void AGWidget::setWidth ( float w ) {
  bool changed= ( width() !=w );
  regChange();
  mRect.setWidth ( w );
  if ( mCache && changed )
    setCaching ( true );
  regChange();
  queryRedraw();
}
void AGWidget::setHeight ( float h ) {
  if(!(h>=0)) {
    std::cout<<"Invalid height given !!!"<<std::endl;
  }
  
  bool changed= ( height() !=h );
  regChange();
  mRect.setHeight ( h );
  if ( mCache && changed )
    setCaching ( true );
  regChange();
  queryRedraw();
}

void AGWidget::setTop ( float y ) {
  regChange();
  mRect.setTop ( y );
  regChange();
}
void AGWidget::setLeft ( float x ) {
  regChange();
  mRect.setLeft ( x );
  regChange();
}
float AGWidget::bottom() const {
  return mRect[1][1];
}
float AGWidget::right() const {
  return mRect[1][0];
}


float AGWidget::top() const {
  return mRect.y();
}

float AGWidget::left() const {
  return mRect.x();
}

void AGWidget::show() {
  mVisible=true;
  queryRedraw();
}
void AGWidget::hide() {
  mVisible=false;
  queryRedraw();
}

void AGWidget::setVisible ( bool v ) {
  if ( mVisible!=v ) {
    queryRedraw();
  }
  mVisible=v;
}


void AGWidget::setParent ( const GUIWidgetPtr &pParent ) {
  CTRACE;

  if ( !mParent ) {
    GUIWidgetPtr old=mParent;
    mParent=pParent;
    if ( mParent==0 && old!=0 )
      old->eventChildrenDeleted ( *self() );
  }

  mParent=pParent;
  
  // add to refchildren !!! FIXME TODO
}


GUIWidgetPtr AGWidget::getParent() {
  return mParent;
}

AGVector2 AGWidget::getScreenPosition() const {
  return getScreenRect().getV0();
}

/**
 * returns the extends of this widget wrt. to the screen-coordinates
 */
AGRect2 AGWidget::getScreenRect() const {
  AGRect2 r=getRect();
  if ( mParent ) {
    AGRect2 result=mParent->toScreen ( getRect() );
    return result;
  }
  return r;
}

AGRect2 AGWidget::toScreen ( const AGRect2&p ) const {
  AGRect2 r=innerToOuter ( p );
  if ( mParent )
    r=mParent->toScreen ( r );
  return r;
}

AGVector2 AGWidget::toScreen ( const AGVector2&p ) const {
  AGVector2 r=innerToOuter ( p );
  if ( mParent )
    r=mParent->toScreen ( r );
  return r;
}


AGRect2 AGWidget::fromScreen ( const AGRect2 &p ) const {
  AGRect2 r=outerToInner ( p );
  if ( mParent )
    r=mParent->toScreen ( r );
  return r;
}



AGVector2 AGWidget::fromScreen ( const AGVector2 &p ) const {
  AGVector2 r=outerToInner ( p );
  if ( mParent )
    r=mParent->toScreen ( r );
  return r;
  /*  if(!mParent)
    return p;
  AGRect2 r(mParent->getScreenRect());
  return p-r[0];*/
}

bool AGWidget::canFocus() const {
  Children::const_iterator i=mChildren.begin();

  for ( ;i!=mChildren.end();i++ )
    if ( ( *i )->canFocus() ) {

      return true;
    }

  return false;
}

bool AGWidget::eventGotFocus() {
  mHasFocus=true;
  return false;
}

bool AGWidget::eventLostFocus() {
  CTRACE;
  if ( mFocus )
    mFocus->eventLostFocus();
  mHasFocus=false;
  mFocus=GUIWidgetPtr();

  if ( mChildren.size() >0 )
    ( *mChildren.begin() )->eventLostFocus();

  return false;
}

void AGWidget::gainCompleteFocus ( const GUIWidgetPtr &pWidget ) {
#ifdef FOCUS_BY_SORT
  if ( mParent )
    mParent->gainCompleteFocus ( *self() );
  if ( pWidget ) {
    Children::iterator i=std::find ( mChildren.begin(),mChildren.end(),pWidget );
    if ( i!=mChildren.end() ) {
      mChildren.erase ( i );
      assert(pWidget);

      mChildren.push_front ( pWidget );
    }
  }
#endif
}

void AGWidget::gainFocus ( const GUIWidgetPtr &pWidget ) {
#ifdef FOCUS_BY_SORT
  if ( pWidget ) {
    Children::iterator i=std::find ( mChildren.begin(),mChildren.end(),pWidget );
    if ( i!=mChildren.end() ) {
      mChildren.erase ( i );

      if ( mChildren.size() >0 )
        ( *mChildren.begin() )->eventLostFocus();
      assert(pWidget);
      mChildren.push_front ( pWidget );
      pWidget->eventGotFocus();

    }
  } else if ( mParent ) {
    if ( canFocus() ) {
      mParent->gainFocus ( *self() );
    }
  }
#else
  if ( pWidget==0 && mParent )
    mParent->gainFocus ( this );
  else if ( mParent )
    mParent->gainFocus ( pWidget );
  else
    gainFocusDown ( pWidget );
#endif
}

void AGWidget::gainFocus() {
  if ( mParent ) {
    if ( canFocus() ) {
      mParent->gainFocus ( *self() );
    }
  }
}

void AGWidget::gainFocusDown ( const GUIWidgetPtr &pWidget ) {
  Children::iterator i;
  i=std::find ( mChildren.begin(),mChildren.end(),pWidget );
  if ( i!=mChildren.end() ) {
    // found
    if ( !mHasFocus ) {
      if ( mParent )
        mParent->gainFocus ( *self() );
      else {
        mHasFocus=true;
        eventGotFocus();
      }
    }

    if ( mFocus!=pWidget ) {
      if ( mFocus )
        mFocus->eventLostFocus();
      mFocus=pWidget;
      mFocus->eventGotFocus();
    }
  } else {
    for ( i=mChildren.begin();i!=mChildren.end();i++ )
      ( *i )->gainFocusDown ( pWidget );
  }
}

void AGWidget::checkFocus() {
  if ( mChildren.size() >0 && mFocus && mHasFocus ) {
    if ( mFocus!=*mChildren.begin() ) {
      Children::iterator i;

      i=std::find ( mChildren.begin(),mChildren.end(),mFocus );
      // delete children and set to front
      mChildren.erase ( i );
      assert(mFocus);
      mChildren.push_front ( mFocus );
    }
  }
}

bool AGWidget::hasFocus ( const GUIWidgetPtr &pWidget ) {
#ifdef FOCUS_BY_SORT
  if ( pWidget==0 ) {
    if ( mParent )
      return mParent->hasFocus ( *self() );
    else
      return true;
  }
  if ( mChildren.size() ==0 )
    return true; // some error

  if ( *mChildren.begin() ==pWidget ) {
    if ( mParent )
      return mParent->hasFocus ( *self() ); // ok - so go on and check if "this" has focus
    return true; // ok
  }

  return false;
#else
  if ( pWidget==0 ) {
    if ( mParent )
      return mParent->hasFocus ( this );
    else
      return true;
  } else if ( mFocus!=pWidget )
    return false;
  else if ( mParent )
    return mParent->hasFocus ( this );
  return true;
#endif
}


bool AGWidget::eventDragBy ( AGEvent *event,const AGVector2 &pDiff ) {
  return false;
}

bool AGWidget::getFocus() const {
  return mHasFocus;
}

const AGString &AGWidget::getName() const {
  return mName;
}
void AGWidget::setName ( AGString pName ) {
  mName=pName;
}

void AGWidget::drawAfter ( AGPainter &p ) {
}

bool AGWidget::visible() const {
  return mVisible;
}

/// override this and return true, if widget is opaque and you want to increase performance
bool AGWidget::isOpaque() const {
  return false;
}



GUIWidgetPtr AGWidget::getChild ( AGString pName ) {
  CTRACE;
  if ( mName==pName ) {
    std::cout<<"Child found:"<<pName<<std::endl;
    return *self();
  }


  GUIWidgetPtr w;
  Children::iterator i=mChildren.begin();

  for ( ;i!=mChildren.end();i++ ) {
    w= ( *i )->getChild ( pName );
    if ( w )
      break;
  }
  return w;
}

void AGWidget::setModal ( bool pModal ) {
  mModal=pModal;
}

/// descend down tree, but dont mark itself !
void AGWidget::mark() throw() {
  for ( Children::iterator i=mChildren.begin();i!=mChildren.end();i++ ) {
    i->ruby()->mark();
  }
}



AGWidget *toAGWidget ( AGMessageObject *o ) {
  return dynamic_cast<AGWidget*> ( o );
}


bool AGWidget::redraw() const {
  return mCacheTouched;
}

bool AGWidget::checkRedraw() const {
  if ( !mVisible )
    return false;
  if ( redraw() )
    return true;
  for ( Children::const_iterator i=mChildren.begin();i!=mChildren.end();++i )
    if ( ( *i )->checkRedraw() )
      return true;
  return false;
}

void AGWidget::prepareDrawAll() {
  if ( !mVisible )
    return;

  for ( Children::iterator i=mChildren.begin();i!=mChildren.end();++i )
    ( *i )->prepareDrawAll();

  prepareDraw();

}


void AGWidget::prepareDraw() {
  if ( !mVisible )
    return;

  if ( mCache ) {
    if ( checkRedraw() || !mCache->hasTexture() ) {
      mCache->clearContent();

      AGPainter p ( *mCache );

      if ( !mChildrenDrawFirst )
        draw ( p );

      Children::reverse_iterator i=mChildren.rbegin(); // draw from back to front

      for ( ;i!=mChildren.rend();i++ )
        ( *i )->drawAll ( p );

      if ( mChildrenDrawFirst )
        draw ( p );

      drawAfter ( p );

      setDrawn();

      if ( mParent ) {
        mParent->queryRedraw();
      }

      assert ( checkRedraw() ==false );
      assert ( mCache->hasTexture() );
    }
  }
}

/**
 * enable texture caching for this widget (widgetTextureCache in config must be enabled for this)
 * cache will be discarded whenever you modify the widget (e.g. by setting its text or the like).
 * You'll have to call queryRedraw in subclasses. This works for both gl- and sdl-mode.
 */
void AGWidget::setCaching ( bool pEnable ) {

  if ( getConfig()->get ( "widgetTextureCache" ) =="false" )
    return;
  getConfig()->set ( "widgetTextureCache","true" );

  mCaching=pEnable;
  delete mCache;

  mCache=0;
  mCacheTouched=false;
  if ( pEnable ) {
    mCache=new AGTexture ( ( int ) width(), ( int ) height() );

    mCacheTouched=true;
  }
}

void AGWidget::setDrawn() {
  if ( !mVisible )
    return;

  mCacheTouched=false;
  for ( Children::iterator i=mChildren.begin();i!=mChildren.end();++i )
    ( *i )->setDrawn();
  mChangeRect=AGRect2 ( 0,0,0,0 );
}

void AGWidget::queryRedraw() {
  //  cdebug(getName()<<"::"<<typeid(*this).name());
  mCacheTouched=true;
  regChange();
}

/**
   \brief special function for "using textures"

   within a texture-garbage-collection run all unused textures get cleaned,
   so this function "uses" the textures. This way they won't get collected
 */
void AGWidget::useTextures() {
}

/**
   \brief special function for "using textures"

   within a texture-garbage-collection run all unused textures get cleaned,
   so this function "uses" the textures. This way they won't get collected.

   This function calles useTextures() recursively. Don't override this one!
 */
void AGWidget::useTexturesRecursive() {
  useTextures();
  for ( Children::iterator i=mChildren.begin();i!=mChildren.end();++i )
    ( *i )->useTexturesRecursive();
}

AGRect2 AGWidget::getChangeRect() {
  AGRect2 r=mChangeRect;

  for ( Children::iterator i=mChildren.begin();i!=mChildren.end();++i ) {
    AGRect2 n= ( *i )->getChangeRect();
    if ( n.width() !=0 && n.height() !=0 ) {
      if ( r.width() !=0 && r.height() !=0 ) {
        r.include ( n[0] );
        r.include ( n[1] );
      } else
        r=n;
    }
  }
  return r;
}

void AGWidget::setTooltip ( const AGStringUtf8 &pTooltip ) {
  mTooltip=pTooltip;
}

void AGWidget::initHandlers() {
}

void AGWidget::eventTick ( float pTime ) {
}
void AGWidget::sigTick ( float pTime ) {
  eventTick ( pTime );
  for ( Children::iterator i=mChildren.begin();i!=mChildren.end();++i )
    ( *i )->sigTick ( pTime );
}

void AGWidget::close() {
  CTRACE;
  if ( mParent ) {
    mParent->removeChild ( *self() );
    mParent=GUIWidgetPtr();
  }
}

bool AGWidget::isParent(AGWidget* pParent)
{
  if ( mParent.widget()==pParent )
    return true;
  else if ( mParent!=0 )
    return mParent->isParent ( pParent );
  return false;

}


bool AGWidget::isParent ( const GUIWidgetPtr &pParent ) {
  return isParent(pParent.widget());
}

void AGWidget::acquireClipping ( AGClipping &p ) {
  if ( !visible() )
    return;

  //  cdebug("clipping before:"<<p.toString());
  if ( isOpaque() )
    p.exclude ( getScreenRect() );

  for ( std::list<AGRect2>::iterator i=mMyChanges.begin();i!=mMyChanges.end();i++ )
    p.include ( *i );//+getScreenPosition());

  //  cdebug("clipping in:"<<p.toString());

  for ( Children::iterator i=mChildren.begin();i!=mChildren.end();i++ )
    ( *i )->acquireClipping ( p );

  //  cdebug("clipping after:"<<p.toString());
  return;
}


std::list<AGRect2> AGWidget::aquireChanges() {
  std::list<AGRect2> l;

  for ( Children::iterator i=mChildren.begin();i!=mChildren.end();i++ ) {
    std::list<AGRect2> t= ( *i )->aquireChanges();
    // FIXME: check, if opaque and truncates rectangles
    std::copy ( t.begin(),t.end(),std::back_inserter ( l ) );
  }
  std::copy ( mMyChanges.begin(),mMyChanges.end(),std::back_inserter ( l ) );

  return l;
}
void AGWidget::pushChangeRect ( const AGRect2 &pRect ) {
  //  cdebug("push:"<<pRect);
  mMyChanges.push_back ( pRect );
}
void AGWidget::clearChangeRects() {
  //  cdebug("clearing - size was:"<<mMyChanges.size());
  mMyChanges.clear();
  for ( Children::iterator i=mChildren.begin();i!=mChildren.end();i++ )
    ( *i )->clearChangeRects();
}

AGApplication *AGWidget::getApp() {
  if ( !mApp )
    if ( mParent )
      return mParent->getApp();
  return mApp;
}

void AGWidget::setApp ( AGApplication *pApp ) {
  assert ( ( !mApp ) ||mApp==pApp|| ( pApp==0 ) );
  mApp=pApp;
}


AGRect2 AGWidget::getChildRect ( const AGRect2 &pRect ) const {
  if ( mUseClientRect )
    return mClientProj.project ( pRect );
  else
    return pRect;
}
bool AGWidget::containsPoint ( AGWidget *pWidget,const AGVector2 &pVector ) const {
  return getChildRect ( pWidget->getRect() ).contains ( pVector );
}

void AGWidget::setButtonDown ( bool value,const AGVector2 &startVector ) {
  mOldMousePos=startVector;
  mButtonDown=value;
}

AGProjection2D AGWidget::innerToOuter() const {
  AGRect2 u ( 0,0,1,1 );
  return AGProjection2D ( u,innerToOuter ( u ) );
}
AGProjection2D AGWidget::outerToInner() const {
  AGRect2 u ( 0,0,1,1 );
  return AGProjection2D ( u,outerToInner ( u ) );
}

AGRect2 AGWidget::innerToOuter ( const AGRect2 &p ) const {
  AGRect2 m=p;
std::cout<<"innerToOuter"<<m.toString()<<std::endl;
std::cout<<"use client rect:"<<mUseClientRect<<std::endl;
std::cout<<"getRect"<<getRect()<<std::endl;
std::cout<<"this:"<<typeid(this).name()<<std::endl;
std::cout<<"name:"<<getName()<<std::endl;

  if ( mUseClientRect )
    m=mClientProj.project ( m );
  return m+getRect().getV0();
}
AGVector2 AGWidget::innerToOuter ( const AGVector2 &p ) const {
  AGVector2 m=p;

  if ( mUseClientRect )
    m=mClientProj.project ( m );
  return m+getRect().getV0();
}
AGRect2 AGWidget::outerToInner ( const AGRect2 &p ) const {
  AGRect2 m=p;

  if ( mUseClientRect )
    m=mClientProj.inverse().project ( m );
  return m-getRect().getV0();
}
AGVector2 AGWidget::outerToInner ( const AGVector2 &p ) const {
  AGVector2 m=p;

  if ( mUseClientRect )
    m=mClientProj.inverse().project ( m );
  return m-getRect().getV0();
}


void AGWidget::initEvents() {
  if ( !mEventsInited )
    eventInitEvents();
  for ( Children::iterator i=mChildren.begin();i!=mChildren.end();i++ )
    ( *i )->initEvents();
}

void AGWidget::eventInitEvents() {

}
GUIWidgetPtr AGWidget::getFocusedWidget() {
  GUIWidgetPtr found;
  for ( Children::reverse_iterator i=mChildren.rbegin();i!=mChildren.rend();i++ ) {
    found= ( *i )->getFocusedWidget();
    if ( found )
      return found;
  }
  return canFocus() ?*self():GUIWidgetPtr();
}
// kate: indent-mode cstyle; space-indent on; indent-width 2; 
