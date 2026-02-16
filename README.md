# Ys 1&2 Chronicles Co-Op Mod
This mod allows another player to join the fun locally. Controls for player 2 are keyboard based but configurable, and something like Steam Input can be used to map a controller to keys.

Player 1 is the main player. Camera will follow him and some interactions are only available to player 1. P1 stats are copied to P2. P2 will teleport to P1 when too far out of view. The distance threshold can be configured. If either player dies, you lose.

This mod works for both Ys 1 and Ys 2, although the implementations differ as the games are programmed surprisingly differently. It should work whether you start a new game or load existing unmodded saves or saves made with this mod.

### Install: For both games, simply unzip the mod from the releases into the game folder, next to the exe.

To uninstall, remove the dbghelp dll files. If loading a co-op save, it should revert to normal when changing rooms.

## Ys 1
The other player is spawned by borrowing some Feena related code, but you can still have Feena at the same time. P2 and Feena share an HP bar.

Adol's sprite is also used for P2 because it has all the necessary animation frames and I can easily assign it to P2. Making a distinct sprite for P2 would likely be a significant undertaking.

Players can be distinguished from one another by text above their heads that says P1 or P2 in different colors.

Known issues:
-P2 Sword animation may appear at wrong locations
-Crash sometimes on room transition, especially when exiting shrine or immediately after loading a save
-Bosses knockback P1 when P2 attacks
-Bat boss randomly refers to either P1 or P2 HP on hit
-Feena gets stuck on P2 when bringing her back to town
-Tree and Reah FMVs end abruptly
-Sometimes P1 dies unexpectedly / HP bar shows someone else's HP
-Light in cave gets attached to P2 when loading
-Regen Ring and after-boss recovery doesn't apply to P2
-You can save and load to save P2 from dying
-Sometimes P2 ends up out of bounds when changing rooms

## Ys 2
The other player is spawned by setting the flags for Tarf to be following Adol, then changing the properties of Tarf. He uses Adol's Roo sprite because it has all the necessary animation frames. This way the players look significantly different. When Adol transforms, P2 will blink, so you can still distinguish them.

He will not spawn in Lava Colony until you do his quest to the point where you give him the Black Orb. The escort mission will be significantly easier because P2 can continue to control him.

If P2 is not spawned in, try changing rooms.

P1 and P2 can both use fire magic if it is equipped. MP charge is shared, but total MP is separate.

## Work in progress
Currently Steam version is supported. I will check and fix GOG version once I have tested and solved other potential issues.

Only a limited amount of testing has been done so far. There are probably bugs to fix when going through the entirity of both games.

Other possible additions for future (not necessarily planned but could be worthwhile additions): 
- Adaptive / split / wider camera. This would be really nice, but currently at best I could probably get it to center on the average between players, and I don't know how useful that would even be.
- Auto- / Quicksave. Menuing saves in co-op can be inconvenient.
- Make enemies actually target P2 in Ys 1
- Improved HUD for P2
- Balancing options. Could be good to increase boss HP (Ys 2) or make it more forgiving so one player's fun isn't ruined by the other player dying.
- Built-in controller support for P2
- Custom sprite for P2 like blue haired variant of Adol or something

## Compiling from source
Should be easy. This was done using Visual Studio 2022. I don't think there are any particular dependencies assuming you have the C++ development module, so just clone and open the solution and try building for x86, rename to dbghelp.dll and include the original dbghelp from SysWOW64 as dbghelp_original.dll.

This is my first time making a hooked dll type mod so it's probably not ideal but it works. You could easily adapt this to other games as the only game specific parts are the memory addresses and mod logic. It should also be possible to build for x64 games, just make sure to get the dbghelp.dll from system32 in that case.
