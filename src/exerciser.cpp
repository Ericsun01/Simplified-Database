#include "exerciser.h"

void exercise(connection *C)
{ 
  query2(C,"Red");
  query3(C,"Duke");
  query4(C,"NC","Red");
  query5(C,8);
  add_player(C,1,1,"Junq","Sun",7,7,12,7,1.5,1.5);
  query1(C,0,30,38,0,0,0,1,5,12,0,0,0,0,0,0,0,0,0);
  add_color(C,"crason");
  add_state(C,"X");
  add_team(C,"team_dragon",8,3,18,0);

}
