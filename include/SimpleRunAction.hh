#ifndef SimpleRunAction_h
#define SimpleRunAction_h 1

#include "G4UserRunAction.hh"

class G4Run;

class SimpleRunAction : public G4UserRunAction
{
public:
  SimpleRunAction();
  virtual ~SimpleRunAction();

  virtual void BeginOfRunAction(const G4Run*);
  virtual void   EndOfRunAction(const G4Run*);
};

#endif

