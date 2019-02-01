#include <vector>

// Select a proper single-/multithreaded run manager
#ifdef G4MULTITHREADED
    #include <G4MTRunManager.hh>
    using RunManager = G4MTRunManager;
#else
    #include <G4RunManager.hh>
    using RunManager = G4RunManager;
#endif

#ifdef G4VIS_USE
    #include <G4VisExecutive.hh>
#endif

#ifdef G4UI_USE
    #include <G4UIExecutive.hh>
#endif

#include <G4String.hh>
#include <G4UImanager.hh>

#include "ActionInitialization.hh"
#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "G4PhysListFactory.hh"
#include "G4VUserPhysicsList.hh"
#include "QGSP_BERT.hh"
#include "FTFP_BERT.hh"
#include "QGSP_BIC.hh"
// #include "QGSP_BIC_EMY.hh"

#include "G4ScoringManager.hh"

using namespace std;

/* Main function that enables to:
 * - run any number of macros (put them as command-line arguments)
 * - start interactive UI mode (no arguments or "-i")
 */
int main(int argc, char** argv)
{
    std::cout << "Application starting..." << std::endl;

    vector<G4String> macros;
    bool interactive = false;

    // Parse command line arguments
    if  (argc == 1)
    {
        interactive = true;
    }
    else
    {
        for (int i = 1; i < argc; i++)
        {
            G4String arg = argv[i];
            if (arg == "-i" || arg == "--interactive")
            {
                interactive = true;
                continue;
            }
            else
            {
                macros.push_back(arg);
            }
        }
    }

    auto runManager = new RunManager();

    #ifdef G4VIS_USE
        G4VisManager* visManager = new G4VisExecutive("quiet");
        visManager->SetVerboseLevel(0);    // Default, you can always override this using macro commands
        visManager->Initialize();
    #endif


    G4PhysListFactory *physListFactory = new G4PhysListFactory();
    G4VUserPhysicsList *physicsList = physListFactory->GetReferencePhysList("QGSP_BERT");
    // G4VUserPhysicsList *physicsList = physListFactory->GetReferencePhysList("FTFP_BERT");

    runManager->SetUserInitialization(new PhysicsList()); // must be placed after the one above. Overriding?
    runManager->SetUserInitialization(physicsList);


    runManager->SetUserInitialization(new DetectorConstruction());
    runManager->SetUserInitialization(new ActionInitialization());

    #ifdef G4UI_USE
        G4UIExecutive* ui;
        if (interactive)
        {
            ui = new G4UIExecutive(argc, argv);
        }
    #endif

    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    G4ScoringManager::GetScoringManager();

    for (auto macro : macros)
    {
        G4String command = "/control/execute ";
        UImanager->ApplyCommand(command + macro);
    }

    #ifdef G4UI_USE
        if (interactive)
        {
            UImanager->ApplyCommand("/control/execute macros/ui.mac");
            ui->SessionStart();
            delete ui;
        }
    #endif

    delete runManager;

    // G4AnalysisManager* man = G4AnalysisManager::Instance();
    // man->CloseFile();

    std::cout << "Application successfully ended.\nBye :-)" << std::endl;

    return 0;
}
