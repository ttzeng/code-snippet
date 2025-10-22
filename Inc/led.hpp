#ifndef LED_HPP
#define LED_HPP

class Led {
  public:
    /**
     * @brief Overload the assignment operator to set LED state
     * @param state true for ON, false for OFF
     * @return Reference to this Led object
     */
    Led& operator = (bool state) {
        set_state(state);
        return *this;
    }

    /**
     * @brief Boolean conversion operator to get current LED state
     * @return true if LED is ON, false if OFF
     */
    operator bool() const {
        return get_state();
    }

  protected:
    /**
     * @brief Set the LED to a specific state
     * @param state true for ON, false for OFF
      */
    virtual void set_state(bool state) = 0;

    /**
     * @brief Get the current LED state
     * @return true if LED is ON, false if OFF
     */
    virtual bool get_state() const = 0;
};

#endif // LED_HPP
