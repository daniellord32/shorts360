Copyright (c) 2006 Microsoft Corporation.  All rights reserved.

This is a sample of several Flight Simulator X code gauges.  You can compile the sample and use the gauges in the game.

The SDKSample.VCPROJ is a Microsoft Visual Studio 2005 project file set up to build the gauge "SDK.dll" using the .cpp source files that are part of this sample.  This project file can be opened with either Microsoft Visual Studio 2005 or Microsoft Visual Studio Express.  Microsoft Visual Studio Express is a free product available for download at http://msdn.microsoft.com/vstudio/express/visualc/.  

Instructions:

- Open the SDKSample.vcproj Visual Studio Project file
- Examine the cpp source files, the .h header files, and the makefile.  Reference the SDK documentation to understand how these files are written
- Select Build->Build SDKSample, and observe the Output window results
- You should now have a file called SDK.dll in the directory from which you are running the VCProj file.
- Copy the SDK.dll file to the "\Program Files\Microsoft Games\Micorsoft Flight Simulator X\gauges" directory.  (Note that this directory may be different if you didn't not install Flight Simulator to its default installation location). 
- Now edit the aircraft.cfg for an aircraft (we recommend the Cessna 172) to add a new variation which will use the SDK panel.  Open FSX\SimObjects\Airplanes\C172\aircraft.cfg and add the following lines after the [fltsim.5] section:

[fltsim.6]
title=Cessna Skyhawk 172SP SDK panel
sim=Cessna172SP
model=
panel=SDK
sound=
texture=
kb_checklists=Cessna172SP_check
kb_reference=Cessna172SP_ref
atc_id=N760PL
ui_manufacturer="Cessna"
ui_type="C172SP Skyhawk SDK"
ui_variation=" SDK"
ui_typerole="Single Engine Prop"
ui_createdby="Microsoft Corporation"

- Create a new directory called "Panel.SDK" in the FSX\SimObjects\Airplanes\C172 directory.  Copy the panel.cfg and Cessna_panel_1024.bmp to this directory.
- Run FSX, select "Free Flight", "Change aircraft" and select the  .

You'll notice that the gauges created with this SDK are of lower visual quality than those shipped with the product.  This is due to the lower resolution textures in the \res directory of this sample.  Higher quality images can be used for any gauges you create yourself.

We hope you find this SDK sample useful.  Keep checking back to http://www.fsinsider.com for the latest information on building add-ons for Microsoft Flight Simulator!

Thanks,

The Flight Simulator Team
