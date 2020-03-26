#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

#include "../customLibs/CustomTime.h"
#include "../stabilization/hardware/RadioReception.h"
#include "../stabilization/Stabilization.h"
#include "../stateMachine/states/IState.h"

class StateMachine {
  private:
    // Buzzer for lost model alarm
    const int BUZZER_PIN = 7;
    const int delayThresholdSec = 5; // (s)
    CustomTime elapsedTime;
    CustomTime timeBuzzer;
    IState *currentState;

  public:
    bool throttleWasHigh = true;
    void Init();

    // Activate buzzer after x minutes of power idle
    void ActivateBuzzer(int _duration);

    // Auto Disarm when throttle is idle since a long period
    bool IsSafetyStateNeeded();

    void SetState(IState *_newState) {
        currentState = _newState;
    }

    void Run(const float _loopTimeSec) {
        currentState->Run(this, _loopTimeSec);
    }

  private:
    void Print();
};

#endif // STATEMACHINE_H_