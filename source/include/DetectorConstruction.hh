#ifndef DETECTOR_CONSTRUCTION_HH
#define DETECTOR_CONSTRUCTION_HH

#include <G4VUserDetectorConstruction.hh>

class G4LogicalVolume;

/**
  * Obligatory class responsible for geometry - volumes, materials, fields, etc.
  *
  * You will work mainly with this header file (.hh) and its associated source file (.cc).
  */
class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
    // Main method that has to be overridden in all detectors
    G4VPhysicalVolume* Construct() override;

};

#endif
