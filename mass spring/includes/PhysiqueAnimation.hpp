
#ifndef PHYSIQUEANIMATION_HPP
#define PHYSIQUEANIMATION_HPP

#include "Animation.hpp"
#include <cmath>
#include <limits>

class PhysicsAnimation : public Animation {
 public:
    //! Default constructor.
    PhysicsAnimation();

    //! Destructor.
    virtual ~PhysicsAnimation();


    bool isUsingFixedSubTimeSteps() const;
    void setIsUsingFixedSubTimeSteps(bool isUsing);

    unsigned int numberOfFixedSubTimeSteps() const;
    void setNumberOfFixedSubTimeSteps(unsigned int numberOfSteps);

    //! Advances a single frame.
    void advanceSingleFrame();

    Frame currentFrame() const;

    void setCurrentFrame(const Frame& frame);

    double currentTimeInSeconds() const;

 protected:
    
    virtual void onAdvanceTimeStep(double timeIntervalInSeconds) = 0;

    virtual unsigned int numberOfSubTimeSteps(
        double timeIntervalInSeconds) const;

    virtual void onInitialize();

 private:
    Frame _currentFrame;
    bool _isUsingFixedSubTimeSteps = true;
    unsigned int _numberOfFixedSubTimeSteps = 1;
    double _currentTime = 0.0;

    void onUpdate(const Frame& frame) final;

    void advanceTimeStep(double timeIntervalInSeconds);

    void initialize();
};

constexpr double kEpsilonD = std::numeric_limits<double>::epsilon();

#endif