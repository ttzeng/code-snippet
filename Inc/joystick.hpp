#ifndef JOYSTICK_HPP
#define JOYSTICK_HPP

class joystick {
  public:
    virtual void read(int& x, int& y, bool& button, int normalized = 0) = 0;
};

#endif  // JOYSTICK_HPP
