# Ys 1&2 Chronicles Co-Op Mod
This mod allows another player to join the fun locally. Controls for player 2 are keyboard based but configurable, and something like Steam Input can be used to map a controller to keys.

Player 1 is the main player. Camera will follow him and some interactions are only available to player 1. P1 stats are copied to P2. P2 will teleport to P1 when too far out of view. The distance threshold can be configured. 4:3 aspect ratio setting is recommended for bigger FOV. If either player dies, you lose.

This mod works for both Ys 1 and Ys 2, although the implementations differ as the games are programmed surprisingly differently. It should work whether you start a new game or load existing unmodded saves or saves made with this mod.

### Install: For both games, simply unzip the mod from the releases into the game folder, next to the exe.

To uninstall, remove the dbghelp dll files. If loading a co-op save, it should revert to normal when changing rooms.

## Additional Feature: Quicksave
Press the quicksave button as defined in the coop_config.txt at any time that you can normally save, to save without interrupting gameplay. You can configure save slots that will be used for quicksaves and it will cycle through those slots. Even in singleplayer, it's a good idea to make frequent saves in these games, but that's inconvenient to do in multiplayer, which is why I added quicksaves. I also highly recommend saving often in case of any game breaking issues caused by the mod.

## Additional Feature: Regen Speedup
Press the speedup button as defined in the coop_config.txt at any time that you can regen HP to speed it up. It's a bit different between the games, but in both cases it makes the game faster while standing still, so make sure the area is safe first. The sped up regen helps minimize downtime, which is an issue that is especially apparent in co-op, which is why I added this feature.

## Ys 1
The other player is spawned by borrowing some Feena related code, but you can still have Feena at the same time. P2 and Feena share an HP bar.

Adol's sprite is also used for P2 because it has all the necessary animation frames and I can easily assign it to P2. Making a distinct sprite for P2 would likely be a significant undertaking.

Players can be distinguished from one another by text above their heads that says P1 or P2 in different colors.

## Ys 2
The other player is spawned by setting the flags for Tarf to be following Adol, then changing the properties of Tarf. He uses Adol's Roo sprite because it has all the necessary animation frames. This way the players look significantly different most of the time.

He will not spawn in Lava Colony until you do his quest to the point where you give him the Black Orb. The escort mission will be significantly easier because P2 can continue to control him. In other instances when Tarf would normally be present, he is replaced by P2, but P1 can still trigger the dialog with him.

If P2 is not spawned in, try changing rooms.

P1 and P2 can both use fire and shield magic if it is equipped. MP charge is shared, but total MP is separate.

## Progress
I have completed the mod and testing for both games. However, there may still be issues, as later changes can unexpectedly break earlier parts of the games. I may also have overlooked something. There are also some minor issues that I'm aware of, but it's not worth it to me to fix every minor issue. Feel free to play how you want, but sometimes messing around with what the mod allows you to do can break things. If you do run into issues that are preventing you from progressing as expected, please report them to me, preferably with save files included, so I can fix them.

## Compiling from source
Should be easy. This was done using Visual Studio 2022. I don't think there are any particular dependencies assuming you have the C++ development module, so just clone and open the solution and try building for x86, rename to dbghelp.dll and include the original dbghelp from SysWOW64 as dbghelp_original.dll.

This is my first time making a hooked dll type mod so it's probably not ideal but it works. You could easily adapt this to other games as the only game specific parts are the memory addresses and mod logic. It should also be possible to build for x64 games, just make sure to get the dbghelp.dll from system32 in that case.
