# 202---Arkapong
CAB202 Microprocessors

<h1>Arkapong</h1>
The creation of a pong based game in C using a university provided library.

Requires:
 - Cygwin (Link Coming Soon)
 
Instructions:
 - Coming soon.
 
Controls:
 Arrow keys - move your paddle. 
 Q - quit
 R - restart
 S - cycle speed
 Space - pause
 G - cheat giant paddle
 
 Toggles:
  1 - The Opponent AI
  2 - Not Implemented
  3 - Basic Obstacle Blocks
  4 - Extender Blocks
  5 - Shrinker Blocks
  6 - Ball Duplicator Blocks
  7 - Wind
  8 - The Muncher

Notes:
For My blocks special and normal, I have allowed them to overlap as to create more
 interesting structures in the on-screen environment.

For Wind in my Arkapong Game I have it as a chance to gust that each 'turn' rather
 than a constant force as it emulates real wind and it gives players a better chance
 to make a comeback.
 
The Ball Muncher will eat balls and special blocks or try to move on its turn.
 The muncher increases in size/tier every time it eats up to tier 3.
 The muncher knows it has an eating problem and so runs from balls when possible.
 Eating a paddle size block changes the size of both players paddles.
 Splitter blocks increases the tier of the muncher to max size.
 Wind blocks, give the muncher wind and reduces its size to minimum.
 Normal blocks dont taste taste nice so the muncher wont eat them.

Also included are a couple of utility functions: a game speed function press 's' to
 cycle through game speeds, very slow to very fast. Note these also affect the
 players movement to keep the game fair. 
 Pressing space will pause the game.
 Pressing 'g' will increase the size of the players paddle to the maximum.