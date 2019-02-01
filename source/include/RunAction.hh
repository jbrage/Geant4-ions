#ifndef RUNACTION_HH
#define RUNACTION_HH

#include <G4UserRunAction.hh>
#include <G4Run.hh>
#include <G4ParticleDefinition.hh>
#include <G4Parameter.hh>
#include <G4ParameterManager.hh>
#include <G4Step.hh>

class RunAction : public G4UserRunAction
{
public:
  //! constructor
  RunAction();

  //! destructor
  ~RunAction();

  //! Main interface
  void BeginOfRunAction(const G4Run*);
  void EndOfRunAction(const G4Run*);

  void AddSecondary(const G4Step*);
  // void CerenkovCount();

private:
  // G4Parameter<G4int> counter;

};

#endif
