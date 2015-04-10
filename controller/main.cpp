#include "irrlicht.h"
#include <iostream>
#include <cstdio>
#include <vector>
#include "PositionDataStruct.hpp"
#include "ShipDataStruct.hpp"
#include "OtherShipDataStruct.hpp"
#include "Network.hpp"
#include "ControllerModel.hpp"
#include "GUI.hpp"

#include "../Lang.hpp"

// Irrlicht Namespaces
using namespace irr;

int main (int argc, char ** argv)
{

    IrrlichtDevice* device = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(800,600),32,false,false,false,0); //Fixme: Hardcoded size, depth and full screen
    video::IVideoDriver* driver = device->getVideoDriver();
    //scene::ISceneManager* smgr = device->getSceneManager();

    //load language
    Lang language("language.txt");

    //Classes:  Network and Controller share data with shared data structures (passed by ref). Controller then pushes data to the GUI
    //Network class
    Network network;
    //GUI class
    GUIMain guiMain(device, &language);
    //Main model
    ControllerModel controller(device, &guiMain);

    //Create data structures to hold own ship, other ship and buoy data
    irr::u64 timestamp = 0;
    ShipData ownShipData;
    std::vector<PositionData> buoysData;
    std::vector<OtherShipData> otherShipsData;

    while(device->run()) {

        driver->beginScene();

        //Read in data from network
        network.update(timestamp, ownShipData, otherShipsData, buoysData);

        //Update the internal model, and call the gui
        controller.update(timestamp, ownShipData, otherShipsData, buoysData);

        driver->endScene();
    }

    return(0);
}