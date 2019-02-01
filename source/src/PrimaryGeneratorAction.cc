#include "PrimaryGeneratorAction.hh"

#include <G4ParticleTable.hh>
#include <G4Event.hh>
#include <G4SystemOfUnits.hh>
#include <G4ParticleGun.hh>
#include <Randomize.hh>

#include <G4GeneralParticleSource.hh>

using namespace std;

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
    fGPS = new G4GeneralParticleSource();
    //
    // G4ParticleDefinition* electron = G4ParticleTable::GetParticleTable()->FindParticle("e-");
    // // Alternative: electron = G4Electron::ElectronDefinition();
    //
    // /* fGun->SetParticleDefinition(electron);
    // fGun->SetParticleEnergy(100. * MeV);
    // fGun->SetParticleMomentumDirection(G4ThreeVector(1., 0., 0.));  // along y
    // */
    // fGPS->SetParticleDefinition(electron);
    // fGPS->GetCurrentSource()->GetEneDist()->SetMonoEnergy(100 * MeV);
    // fGPS->GetCurrentSource()->GetAngDist()->SetParticleMomentumDirection(G4ThreeVector(1., 0., 0.));
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fGPS;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    // Task 2a.2: Include the position randomization
    /* G4double x0 = -10 * cm, y0  = 0 * cm, z0  = -4 * cm;
    G4double dx0 = 1 * cm, dy0 = 1 * cm, dz0 = 1 * cm;
    x0 += dx0 * (G4UniformRand() - 0.5);
    y0 += dy0 * (G4UniformRand() - 0.5);
    z0 += dz0 * (G4UniformRand() - 0.5);

    fGun->SetParticlePosition({x0, y0, z0});
    */

    fGPS->GeneratePrimaryVertex(anEvent);
}
