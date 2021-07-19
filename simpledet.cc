#include "SimpleGeometry.hh"
#include "SimpleParticleSource.hh"
#include "SimpleRunAction.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4RunManager.hh"
#include "G4ProductionCuts.hh"
#include "G4UImanager.hh"
#include "Shielding.hh"

int main(int argc, char** argv)
{
 if (argc != 2 )
     {
           G4cout << "Usage: ./simpledet  RUN_NUMBER" << G4endl;
                 return 0;
     }
 long jobId = 0;
 if ( argc == 2)
      jobId = atol(argv[1]);

// Choose the Random engine
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
                                  
  // Construct the default run manager

  G4RunManager * runManager = new G4RunManager;

  // Set mandatory initialization classes

  // Detector construction
  runManager->SetUserInitialization(new SimpleGeometry());

  // Physics list
  runManager->SetUserInitialization(new Shielding);
    
  // Primary generator action
  runManager->SetUserAction(new SimpleParticleSource());

  runManager->SetUserAction(new SimpleRunAction);

  // Initialize G4 kernel
  runManager->Initialize();

  long rand[2];
  rand[0] = long(jobId*100000000 + 123456789);
  rand[1] = 123456789;
  const long* rand1 = rand;
  G4Random::setTheSeeds(rand1);

  G4UIExecutive* ui = new G4UIExecutive(argc, argv);

  G4UImanager::GetUIpointer()->ApplyCommand("/tracking/verbose 0");

//  G4VisManager* visManager = new G4VisExecutive;
//  visManager->Initialize();
  G4cout << "Start run "<< jobId << " 1e6 neutrons" << G4endl;

  // interactive mode
  G4UImanager::GetUIpointer()->ApplyCommand("/run/beamOn 10000000");
//  ui->SessionStart();
  G4cout << "End of run" << G4endl;

//  delete ui;
//  delete visManager;
  delete runManager;
  return 0;
}
