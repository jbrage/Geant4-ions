#include "RunAction.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4ParameterManager.hh"
#include "G4SystemOfUnits.hh"

#include "Analysis.hh"

#include "G4Electron.hh"
#include "G4Neutron.hh"
#include "G4Gamma.hh"
#include <G4Step.hh>
#include <G4Track.hh>

using namespace std;

G4int MAX_Z = 9; // score up to atomic number z = MAX_Z - 1
G4int length_cm = 10; // depth of the ionization curve

RunAction::RunAction() :
  G4UserRunAction()
  // ,
  // counter("fcounter",0.)
{
  // G4ParameterManager* parameterManager = G4ParameterManager::Instance();
  // parameterManager->RegisterParameter(counter);


  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetVerboseLevel(0);
  // analysisManager->SetFirstNtupleId(0);
  analysisManager->SetFirstHistoId(0);

  G4int nBins = 200;

  analysisManager->CreateH1("total_dose", "dose", nBins, 0, length_cm);

  G4String E_name, f_name;
  for (G4int i=1; i<MAX_Z; i++){
    ostringstream dose, fluence;
    dose << i << "_z_dose";
    E_name = dose.str();
    analysisManager->CreateH1(E_name, "energy_deposition", nBins, 0, length_cm);

    fluence << i << "_z_fluence";
    f_name = fluence.str();
    analysisManager->CreateH1(f_name, "track_length", nBins, 0, length_cm);
  }


  // CreateH2(const G4String& name, const G4String& title,
  //                  G4int nxbins, G4double xmin, G4double xmax,
  //                  G4int nybins, G4double ymin, G4double ymax,
  // analysisManager->CreateH2("cherenkov","2Dhist",
  //                           nBins, 0., 10.,
  //                           nBins, 0., 10.);

  analysisManager->OpenFile("histograms/");
}


void RunAction::BeginOfRunAction(const G4Run*)
{
  G4ParameterManager* parameterManager = G4ParameterManager::Instance();
  parameterManager->Reset();
}


void RunAction::EndOfRunAction(const G4Run* run)
{
  G4int nofEvents = run->GetNumberOfEvent();

  //do nothing, if no events were processed
  if (nofEvents == 0) return;

  // Merge parameters
  G4ParameterManager* parameterManager = G4ParameterManager::Instance();
  parameterManager->Merge();
  if (IsMaster())
  {
    cout << "\n--------------------End of Global Run-----------------------" << endl;

  }
}

RunAction::~RunAction()
{
    G4AnalysisManager* man = G4AnalysisManager::Instance();
    man->Write();
}


void RunAction::AddSecondary(const G4Step* aStep)
{
    G4Track *aTrack = aStep->GetTrack();
    G4String pname = aTrack->GetDefinition()->GetParticleName();

    // charge of the particle
    G4int z = aTrack->GetDefinition()->GetPDGCharge();
    G4double energy_dep_keV = aStep->GetTotalEnergyDeposit() / keV;
    G4double x_cm = aTrack->GetPosition().x() / cm;
    G4double steplength_um = aStep->GetStepLength() / um;

    G4AnalysisManager* analysis = G4AnalysisManager::Instance();

    G4int dose_hist_ID, fluence_hist_ID;

    if (x_cm > 0 && x_cm <= length_cm){
        // fill all; total
        analysis->FillH1(0, x_cm, energy_dep_keV);

        if(z > 0 && z < MAX_Z){

            dose_hist_ID = 2*z - 1;
            fluence_hist_ID = 2*z;

            analysis->FillH1(dose_hist_ID, x_cm, energy_dep_keV);
            analysis->FillH1(fluence_hist_ID, x_cm, steplength_um);
        }
    }
}
