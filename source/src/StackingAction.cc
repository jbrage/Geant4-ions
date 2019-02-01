#include "StackingAction.hh"
#include "RunAction.hh"

#include <G4SystemOfUnits.hh>

#include "G4Gamma.hh"
#include "G4Neutron.hh"
#include "G4Electron.hh"
#include "G4Proton.hh"

#include "G4Cerenkov.hh"

#include <sstream>

using namespace std;

StackingAction::StackingAction(RunAction* aRunAction) :
  G4UserStackingAction(),fRunAction(aRunAction)
{;}

G4ClassificationOfNewTrack StackingAction::ClassifyNewTrack (const G4Track*
 aTrack)
{

  return G4UserStackingAction::ClassifyNewTrack(aTrack);
}
