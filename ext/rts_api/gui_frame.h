#ifndef AG_FRAME_H
#define AG_FRAME_H

#include <gui_widget.h>
#include <gui_border.h>
#include <gui_background.h>

// INCLUDE_SWIG - used to filter, which files are included in swig-interfacing

class AGEXPORT AGFrame:public AGWidget
{
 public:
  AGFrame(const GUIWidgetPtr &pParent,const AGRect2 &pRect,int width,int widthH=-1); // transparent frame
  AGFrame(const GUIWidgetPtr &pParent,const AGRect2 &pRect,const AGBorder &pBorder);
  ~AGFrame() throw();

  void setBackground(const AGBackground &pBg);

  AGRect2 getClientRect() const;

  void draw(AGPainter &p);
  void prepareDraw();
  
 private:
  int mWidth;
  int mWidthH;
  AGBorder *mBorder;
  AGBackground *mBg;
  AGTexture mTexture;
  bool mTextureInited;
  bool mUseTexture;
};

#endif
