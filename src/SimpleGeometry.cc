#include "SimpleGeometry.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Orb.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VSensitiveDetector.hh"
#include "G4SDManager.hh"
#include "SimpleDetector.hh"

using namespace CLHEP;

SimpleGeometry::SimpleGeometry()
: G4VUserDetectorConstruction()
{ }

SimpleGeometry::~SimpleGeometry()
{ }

G4VPhysicalVolume* SimpleGeometry::Construct()
{  
  G4bool checkOverlaps = true;

  G4NistManager* nist = G4NistManager::Instance();
  G4Material* Concrete = nist->FindOrBuildMaterial("G4_CONCRETE");
  G4Material* Air = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* Steel = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");
  G4Material* PARAFFIN = nist->FindOrBuildMaterial("G4_PARAFFIN");


  G4double density = 4.100*g/cm3;
  G4Material* DoorMaterial = new G4Material("DoorMaterial", density, 2);
  DoorMaterial->AddMaterial( PARAFFIN,12*perCent);
  DoorMaterial->AddMaterial(Steel,88*perCent);

  // World
  G4Box* world = new G4Box("World", 1100*cm, 750*cm, 800*cm);
  G4LogicalVolume* worldlv =                         
    new G4LogicalVolume(world, Air, "World");  
  
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0, G4ThreeVector(),
                      worldlv, "World",
                      0, false, 0, checkOverlaps);

  // Concrete walls
  G4Box* walls = new G4Box("ConWalls",931.5*cm,  467.5*cm, 451.5*cm);
  G4LogicalVolume* wallslv =                         
    new G4LogicalVolume(walls, Concrete, "ConWalls");  

  new G4PVPlacement(0, G4ThreeVector(0.,0.,0.),
                      wallslv, "ConWalls",
                      worldlv, false, 0, checkOverlaps);


   // Air 
  G4Box* airroom = new G4Box("AirRoom",731.5*cm, 352.5*cm, 271.5*cm);
  G4LogicalVolume* airlv =                         
    new G4LogicalVolume(airroom, Air, "AirRoom");  

  new G4PVPlacement(0, G4ThreeVector(0.,49.*cm,20.*cm),
                      airlv, "AirRoom",
                      wallslv, false, 0, checkOverlaps);

     // Concrete wall 
  G4Box* wall = new G4Box("ConWall", 50*cm, 133.5*cm, 221.5*cm);
  G4LogicalVolume* walllv =                         
    new G4LogicalVolume(wall, Concrete, "ConWall");  

  new G4PVPlacement(0, G4ThreeVector(50.*cm,-216*cm,50.*cm),
                      walllv, "ConWall",
                      airlv, false, 0, checkOverlaps); 
   
  // Door1
  G4Box* door1 = new G4Box("SteelDoor1",100*cm, 133.5*cm, 59.5*cm);
  G4LogicalVolume* door1lv =                         
    new G4LogicalVolume(door1, DoorMaterial, "SteelDoor1");  

  new G4PVPlacement(0, G4ThreeVector(-831.5*cm,-167*cm,31*cm),
                      door1lv, "SteelDoor1",
                      wallslv, false, 0, checkOverlaps);
  G4Box* door1_1 = new G4Box("SteelDoor1_1",35*cm, 133.5*cm, 59.5*cm);
  G4LogicalVolume* door1_1lv =                         
    new G4LogicalVolume(door1_1, DoorMaterial, "SteelDoor1_1");  

  new G4PVPlacement(0, G4ThreeVector(-696.5*cm,-216*cm,11*cm),
                      door1_1lv, "SteelDoor1_1",
                      airlv, false, 0, checkOverlaps);
  G4Box* door1_2 = new G4Box("SteelDoor1_2",35*cm, 133.5*cm, 59.5*cm);
  G4LogicalVolume* door1_2lv =                         
    new G4LogicalVolume(door1_2, DoorMaterial, "SteelDoor1_2");  

  new G4PVPlacement(0, G4ThreeVector(-966.5*cm,-167*cm,31*cm),
                      door1_2lv, "SteelDoor1_2",
                      worldlv, false, 0, checkOverlaps);

  // Door2
  G4Box* door2 = new G4Box("SteelDoor2",59.5*cm, 133.5*cm, 100*cm);
  G4LogicalVolume* door2lv =                         
    new G4LogicalVolume(door2, DoorMaterial, "SteelDoor2");  

  new G4PVPlacement(0, G4ThreeVector(-485.5*cm,-167*cm,-351.5*cm),
                      door2lv, "SteelDoor2",
                      wallslv, false, 0, checkOverlaps);
  
  G4Box* door2_1 = new G4Box("SteelDoor2_1",59.5*cm, 133.5*cm, 35*cm);
  G4LogicalVolume* door2_1lv =                         
    new G4LogicalVolume(door2_1, DoorMaterial, "SteelDoor2_1");  

  new G4PVPlacement(0, G4ThreeVector(-485.5*cm,-216*cm,-236.5*cm),
                      door2_1lv, "SteelDoor2_1",
                      airlv, false, 0, checkOverlaps);

  G4Box* door2_2 = new G4Box("SteelDoor2_2",59.5*cm, 133*cm, 35*cm);
  G4LogicalVolume* door2_2lv =                         
    new G4LogicalVolume(door2_2, DoorMaterial, "SteelDoor2_2");  

  new G4PVPlacement(0, G4ThreeVector(-485.5*cm,-167*cm,-486.5*cm),
                      door2_2lv, "SteelDoor2_2",
                      worldlv, false, 0, checkOverlaps);

    // Door3
  G4Box* door3 = new G4Box("Door3",26*cm, 169.5*cm, 80*cm);
  G4LogicalVolume* door3lv =                         
    new G4LogicalVolume(door3, Air, "Door3");  

  new G4PVPlacement(0, G4ThreeVector(-500*cm,133.25*cm, 371.5*cm),
                      door3lv, "Door3",
                      wallslv, false, 0, checkOverlaps);

      // Door4
  G4Box* door4 = new G4Box("Door4",58.2*cm, 110.*cm, 80*cm);
  G4LogicalVolume* door4lv =                         
    new G4LogicalVolume(door4, Air, "Door4");  

  new G4PVPlacement(0, G4ThreeVector(-623.3*cm,-190.5*cm, 371.5*cm),
                      door4lv, "Door4",
                      wallslv, false, 0, checkOverlaps);

  
  //Shaft
  G4Box* shaft1 = new G4Box("Shaft1",731.5*cm, 48.75*cm, 12.5*cm);
  G4LogicalVolume* shaft1lv =                         
    new G4LogicalVolume(shaft1, Concrete, "Shaft1");  

  new G4PVPlacement(0, G4ThreeVector(0.*cm,303.25*cm,259*cm),
                      shaft1lv, "Shaft1",
                      airlv, false, 0, checkOverlaps);

  G4Box* shaft2 = new G4Box("Shaft2",731.5*cm, 48.75*cm, 40.*cm);
  G4LogicalVolume* shaft2lv =                         
    new G4LogicalVolume(shaft2, Concrete, "Shaft2");  

  new G4PVPlacement(0, G4ThreeVector(0.*cm,303.25*cm,-231.5*cm),
                      shaft2lv, "Shaft2",
                      airlv, false, 0, checkOverlaps);

    // Labyrinth
    G4Box* labyrinth1  = new G4Box("Labyrinth1",45.*cm, 133.5*cm, 65.*cm);
  G4LogicalVolume* labyrinth1lv =                         
    new G4LogicalVolume(labyrinth1, Air, "Labyrinth1");  

  new G4PVPlacement(0, G4ThreeVector(776.5*cm, -167*cm, -86.5*cm),
                      labyrinth1lv, "Labyrinth1",
                      wallslv, false, 0, checkOverlaps);

  G4Box* labyrinth2  = new G4Box("Labyrinth2", 80.*cm, 133.5*cm, 51*cm);
  G4LogicalVolume* labyrinth2lv =                         
    new G4LogicalVolume(labyrinth2, Air, "Labyrinth2");  

  new G4PVPlacement(0, G4ThreeVector(851.5*cm, -167*cm, 29.5*cm),
                      labyrinth2lv, "Labyrinth2",
                      wallslv, false, 0, checkOverlaps);
  
   // Detectors 
     G4Orb* detector = new G4Orb("Detector",5.*cm);
        G4LogicalVolume*Detectorlv =                         
      new G4LogicalVolume(detector, Air, "Detector");

   for(int j = 0; j < 13;j++){
   for(int i = 0; i < 8;i++) {new G4PVPlacement(0, G4ThreeVector((-731.5+70.+5.+50.*j)*cm, (-352.5+62.5)*cm, (271.5-5.-70.-i*50.)*cm),
                     Detectorlv, "Detector",
  						airlv, false, i+j*10, checkOverlaps);
	   };
  };


  for(int j = 0; j < 13;j++){
    for(int i = 0; i < 8;i++) {new G4PVPlacement(0, G4ThreeVector((121.5+50.*j)*cm, (-352.5+62.5)*cm, (271.5-5.-70.-i*50.)*cm),
                     Detectorlv, "Detector",
						airlv, false,130+i+j*10, checkOverlaps);
	   };
  };

     for(int i = 0; i < 29;i++) {new G4PVPlacement(0, G4ThreeVector((-705.+50.*i)*cm, (-352.5+49+62.5)*cm, (451.5+10.)*cm),
                     Detectorlv, "Detector",
						worldlv, false,260+i, checkOverlaps);
	   };

     for(int i = 0; i < 29;i++) {new G4PVPlacement(0, G4ThreeVector((-705.+50.*i)*cm, (-352.5+49.+62.5)*cm, (-451.5-80.)*cm),
                     Detectorlv, "Detector",
						worldlv, false,290+i, checkOverlaps);
	   };

     for(int i = 0; i < 8;i++) {new G4PVPlacement(0, G4ThreeVector((-931.5-80.)*cm, (-352.5+49.+62.5)*cm, (271.5+20-5-70-i*50.)*cm),
                     Detectorlv, "Detector",
  						worldlv, false, 320+i, checkOverlaps);
	   };
     for(int i = 0; i < 8;i++) {new G4PVPlacement(0, G4ThreeVector((931.5+10.)*cm, (-352.5+49.+62.5)*cm, (271.5+20-5-70-i*50.)*cm),
                     Detectorlv, "Detector",
  						worldlv, false, 330+i, checkOverlaps);
     };
	      
   for(int j = 0; j < 13;j++){
   for(int i = 0; i < 8;i++) {new G4PVPlacement(0, G4ThreeVector((-731.5+70.+5.+50.*j)*cm, (-352.5+62.5+267.)*cm, (271.5-5.-70.-i*50.)*cm),
                     Detectorlv, "Detector",
  						airlv, false,340+i+j*10, checkOverlaps);
	   };
   };

   for(int j = 0; j < 29;j++){
   for(int i = 0; i < 8;i++) {new G4PVPlacement(0, G4ThreeVector((-731.5+70.+5.+50.*j)*cm, (467.5+62.5+5.)*cm, (271.5-5.-70.-i*50.)*cm),
                     Detectorlv, "Detector",
  						worldlv, false,470+i+j*10, checkOverlaps);
	   };
   };

   for(int j = 0; j < 29;j++){
   for(int i = 0; i < 8;i++) {new G4PVPlacement(0, G4ThreeVector((-731.5+70.+5.+50.*j)*cm, (-467.5-220.)*cm, (271.5-5.-70.-i*50.)*cm),
                     Detectorlv, "Detector",
  						worldlv, false,760+i+j*10, checkOverlaps);
	   };
   };

   
  return physWorld;
}


void SimpleGeometry::ConstructSDandField()
{
  // Sensitive detectors
  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  G4VSensitiveDetector* sd = new SimpleDetector("simple_detector");
  SetSensitiveDetector("Detector", sd, true);
  SDman->AddNewDetector(sd);
}
