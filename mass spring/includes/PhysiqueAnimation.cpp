#include "PhysiqueAnimation.hpp"

PhysicsAnimation::PhysicsAnimation() {
    _currentFrame.index = -1;
}

PhysicsAnimation::~PhysicsAnimation() {
}

bool PhysicsAnimation::isUsingFixedSubTimeSteps() const {
    return (_isUsingFixedSubTimeSteps);
}

void PhysicsAnimation::setIsUsingFixedSubTimeSteps(bool isUsing) {
    _isUsingFixedSubTimeSteps = isUsing;
}

unsigned int PhysicsAnimation::numberOfFixedSubTimeSteps() const {
    return (_numberOfFixedSubTimeSteps);
}

void PhysicsAnimation::setNumberOfFixedSubTimeSteps(unsigned int numberOfSteps) {
    _numberOfFixedSubTimeSteps = numberOfSteps;
}

void PhysicsAnimation::advanceSingleFrame() {
    Frame f = _currentFrame;
    update(++f);
}

Frame PhysicsAnimation::currentFrame() const {
    return (_currentFrame);
}

void PhysicsAnimation::setCurrentFrame(const Frame& frame) {
    _currentFrame = frame;
}

double PhysicsAnimation::currentTimeInSeconds() const {
    return (_currentTime);
}

unsigned int PhysicsAnimation::numberOfSubTimeSteps(double timeInterval) const {
    (void)timeInterval;
    return (_numberOfFixedSubTimeSteps);
}

void PhysicsAnimation::onUpdate(const Frame& frame) {
    if (frame.index > _currentFrame.index) {
        if (_currentFrame.index < 0) {
            initialize();
        }

        int numberOfFrames = frame.index - _currentFrame.index;

        for (int i = 0; i < numberOfFrames; ++i) {
            advanceTimeStep(frame.timeIntervalInSeconds);
        }

        _currentFrame = frame;
    }
}

void PhysicsAnimation::advanceTimeStep(double timeIntervalInSeconds) {
    _currentTime = _currentFrame.timeInSeconds();

    if (_isUsingFixedSubTimeSteps) {
        const double actualTimeInterval = timeIntervalInSeconds / static_cast<double>(_numberOfFixedSubTimeSteps);
    
        for (unsigned int i = 0; i < _numberOfFixedSubTimeSteps; ++i) {
            onAdvanceTimeStep(actualTimeInterval);

            _currentTime += actualTimeInterval;
        }
    } else {
        double remainingTime = timeIntervalInSeconds;
        while (remainingTime > kEpsilonD) {
            unsigned int numSteps = numberOfSubTimeSteps(remainingTime);
            double actualTimeInterval = remainingTime / static_cast<double>(numSteps);

            onAdvanceTimeStep(actualTimeInterval);

            remainingTime -= actualTimeInterval;
            _currentTime += actualTimeInterval; 
        }
    }
}

void PhysicsAnimation::initialize() { 
    onInitialize();
}

void PhysicsAnimation::onInitialize() {
    // Do nothing
}