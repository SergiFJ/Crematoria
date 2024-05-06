# Crematoria
The objective of this project is to program a bot that plays crematoria boardgame (an invented game).

To program this the majority of algorithms implemented are bfs to see what move is better to do in each ocasion. To improve this, we could use dijkstra.

**How to use it**

To run this project you only need a recent g++ version, make installed in your system, plus a modern browser like Firefox or Chrome. And the steps to do are:
1) Open a console and cd to the directory where you extracted the source code.
2) If, for example, you are using Linux, run:
cp AIDummy.o.Linux AIDummy.o
cp Board.o.Linux Board.o
3) Run
make all
to build the game and all the players. Note that Makefile identifies as a player any file matching AI*.cc.
4) This creates an executable file called Game. This executable allows you to run a game using a command like:
./Game Demo Demo Demo Demo -s 30 -i default.cnf -o default.res
This starts a match, with random seed 30, of four instances of the player Demo, in the board defined in default.cnf. The output of this match is redirected to default.res.
5) To watch a game, open the viewer file viewer.html with your browser and load the file default.res.

**Adding your player**

To create a new player with, say, name Riddick, copy AINull.cc (an empty player that is provided as a template) to a new file AIRiddick.cc. Then, edit the new file and change the

#define PLAYER_NAME Null
line to

#define PLAYER_NAME Riddick
