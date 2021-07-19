#include "SimpleRunAction.hh"
#include "G4Run.hh"

#include "SimpleAnalysis.hh"

SimpleRunAction::SimpleRunAction() : G4UserRunAction()
{

auto analysisManager = G4AnalysisManager::Instance();
 analysisManager->CreateNtuple("NTuple", "Example simple tree");
 analysisManager->CreateNtupleIColumn("Detecor");
 analysisManager->CreateNtupleDColumn("Energy");
 analysisManager->CreateNtupleIColumn("PDG");
 analysisManager->FinishNtuple();

  
}

SimpleRunAction::~SimpleRunAction()
{}

void SimpleRunAction::BeginOfRunAction(const G4Run* aRun)
{ 
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->OpenFile("run.csv");

  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;
}

void SimpleRunAction::EndOfRunAction(const G4Run*)
{
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();
}
