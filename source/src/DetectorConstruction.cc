#include "DetectorConstruction.hh"

#include <G4LogicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4NistManager.hh>
#include <G4SystemOfUnits.hh>
#include <G4VisAttributes.hh>
#include <G4Box.hh>
#include <G4Orb.hh>
#include <G4SDManager.hh>


#include "G4Material.hh"
#include "G4UserLimits.hh"


#include <sstream>

using namespace std;

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    G4NistManager* nist = G4NistManager::Instance();
    G4double worldSizeX = 1 * m;
    G4double worldSizeY = 1 * m;
    G4double worldSizeZ = 1 * m;


    // 1) Solid
    G4VSolid* worldBox = new G4Box("world", worldSizeX / 2, worldSizeY / 2, worldSizeZ / 2);

    // 2) Logical volume
    G4LogicalVolume* worldLog = new G4LogicalVolume(worldBox, nist->FindOrBuildMaterial("G4_AIR"), "world");
    G4VisAttributes* visAttr = new G4VisAttributes();
    visAttr->SetVisibility(false);
    worldLog->SetVisAttributes(visAttr);

    // 3) Physical volume
    G4VPhysicalVolume* worldPhys = new G4PVPlacement(nullptr, {}, worldLog, "world", nullptr, false, 0);

    G4Material * water = nist->FindOrBuildMaterial("G4_WATER");

    G4Box* waterTank_box = new G4Box("Tank", worldSizeX / 2.1, worldSizeY / 2.1, worldSizeZ / 2.1);

    G4LogicalVolume* waterTank_log
    = new G4LogicalVolume(waterTank_box,water,"Tank",0,0,0);

    // G4VPhysicalVolume* waterTank_phys=
                            new G4PVPlacement(0,
                                    G4ThreeVector(),
                                    waterTank_log,
                                    "Tank",
                                    worldLog,
                                    false,
                                    0);
    visAttr->SetVisibility(true);
    waterTank_log->SetVisAttributes(visAttr);

    // // STEP SIZE LIMIT
    // G4double maxStep = 0.5*mm;
    // G4UserLimits* fStepLimit = new G4UserLimits(maxStep);
    // fStepLimit->SetMaxAllowedStep(maxStep);
    // waterTank_log->SetUserLimits(fStepLimit);

    // The Construct() method has to return the final (physical) world volume:
    return worldPhys;
}
