#ifndef AG_ABSTRACT_APPLICATION_H
#define AG_ABSTRACT_APPLICATION_H


class GUIEvent {
};

class AGAbstractApplication {
  public:
  virtual void handleEvent(const GUIEvent &event)=0;
};

#endif
