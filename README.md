# SimCityMfc
This is a school project from long ago, created using Visual C++ 6.0 with MFC. At the time I was trying to do two things: learn C++ language, and Windows programming. I recall getting a good mark on the project as well as scoping it to make the deadline and having a really good time working on it. The program was made to look like SimCity for the SNES, a game I liked playing at the time.

**Running the release**

The release is a standalone binary. Since all the image elements are set up as resources, they are built into the binary.

**Usage environment**

This program was originally tested on Windows 98SE. The posted release has been tested on Windows 10. The program is for x86-compatible environments.

**Build**

Incredibly, the VC++ 6.0 DSW (project file) was auto-converted to a workable Visual Studio 2017 solution. I built it using Visual Studio 15.7.5. You can build the .sln and run the result in a modern environment.

![Example image](https://raw.githubusercontent.com/clandrew/SimCityMfc/master/Images/SimCity.gif "Example image")

**How to Play**

The icons on the left hand side are your toolbar to select different building options. 

![Bulldozer](https://raw.githubusercontent.com/clandrew/SimCityMfc/master/RES/_1.bmp "Bulldozer") The bulldozer allows you to demolish anything you've constructed. Parks, roads, buidings, anything. A building is demolished when its center is run over with the bulldozer.

![Road](https://raw.githubusercontent.com/clandrew/SimCityMfc/master/RES/_2.bmp "Road") Roads help the development of commercial zones, and raise land value slightly. You can build powerlines on top of roads. 

![Rail](https://raw.githubusercontent.com/clandrew/SimCityMfc/master/RES/_3.bmp "Rail") Rails increase development of commercial zones even more than roads, but they're a bit more expensive.

![Powerlines](https://raw.githubusercontent.com/clandrew/SimCityMfc/master/RES/_4.bmp "Powerlines") All buildings need power! A zone is considered powered if it has a connection to a power plant, either directly or through another powered zone. A zone without power has a lightning bolt icon in the middle.

![Park](https://raw.githubusercontent.com/clandrew/SimCityMfc/master/RES/_5.bmp "Park") Parks are a great way to increase land value. They look nice, too.

![Residential Zone](https://raw.githubusercontent.com/clandrew/SimCityMfc/master/RES/_6.bmp "Residential Zone") Residential zones are areas where your citizens can move in and live. The development of residential zones is what directly causes your population to increase.

![Commercial Zone](https://raw.githubusercontent.com/clandrew/SimCityMfc/master/RES/_7.bmp "Commercial Zone") Commercial zones are places for your citizens to work. 

![Industrial Zone](https://raw.githubusercontent.com/clandrew/SimCityMfc/master/RES/_8.bmp "Industrial Zone") Industrial zones also provide places to work, but they create pollution.

![Police Station](https://raw.githubusercontent.com/clandrew/SimCityMfc/master/RES/_9.bmp "Police Station") Since the full functionality of SimCity wasn't implemented for this project, police stations simply enhance the development of commercial zones.

![Fire Station](https://raw.githubusercontent.com/clandrew/SimCityMfc/master/RES/_10.bmp "Fire Station") Since the full functionality of SimCity wasn't implemented for this project, fire stations simply enhance the development of commercial zones.

![Stadium](https://raw.githubusercontent.com/clandrew/SimCityMfc/master/RES/_11.bmp "Stadium") People really like living near a stadium; it is an expensive construction though.

![Seaport](https://raw.githubusercontent.com/clandrew/SimCityMfc/master/RES/_12.bmp "Seaport") A seaport increases nearby land value. Like in SimCity, it doesn't have to be built on water!

![Coal Power Plant](https://raw.githubusercontent.com/clandrew/SimCityMfc/master/RES/_13.bmp "Coal Power Plant") Coal is the cheaper of the two power plants, but beware-- it creates pollution.

![Nuclear Power Plant](https://raw.githubusercontent.com/clandrew/SimCityMfc/master/RES/_14.bmp "Nuclear Power Plant") A nuclear power plant is the more expensive of the two power plants, but doesn't raise pollution.

![Airport](https://raw.githubusercontent.com/clandrew/SimCityMfc/master/RES/_15.bmp "Airport") Citizens will appreciate having an airport-- just know that it is expensive and causes pollution.

It's good to start with the three basic zoning types, residential, commercial and industrial. And, don't forget to supply them with power! Near the bottom are two types of power plants- Coal, and Nuclear. While the coal power plant is cheaper, watch out! It increases nearby areas' pollution which can decrease land value. 

As time goes on, you will collect tax revenue with which to build more and expand the city however you see fit. Use the power responsibly :)
