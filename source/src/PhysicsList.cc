#include "PhysicsList.hh"

#include <G4EmStandardPhysics.hh>
#include <G4EmStandardPhysics_option4.hh>
#include <G4DecayPhysics.hh>
#include "G4RadioactiveDecayPhysics.hh"
#include <G4ProductionCutsTable.hh>
#include <G4SystemOfUnits.hh>


#include <G4EmLivermorePhysics.hh>

#include <G4EmExtraPhysics.hh>
#include <G4HadronPhysicsFTFP_BERT.hh>
#include <G4HadronElasticPhysics.hh>

#include "G4OpticalPhysics.hh"
#include <QGSP_BIC_HP.hh>
#include <QGSP_BERT_HP.hh>
#include "G4HadronPhysicsQGSP_BIC.hh"
#include "G4HadronPhysicsQGSP_BIC_HP.hh"
#include "FTFP_BERT_HP.hh"


#include "G4PhysListFactory.hh"
#include "QGSP_BERT.hh"

#include "G4VUserPhysicsList.hh"
#include "G4StepLimiterPhysics.hh"


PhysicsList::PhysicsList()
{

    G4int verbose=0;

    // Standard EM physics
    // RegisterPhysics(new G4EmStandardPhysics(verbose));
    RegisterPhysics(new G4EmStandardPhysics_option4(verbose));

    RegisterPhysics(new G4StepLimiterPhysics());

    // Default Decay Physics
    RegisterPhysics(new G4DecayPhysics(verbose));
    RegisterPhysics(new G4RadioactiveDecayPhysics());
    //
    // RegisterPhysics(new QGSP_BERT_HP());
    RegisterPhysics(new G4HadronElasticPhysics());
    RegisterPhysics(new G4HadronPhysicsQGSP_BIC(verbose));

}


void PhysicsList::SetCuts()
{

    G4VUserPhysicsList::SetCuts();
    // G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(100*eV,100.*GeV);

    // In addition, dump the full list of cuts for the materials used in
    // the setup
    // DumpCutValuesTable();
}
