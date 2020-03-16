# Angels High
### Weapons Free
A sim-cade style combat flight simulator built in C++ with Unreal Engine 4, which has <a href="#Features">many features</a>, including realistic and intuitive aircraft controls and physics, stunning graphics, and engaging first and third person views.

You can play the game by downloading [AngelsHigh-Game](https://github.com/flyscript/Angels-High/blob/master/AngelsHigh-Game) and launching the .exe

This game can be played in Virtual Reality from within the UE4 editor for maximum immersion!

This game was built in Unreal Engine 4 with C++, and you can open it in-engine by downloading [AngelsHigh-Source](https://github.com/flyscript/Angels-High/blob/master/AngelsHigh-Source/) and opening the .uproject. This will prompt you to select a build of Unreal with which to open it. The game will then open after Unreal has built its requisit project files.

Some blueprints were used for constructing child class's component transforms and physical layouts.

Not for commercial use.

This repo uses [Git LFS](https://git-lfs.github.com/) due to its large file size. If don't install Git LFS, [you may get graphical errors](https://help.github.com/en/github/managing-large-files/collaboration-with-git-large-file-storage).

#### Video:
<a href="http://www.youtube.com/watch?feature=player_embedded&v=HRU1hxCyKoM" target="_blank"><img src="https://static.wixstatic.com/media/3978e6_7d71e5528a2442c49250ffc6764d093cf003.jpg" alt="Video Clip of AH:WF" width="853" height="480" border="10" /></a>

<h2 id="Features">Key Features:</h2>

* [Virtual Reality](https://twitter.com/FlyScript/status/1141880057603993600) support for an immersive and engaging experience
* Realistic [lift, thrust, and drag physics simulations](https://github.com/flyscript/Angels-High/blob/master/AngelsHigh-Source/Source/AngelsHighWF/Private/AircraftBase.cpp#L114)
* Dynamic equations that alter lift and drag based on aircraft [alpha to the airstream](https://github.com/flyscript/Angels-High/blob/master/AngelsHigh-Source/Source/AngelsHighWF/Public/AircraftModel.h#L44)
* The aircraft can [stall and even land when the minimum thrust is not constrained](https://github.com/flyscript/Angels-High/blob/master/AngelsHigh-Source/Source/AngelsHighWF/Private/AircraftBase.cpp#L181)!
* Reponsive [heads up display](https://www.youtube.com/watch?v=HRU1hxCyKoM) feeds critical information to the player-pilot in a realistic way
* A camera that can move around in [first and third person views](https://github.com/flyscript/Angels-High/blob/master/AngelsHigh-Source/Source/AngelsHighWF/Private/PlayerAircraft.cpp#L141) to help you [navigate the airspace](https://twitter.com/FlyScript/status/1144583329326538752)
* A virtual 3D cockpit that [responds in real-time](https://twitter.com/FlyScript/status/1143972143291674625) to user input
* Throttle, stick and pedals [respond to keyboard or controller inputs](https://github.com/flyscript/Angels-High/blob/master/AngelsHigh-Source/Source/AngelsHighWF/Private/PlayerAircraft.cpp#L122) as you fly!
* You can connect a HOTAS like the X55 Rhino via XInput keymapping to create a [realistic cockpit](https://twitter.com/FlyScript/status/1141881970122788864)!
* [Weapons loadouts](https://github.com/flyscript/Angels-High/blob/master/AngelsHigh-Source/Source/AngelsHighWF/Private/AircraftBase.cpp#L291) that mimmick real life air-to-air, air-to-ground, and multirole applications
* [Swappable loadout selections](https://github.com/flyscript/Angels-High/blob/master/AngelsHigh-Source/Source/AngelsHighWF/Public/AircraftBase.h#L56) via dropdown in UE4 editor
* An [object-pooling](https://github.com/flyscript/Angels-High/blob/master/AngelsHigh-Source/Source/AngelsHighWF/Private/PlayerAircraft.cpp#L230) [cannon](https://github.com/flyscript/Angels-High/blob/master/AngelsHigh-Source/Source/AngelsHighWF/Private/PlayerAircraft.cpp#L189) that can light up ground targets
* A thrilling feeling of [speed](https://github.com/flyscript/Angels-High/blob/master/AngelsHigh-Source/Source/AngelsHighWF/Private/AircraftBase.cpp#L176) as you turn on the [afterburners](https://twitter.com/FlyScript/status/1157043515366543362)
* Dynamic player feedback effects such as [G-induced blackout and redout](https://github.com/flyscript/Angels-High/blob/master/AngelsHigh-Source/Source/AngelsHighWF/Private/AircraftBase.cpp#L259), [haptic feedback](), [camera shake](https://github.com/flyscript/Angels-High/blob/master/AngelsHigh-Source/Source/AngelsHighWF/Private/PlayerAircraft.cpp#L139), [1st and 3rd person accoustic differences](https://github.com/flyscript/Angels-High/blob/master/AngelsHigh-Source/Source/AngelsHighWF/Private/PlayerAircraft.cpp#L381)
