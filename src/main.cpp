#include <iostream>
#include <pqxx/pqxx>
#include <fstream>
#include <sstream>
#include <string>

#include "exerciser.h"

using namespace std;
using namespace pqxx;

int main (int argc, char *argv[]) 
{

  //Allocate & initialize a Postgres connection object
  connection *C;

  try{
    //Establish a connection to the database
    //Parameters: database name, user name, user password
    C = new connection("dbname=ACC_BBALL user=postgres password=passw0rd");
    if (C->is_open()) {
      cout << "Opened database successfully: " << C->dbname() << endl;
    } else {
      cout << "Can't open database" << endl;
      return 1;
    }
 
     //TODO: create PLAYER, TEAM, STATE, and COLOR tables in the ACC_BBALL database
    
    std::string dropplayer = "DROP TABLE IF EXISTS PLAYER CASCADE;";
    std::string dropteam =  "DROP TABLE IF EXISTS TEAM CASCADE;";
    std::string dropstate = "DROP TABLE IF EXISTS STATE CASCADE;";
    std::string dropcolor =  "DROP TABLE IF EXISTS COLOR CASCADE;";
    
    std::string player = "CREATE TABLE PLAYER("
      "PLAYER_ID 	SERIAL	PRIMARY KEY," 
      "TEAM_ID	        INT,"  
      "UNIFORM_NUM	INT," 
      "FIRST_NAME	TEXT," 
      "LAST_NAME	TEXT," 
      "MPG		INT," 
      "PPG		INT," 
      "RPG		INT," 
      "APG		INT," 
      "SPG		REAL," 
      "BPG		REAL,"
      "CONSTRAINT TEAMCLEAR FOREIGN KEY (TEAM_ID) REFERENCES TEAM(TEAM_ID) ON DELETE SET NULL ON UPDATE CASCADE);";

    std::string team = "CREATE TABLE TEAM(" 
      "TEAM_ID	SERIAL PRIMARY KEY," 
      "NAME		TEXT," 
      "STATE_ID    	INT," 
      "COLOR_ID	        INT,"
      "WINS		INT,"
      "LOSSES		INT,"
      "CONSTRAINT STATECLEAR FOREIGN KEY (STATE_ID) REFERENCES STATE(STATE_ID) ON DELETE SET NULL ON UPDATE CASCADE,"
      "CONSTRAINT COLORCLEAR FOREIGN KEY (COLOR_ID) REFERENCES COLOR(COLOR_ID) ON DELETE SET NULL ON UPDATE CASCADE);";

    std::string state = "CREATE TABLE STATE("
      "STATE_ID	SERIAL PRIMARY KEY,"
      "NAME		TEXT);";

    std::string color = "CREATE TABLE COLOR ("
      "COLOR_ID SERIAL PRIMARY KEY," 
      "NAME             TEXT);";
   
    work W(*C);
    W.exec(dropplayer);
    W.exec(dropteam);
    W.exec(dropstate);
    W.exec(dropcolor);
    W.exec(state);
    W.exec(color);
    W.exec(team);
    W.exec(player);
    W.commit();

    //      load each table with rows from the provided source txt files
    std::string state_name, color_name, team_name, first_name, last_name, curr1,curr2, curr3, curr4;
    double spg, bpg;
    int color_colorid, state_stateid, team_teamid, team_stateid, team_colorid, wins, losses, player_id, player_teamid, uniform_num, mpg, ppg, rpg, apg;
    std::stringstream flow;

    ifstream fteam("team.txt");
    ifstream fcolor("color.txt");
    ifstream fstate("state.txt");
    ifstream fplayer("player.txt");

    while(getline(fcolor, curr1))
      { flow.clear();
	flow.str(curr1);
	flow >> color_colorid >> color_name;
	add_color(C, color_name);
      }
    
    while(getline(fstate, curr2))
      {
	flow.clear();
	flow.str(curr2);
	flow >> state_stateid >> state_name;
	add_state(C, state_name);
      }

    while(getline(fteam, curr3))
      {
	flow.clear();
	flow.str(curr3);
	flow >> team_teamid >> team_name >> team_stateid >> team_colorid >> wins >> losses;
	add_team(C, team_name, team_stateid, team_colorid, wins, losses);
      }

    while(getline(fplayer, curr4))
      {
	flow.clear();
	flow.str(curr4);
	flow >> player_id >> player_teamid >> uniform_num >> first_name >>last_name >> mpg >> ppg >> rpg >> apg >> spg >> bpg;
	add_player(C, player_teamid, uniform_num, first_name, last_name, mpg, ppg, rpg, apg, spg, bpg);
      }
   
 }
  catch (const std::exception &e){
    cerr << e.what() << std::endl;
    return 1;
  }
  exercise(C);
  
  //Close database connection
  C->disconnect();

  return 0;
}


