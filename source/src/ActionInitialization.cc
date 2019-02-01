#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "PhysicsList.hh"

#include "RunAction.hh"
#include "StackingAction.hh"
#include "SteppingAction.hh"

void ActionInitialization::Build() const
{
    SetUserAction(new PrimaryGeneratorAction());
    // SetUserAction(new PhysicsList());

    RunAction* theRunAction = new RunAction();
    SetUserAction(theRunAction);
    SetUserAction(new StackingAction(theRunAction));
    SetUserAction(new SteppingAction(theRunAction));

}

void ActionInitialization::BuildForMaster() const
{
  // By default, don't do anything. This applies only in MT mode:
  SetUserAction(new RunAction());
}
