
#ifndef ANIMATION_HPP
#define ANIMATION_HPP

struct Frame final {
    //! Frame index.
    int index = 0;

    //! Time interval in seconds between two adjacent frames.
    double timeIntervalInSeconds = 1.0 / 60.0;

    //! Constructs Frame instance with 1/60 seconds time interval.
    Frame();

    //! Constructs Frame instance with given time interval.
    Frame(int newIndex, double newTimeIntervalInSeconds);

    //! Returns the elapsed time in seconds.
    double timeInSeconds() const;

    //! Advances single frame.
    void advance();

    //! Advances multiple frames.
    //! param delta Number of frames to advance.
    void advance(int delta);

    //! Advances single frame (prefix).
    Frame& operator++();

    //! Advances single frame (postfix).
    Frame operator++(int);
};

class Animation {
 public:
    Animation();

    virtual ~Animation();

    //!
    //! brief Updates animation state for given frame.
    //!
    //! This function updates animation state by calling Animation::onUpdate
    //! function.
    //!
    void update(const Frame& frame);

 protected:
    //!
    //!  The implementation of this function should update the animation
    //!     state for given Frame instance frame.
    //!
    //! This function is called from Animation::update when state of this class
    //! instance needs to be updated. Thus, the inherited class should overrride
    //! this function and implement its logic for updating the animation state.
    //!
    virtual void onUpdate(const Frame& frame) = 0;
};

#endif