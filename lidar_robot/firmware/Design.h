#ifndef __DESIGN_H__
#define __DESIGN_H__

class Design {
  private:
    int l1Pin;
    int l2Pin;
    int l3Pin;
    int l4Pin;
    int l5Pin;
    int l6Pin;

  public:
    void init(int _l1Pin, int _l2Pin, int _l3Pin, int _l4Pin, int _l5Pin, int _l6Pin);
    void inOut(int inDelay);
    void on();
    void on(int line);
    void off();
    void off(int line);

};
#endif
