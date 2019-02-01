## Geant4: 200 MeV/u carbon ions in water

### Scoring
* the dose for primaries and secondaries for a given atomic number 
* the fluence-averaged LET or whatever quantity specified in the routine
* the max step length can be modified in the DetectorConstruction class
* Saves histograms to 
```
mkdir -p build/histograms
```

### Validation 
* the dose distributions for the ion fragments are identical to figure 2 in [1]

### References
[1] Gunzert-Marx, K., et al. _Secondary beam fragments produced by 200 MeV/u 12C ions in water and their dose contributions in carbon ion radiotherapy._ New journal of physics 10.7 (2008): 075003


