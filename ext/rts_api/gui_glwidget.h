#ifndef AG_GLWIDGET_H
#define AG_GLWIDGET_H

// INCLUDE_SWIG - used to filter, which files are included in swig-interfacing


#include <gui_widget.h>
#include <gui_geometry.h>

class AGEXPORT AGGLWidget:public AGWidget
{
 public:
  AGGLWidget(AGWidget *pParent,const AGRect2 &r);

  virtual void drawGL();
  
  virtual void drawAll(AGPainter &p);
  
  float getRatio() const;

  void setPerspective(float openAngle,float near,float far);

 private:
  void beginGL();
  void endGL();

  AGMatrix4 pMatrix,mMatrix;
};

#endif
