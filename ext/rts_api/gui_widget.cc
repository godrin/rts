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




AGWidget::AGWidget (Rice::Object pSelf) :
ObjectTreeNode< AGWidget >(pSelf),
    sigMouseEnter ( this,"sigMouseEnter" ),
    sigMouseLeave ( this,"sigMouseLeave" ),
    sigClick ( this,"sigClick" ),
    sigDragBy ( this,"sigDragBy" ),
    mApp ( 0 ),
    mUseClientRect ( false ),
    mChildrenEventFirst ( false ),mChildrenDrawFirst ( false ),mMouseIn ( false ),mButtonDown ( false ),
    mVisible ( true ),mCaching ( false ),
    mHasFocus ( false ),mFocus ( 0 )

{
  CTRACE;
  
  mEventsInited=false;

  mChangeRect=AGRect2 ( 0,0,0,0 );
  mCache=0;
  mCacheTouched=false;
  mModal=false;

}

AGWidget::~AGWidget() throw() {
  
  CTRACE;
}
/*
void AGWidget::setSelf(const GUIWidgetPtr &p) {
  assert(self.is_nil());
  self=p;
}
*/




void AGWidget::eventChildrenDeleted ( Ptr pWidget ) {
}


void AGWidget::draw ( AGPainter &p ) {
}


void AGWidget::drawAll ( AGPainter &p ) {

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

    ObjectList children=getChildren();
    ObjectRIterator i=children.rbegin(); // draw from back to front
    std::cout<<"drawAll 3"<<std::endl;
    std::cout<<"Children size:"<<this<<"  "<<typeid(*this).name()<<"  "<<children.size()<<std::endl;

    for ( ;i!=children.rend();i++ ) {
      drawChild ( p,*i);
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

void AGWidget::drawChild ( AGPainter &p,const GUIWidgetPtr &pWidget ) {
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

  ObjectIterator i;

  ObjectList children=getChildren(); // copy children, so that changes do not affect iteration
  for ( i=children.begin();i!=children.end() && !processed; i++ )
    processed=letChildProcess ( *i,event );

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

bool AGWidget::letChildProcess ( const GUIWidgetPtr &pChild,AGEvent *event ) {
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
    mTooltipWidget=Create<AGTooltip>();
    (*mTooltipWidget)->setTooltip( mTooltip );
    getApp()->setTooltip ( mTooltipWidget );
  }

  return false;
}
bool AGWidget::eventMouseLeave() {
  if ( mTooltipWidget ) {
    getApp()->resetTooltip ( mTooltipWidget );
    mTooltipWidget.reset();
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
          Nullable<Rice::Data_Object<AGWidget> > overlay=getApp()->getOverlay();

          if ( !isParent (*overlay ) )
            app->setOverlay ( 0 );
        }
        if ( !isParent ( *getApp()->getOverlay() ) )
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
  ObjectList children=getChildren();
  for ( ObjectIterator i=children.begin();i!=children.end();i++ ) {
    if ( containsPoint ( *i,pPosition ) ) {
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



void AGWidget::addChild ( GUIWidgetPtr w ) {
  assert(w);

  ObjectTreeNode<AGWidget>::removeChild(w);
  ObjectTreeNode<AGWidget>::addChildFront(w);

  if ( mHasFocus && w->canFocus() ) {
    gainFocus ( w );
  }
  queryRedraw();
}


void AGWidget::addChildBack ( GUIWidgetPtr w ) {
  ObjectTreeNode<AGWidget>::removeChild(w);
  ObjectTreeNode<AGWidget>::addChildBack(w);
  assert(w);

  if ( mHasFocus && w->canFocus() ) {
    gainFocus ( w );
  }
  queryRedraw();
}

void AGWidget::regChange() {
  
  REMOVE THIS ???????????????????????
  
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
  
  if ( mCache&& ( getRect().width() !=pRect.width() ||getRect().height() !=pRect.height() ) )
    setCaching ( true );

  
  
  regChange();
  mRect=pRect;
  regChange();
  
  Nullable<Ptr> parent=getParent();
  if ( parent )
    (*parent)->redraw();

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



Nullable<AGWidget::Ptr> AGWidget::getParent() const{
  ObjectList l=getParents();
  for(ObjectIterator i=l.begin();i!=l.end();i++)
    return *i;
  return Nullable<AGWidget::Ptr>();
}

AGVector2 AGWidget::getScreenPosition() const {
  return getScreenRect().getV0();
}

/**
 * returns the extends of this widget wrt. to the screen-coordinates
 */
AGRect2 AGWidget::getScreenRect() const {
  AGRect2 r=getRect();
  if ( getParent() ) {
    AGRect2 result=(*getParent())->toScreen ( getRect() );
    return result;
  }
  return r;
}

AGRect2 AGWidget::toScreen ( const AGRect2&p ) const {
  AGRect2 r=innerToOuter ( p );
  if ( getParent())
    r=(*getParent())->toScreen ( r );
  return r;
}

AGVector2 AGWidget::toScreen ( const AGVector2&p ) const {
  AGVector2 r=innerToOuter ( p );
  if ( getParent() )
    r=(*getParent())->toScreen ( r );
  return r;
}


AGRect2 AGWidget::fromScreen ( const AGRect2 &p ) const {
  AGRect2 r=outerToInner ( p );
  if ( getParent() )
    r=(*getParent())->toScreen ( r );
  return r;
}



AGVector2 AGWidget::fromScreen ( const AGVector2 &p ) const {
  AGVector2 r=outerToInner ( p );
  if ( getParent() )
    r=(*getParent())->toScreen ( r );
  return r;
}

bool AGWidget::canFocus() const {
  ObjectList children=getChildren();
  ObjectIterator i=children.begin();

  for ( ;i!=children.end();i++ )
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
    (*mFocus)->eventLostFocus();
  mHasFocus=false;

  mFocus=Nullable<Ptr>();

  if ( getChildren().size() >0 )
    ( *getChildren().begin() )->eventLostFocus();

  return false;
}

void AGWidget::gainCompleteFocus ( const GUIWidgetPtr &pWidget ) {
#ifdef FOCUS_BY_SORT
  if ( getParent() )
    (*getParent())->gainCompleteFocus ( getSelf() );
  if ( pWidget ) {
    //ObjectList children=getChildren();
    //ObjectIterator i=std::find ( children.begin(),children.end(),pWidget );
    //if ( i!=children.end() ) {
      removeChild(pWidget);
      //mChildren.erase ( i );
      //assert(pWidget);
      ObjectTreeNode<AGWidget>::addChildFront(pWidget);
      //mChildren.push_front ( pWidget );
    //}
  }
#endif
}

void AGWidget::gainFocus ( const GUIWidgetPtr &pWidget ) {
  if ( pWidget ) {
      if ( getChildren().size() >0 ) {
        ( *getChildren().begin() )->eventLostFocus();
        removeChild(pWidget);
      //mChildren.erase ( i );
      //assert(pWidget);
      
      ObjectTreeNode<AGWidget>::addChildFront(pWidget);
      pWidget->eventGotFocus();
/*
    ObjectList children=getChildren();
    Children::iterator i=std::find ( mChildren.begin(),mChildren.end(),pWidget );
    if ( i!=mChildren.end() ) {
      mChildren.erase ( i );

      if ( mChildren.size() >0 )
        ( *mChildren.begin() )->eventLostFocus();
      assert(pWidget);
      mChildren.push_front ( pWidget );
      pWidget->eventGotFocus();
*/
      }
  } else if ( getParent() ) {
    if ( canFocus() ) {
      (*getParent())->gainFocus ( getSelf());
    }
  }
}

void AGWidget::gainFocus() {
  if ( getParent() ) {
    if ( canFocus() ) {
      (*getParent())->gainFocus ( getSelf() );
    }
  }
}

void AGWidget::gainFocusDown ( const GUIWidgetPtr &pWidget ) {
  if (hasChild(pWidget)) {
    // found
    if ( !mHasFocus ) {
      if ( getParent() )
        (*getParent())->gainFocus ( getSelf() );
      else {
        mHasFocus=true;
        eventGotFocus();
      }
    }

    if ( mFocus!=pWidget ) {
      if ( mFocus )
        (*mFocus)->eventLostFocus();
      mFocus=pWidget;
      (*mFocus)->eventGotFocus();
    }
  } else {
    ObjectList children=getChildren();
    
    for (ObjectIterator i=children.begin();i!=children.end();i++ )
      ( *i )->gainFocusDown ( pWidget );
  }
}

void AGWidget::checkFocus() {
  if ( hasChildren() >0 && mFocus && mHasFocus ) {
    if ( mFocus!=*getChildren().begin() ) {
      removeChild(*mFocus);
      addChildFront(*mFocus);
    }
  }
}

bool AGWidget::hasFocus ( const GUIWidgetPtr &pWidget ) {
  if ( pWidget.is_nil() ) {
    if ( getParent() )
      return (*getParent())->hasFocus ( getSelf() );
    else
      return true;
  }
  if (!hasChildren())
    return true; // some error

  if ( *getChildren().begin() ==pWidget ) {
    if ( getParent() )
      return (*getParent())->hasFocus ( getSelf() ); // ok - so go on and check if "this" has focus
    return true; // ok
  }

  return false;
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
    std::cout<<"self:"<<getSelf()<<std::endl;
    return getSelf();
  }


  ObjectList children=getChildren();
  Nullable<Ptr> p;
  for(ObjectIterator i=children.begin();i!=children.end();i++) {
    Ptr p=(*i)->getChild(pName);
    if(p)
      break;
  }
  return *p; // may crash FIXME
}

void AGWidget::setModal ( bool pModal ) {
  mModal=pModal;
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
  ObjectList children=getChildren();
  
  for ( ObjectIterator i=children.begin();i!=children.end();++i )
    if ( ( *i )->checkRedraw() )
      return true;
  return false;
}

void AGWidget::prepareDrawAll() {
  if ( !mVisible )
    return;

  ObjectList children=getChildren();
  for(ObjectIterator i=children.begin();i!=children.end();i++)
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

      ObjectList children=getChildren();
      ObjectRIterator i=children.rbegin(); // draw from back to front

      for ( ;i!=children.rend();i++ )
        ( *i )->drawAll ( p );

      if ( mChildrenDrawFirst )
        draw ( p );

      drawAfter ( p );

      setDrawn();

      if ( getParent() ) {
        (*getParent())->queryRedraw();
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
    mCache=new AGTexture ( ( int ) getRect().width(), ( int ) getRect().height() );

    mCacheTouched=true;
  }
}

void AGWidget::setDrawn() {
  if ( !mVisible )
    return;

  mCacheTouched=false;
  ObjectList children;
  for ( ObjectIterator i=children.begin();i!=children.end();++i )
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
  ObjectList children=getChildren();
  for ( ObjectIterator i=children.begin();i!=children.end();++i )
    ( *i )->useTexturesRecursive();
}

AGRect2 AGWidget::getChangeRect() {
  AGRect2 r=mChangeRect;

  ObjectList children=getChildren();
  for ( ObjectIterator i=children.begin();i!=children.end();++i ) {
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
  ObjectList children=getChildren();
  for ( ObjectIterator i=children.begin();i!=children.end();++i )
    ( *i )->sigTick ( pTime );
}

void AGWidget::close() {
  CTRACE;
  Nullable<Ptr> p=getParent();
  if ( p ) {
    (*p)->removeChild ( getSelf() );
  }
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

  ObjectList children= getChildren();
  for ( ObjectIterator i=children.begin();i!=children.end();i++ )
    ( *i )->acquireClipping ( p );

  //  cdebug("clipping after:"<<p.toString());
  return;
}


std::list<AGRect2> AGWidget::aquireChanges() {
  std::list<AGRect2> l;

  ObjectList children=getChildren();
  for ( ObjectIterator i=children.begin();i!=children.end();i++ ) {
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
  ObjectList children=getChildren();
  for ( ObjectIterator i=children.begin();i!=children.end();i++ )
    ( *i )->clearChangeRects();
}

AGApplication *AGWidget::getApp() {
  if ( !mApp )
    if ( getParent() )
      return (*getParent())->getApp();
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
bool AGWidget::containsPoint ( const GUIWidgetPtr &pWidget,const AGVector2 &pVector ) const {
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
  ObjectList children=getChildren();
  for ( ObjectIterator i=children.begin();i!=children.end();i++ )
    ( *i )->initEvents();
}

void AGWidget::eventInitEvents() {

}


Nullable<AGWidget::Ptr> AGWidget::getFocusedWidget() {
  Nullable<AGWidget::Ptr> found;
  ObjectList children=getChildren();
  for ( ObjectRIterator i=children.rbegin();i!=children.rend();i++ ) {
    found= ( *i )->getFocusedWidget();
    if ( found )
      return *found;
  }
  if(canFocus())
    return Rice::Data_Object<AGWidget>(getSelf());
  return found;
}
// kate: indent-mode cstyle; space-indent on; indent-width 2; 
