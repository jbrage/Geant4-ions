#include "SteppingAction.hh"
#include "RunAction.hh"

#include <G4Step.hh>
#include <G4Electron.hh>

SteppingAction::SteppingAction(RunAction* runAction)
    : fRunAction(runAction)
{
}

void SteppingAction::UserSteppingAction(const G4Step* aStep)
{

    fRunAction->AddSecondary(aStep);

}
