#include "TeleopStateMachine.h"

TeleopStateMachine::TeleopStateMachine(frc::Joystick *joystick_, Barrel *barrel_, Shooter *shooter_)
{
    joystick = joystick_;
    barrel = barrel_;
    shooter = shooter_;

    current_state = States::STOP;
}

void TeleopStateMachine::UpdateButtons(){

    current_state = States::STOP_BARREL;

    if(joystick->GetRawButton(8)){
        current_state = States::SHOOT;
    }
    

    if(joystick->GetRawButton(5)){

        current_state = States::RUN;
    } 

    if(joystick->GetRawButton(6)){
        current_state = States::STOP;
    }

    if(joystick->GetRawButton(up_button)){
        current_state = States::UP;
    }

    if(joystick->GetRawButton(down_button)){
        current_state = States::DOWN;
    }

    if(joystick->GetRawButton(slow_button)){
        current_state = States::SLOW_BARREL;
    }

    frc::SmartDashboard::PutNumber("state" ,(int) current_state);
}

void TeleopStateMachine::StateMachine(){

    UpdateButtons();

    switch (current_state)
    {
    case States::INIT:
        barrel->current_state = Barrel::States::INIT;
        shooter->current_state = Shooter::States::INIT;
        break;
    
    case States::RUN:
        shooter->current_state = Shooter::States::GO;
        break;

    case States::STOP:
        shooter->current_state = Shooter::States::STOP;
        break;

    case States::SHOOT:
        shooter->current_state = Shooter::States::SHOOT;
        break;

    case States::UP:
        barrel->current_state = Barrel::States::UP;
        break;

    case States::DOWN:
        barrel->current_state = Barrel::States::DOWN;
        break;

    case States::STOP_BARREL:
        break;

    case States::EMERGENCY:
        shooter->current_state = Shooter::States::EMERGENCY;
        break;

    case States::SLOW_BARREL:
        barrel->current_state = Barrel::States::STOP;
        break;
        
    }

    barrel->StateMachine();
    shooter->StateMachine();

}