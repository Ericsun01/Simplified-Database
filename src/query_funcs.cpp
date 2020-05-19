#include "query_funcs.h"
#include <iomanip>

void add_player(connection *C, int team_id, int jersey_num, string first_name, string last_name,
                int mpg, int ppg, int rpg, int apg, double spg, double bpg)
{
  string head = "INSERT INTO PLAYER (TEAM_ID, UNIFORM_NUM, FIRST_NAME, LAST_NAME, MPG, PPG, RPG, APG, SPG, BPG) VALUES (";
  work W(*C);
   std::string curr1 = "";
  if(first_name=="Ja'Quan"){
    std::string tmp = "Ja''Quan";
    curr1 = "\'"+tmp+"\'";
  }
  else{ 
    curr1 = "\'"+first_name+"\'";
  }
  std::string curr2 = "\'"+last_name+"\'";
  string Team_id = to_string(team_id);
  string Jersey_num = to_string(jersey_num);
  string Mpg = to_string(mpg);
  string Ppg = to_string(ppg);
  string Rpg = to_string(rpg);
  string Apg = to_string(apg);
  string Spg = to_string(spg);
  string Bpg = to_string(bpg);
  string com = ", ";
  string tail = " );";
  string order=head+Team_id+com+Jersey_num+com+curr1+com+curr2+com+Mpg+com+Ppg+com+Rpg+com+Apg+com+Spg+com+Bpg+tail;
  W.exec(order);
  W.commit();
}


void add_team(connection *C, string name, int state_id, int color_id, int wins, int losses)
{ work W(*C);
  string head = "INSERT INTO TEAM (NAME, STATE_ID, COLOR_ID, WINS, LOSSES) VALUES (";
  string Name = "\'"+name+"\'";
  string State_id = to_string(state_id);
  string Color_id = to_string(color_id);
  string Wins = to_string(wins);
  string Losses = to_string(losses);
  string com = ", ";
  string tail = " );";
  string order = head+Name+com+State_id+com+Color_id+com+Wins+com+Losses+tail;
  W.exec(order);
  W.commit();
}


void add_state(connection *C, string name)
{
  work W(*C);
  string head = "INSERT INTO STATE (NAME) VALUES (";
  string Name = "\'"+name+"\'";
  string tail = " );";
  string order = head+Name+tail;
  W.exec(order);
  W.commit();
}


void add_color(connection *C, string name)
{
  work W(*C);
  string head = "INSERT INTO COLOR (NAME) VALUES (";
  string Name = "\'"+name+"\'";
  string tail = " );";
  string order = head+Name+tail;
  W.exec(order);
  W.commit();
}


void query1(connection *C,
	    int use_mpg, int min_mpg, int max_mpg,
            int use_ppg, int min_ppg, int max_ppg,
            int use_rpg, int min_rpg, int max_rpg,
            int use_apg, int min_apg, int max_apg,
            int use_spg, double min_spg, double max_spg,
            int use_bpg, double min_bpg, double max_bpg
            )
{
  int init=0;
  string order = "SELECT * FROM PLAYER";
  string body;
  string tail = ";";
  if(use_mpg==1){
    if(init==0)
      {body=body+" WHERE ";}
    else
      {body=body+" AND ";}
    string head = "(MPG BETWEEN ";
    string Min_mpg = to_string(min_mpg);
    string Max_mpg = to_string(max_mpg);
    string And = " AND ";
    string End = ") ";
    body=body+head+Min_mpg+And+Max_mpg+End;
    init=1;
  }

  if(use_ppg==1){
    if(init==0)
      {body=body+" WHERE ";}
    else
      {body=body+" AND ";}
    string head = "(PPG BETWEEN ";
    string Min_ppg = to_string(min_ppg);
    string Max_ppg = to_string(max_ppg);
    string And = " AND ";
    string End = ") ";
    body=body+head+Min_ppg+And+Max_ppg+End;
    init=1;
  }

  if(use_rpg==1){
    if(init==0)
      {body=body+" WHERE ";}
    else
      {body=body+" AND ";}
    string head = "(RPG BETWEEN ";
    string Min_rpg = to_string(min_rpg);
    string Max_rpg = to_string(max_rpg);
    string And = " AND ";
    string End = ") ";
    body=body+head+Min_rpg+And+Max_rpg+End;
    init=1;
  }

  if(use_apg==1){
    if(init==0)
      {body=body+" WHERE ";}
    else
      {body=body+" AND ";}
    string head = "(APG BETWEEN ";
    string Min_apg = to_string(min_apg);
    string Max_apg = to_string(max_apg);
    string And = " AND ";
    string End = ") ";
    body=body+head+Min_apg+And+Max_apg+End;
    init=1;
  }

  if(use_spg==1){
    if(init==0)
      {body=body+" WHERE ";}
    else
      {body=body+" AND ";}
    string head = "(SPG BETWEEN ";
    string Min_spg = to_string(min_spg);
    string Max_spg = to_string(max_spg);
    string And = " AND ";
    string End = ") ";
    body=body+head+Min_spg+And+Max_spg+End;
    init=1;
  }

  if(use_bpg==1){
    if(init==0)
      {body=body+" WHERE ";}
    else
      {body=body+" AND ";}
    string head = "(BPG BETWEEN ";
    string Min_bpg = to_string(min_bpg);
    string Max_bpg = to_string(max_bpg);
    string And = " AND ";
    string End = ") ";
    body=body+head+Min_bpg+And+Max_bpg+End;
    init=1;
  }

  order=order+body+tail;
  std::cout<<"PLAYER_ID TEAM_ID UNIFORM_ID FIRST_NAME LAST_NAME MPG PPG RPG APG SPG BPG"<<std::endl;
  nontransaction N(*C);
  result R(N.exec(order));
  for(result::const_iterator c=R.begin();c!=R.end();++c)
    { std::cout.setf(ios::fixed);
      std::cout<<c[0].as<int>()<<" "<<c[1].as<int>()<<" "<<c[2].as<int>()<<" "<<c[3].as<string>()<<" "<<c[4].as<string>()<<" "<<c[5].as<int>()<<" "<<c[6].as<int>()<<" "<<c[7].as<int>()<<" "<<c[8].as<int>()<<setprecision(1)<<" "<<c[9].as<double>()<<" "<<c[10].as<double>()<<std::endl;
    }
}

void query2(connection *C, string team_color)
{
  string order = "SELECT TEAM.NAME FROM TEAM, COLOR WHERE TEAM.COLOR_ID = COLOR.COLOR_ID AND COLOR.NAME = ";
  string Team_color = "\'"+team_color+"\'";
  string tail = ";";
  order=order+Team_color+tail;
  std::cout<<"NAME"<<std::endl;
  nontransaction N(*C);
  result R(N.exec(order));
  for(result::const_iterator c=R.begin();c!=R.end();++c){
    std::cout<<c[0].as<string>()<<std::endl;
  }
}


void query3(connection *C, string team_name)
{ string Team_name = "\'"+team_name+"\'";
  string order="SELECT PLAYER.FIRST_NAME, PLAYER.LAST_NAME FROM PLAYER, TEAM WHERE PLAYER.TEAM_ID = TEAM.TEAM_ID AND TEAM.NAME = "+Team_name+" ORDER BY PPG DESC;";
  std::cout<<"FIRST_NAME LAST_NAME"<<std::endl;
  nontransaction N(*C);
  result R(N.exec(order));
  for(result::const_iterator c=R.begin();c!=R.end();++c){
    std::cout<<c[0].as<string>()<<" "<<c[1].as<string>()<<std::endl;
  }
}


void query4(connection *C, string team_state, string team_color)
{
  string Team_state = "\'"+team_state+"\'";
  string Team_color = "\'"+team_color+"\'";
  string order = "SELECT PLAYER.FIRST_NAME, PLAYER.LAST_NAME, PLAYER.UNIFORM_NUM FROM PLAYER, TEAM, COLOR, STATE WHERE PLAYER.TEAM_ID = TEAM.TEAM_ID AND TEAM.COLOR_ID = COLOR.COLOR_ID AND TEAM.STATE_ID = STATE.STATE_ID AND STATE.NAME = "+Team_state+" AND COLOR.NAME = "+Team_color+";";
  std::cout<<"FIRST_NAME LAST_NAME UNIFORM_NUM"<<std::endl;
  nontransaction N(*C);
  result R(N.exec(order));
  for(result::const_iterator c=R.begin();c!=R.end();++c){
    std::cout<<c[0].as<string>()<<" "<<c[1].as<string>()<<" "<<c[2].as<int>()<<std::endl;
  }
}


void query5(connection *C, int num_wins)
{ string Num_wins = to_string(num_wins);
  string order = "SELECT PLAYER.FIRST_NAME, PLAYER.LAST_NAME, TEAM.NAME, TEAM.WINS FROM PLAYER, TEAM WHERE PLAYER.TEAM_ID = TEAM.TEAM_ID AND TEAM.WINS > "+Num_wins+";";
  std::cout<<"FIRST_NAME LAST_NAME TEAM_NAME WINS"<<std::endl;
  nontransaction N(*C);
  result R(N.exec(order));
  for(result::const_iterator c=R.begin();c!=R.end();++c){
    std::cout<<c[0].as<string>()<<" "<<c[1].as<string>()<<" "<<c[2].as<string>()<<" "<<c[3].as<int>()<<std::endl;
  }
}
