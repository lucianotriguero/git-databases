//////////////////////////////////////////////////////////////////////
//Purpose:  Convert an cvs excell file containig the students data  //
//          to a cvs file to be imported by it's learning           //
//Usage: excell2itslearning infile outfile                          //
//Writen by: L.Triguero (LT)                                        //
//Example: Developing with git.
//////////////////////////////////////////////////////////////////////

#include <cstdlib>
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <locale>

using namespace std;

#define ANTAL 500
#define DEBUG 0

typedef struct
{
  string name;
  string surname;
  string klass;
  string personnr;
  string epost;
  string mobil;
  string username;
} STUDENT;

//Function Prototypes
int readin(fstream& in, string* listan);
void split(const string* str, const string d, const int n, vector<STUDENT>& );
void toLower(string& str);
string tlocale(const string s1);
string create_username(const string s1, const string s2);
void writelistan(fstream& out, const string* l, const int n);
void writetable(fstream& out, const vector<STUDENT>& );

main(int argc, char* argv[]) 
{

  if ( argc == 1 ) {
    cout << "Usage: excell2itslearning.x infile outfile " << endl;
    exit(1);
  }


  string listan[ANTAL];

  fstream in(argv[1], ios::in);
  if( in.fail() ) {
    cerr << "File: " << argv[1] << " could no be opened. Exiting ... " << endl;
    exit(1);
  }

  fstream out(argv[2], ios::out);
  if( out.fail() ) {
    cerr << "File could no be opened. Exiting ... " << endl;
    exit(2);
  }  

  int nstudents = readin(in,listan);
  vector<STUDENT> table;
  string delimiter = ",";
  split(listan,delimiter,nstudents,table);
  writetable(out,table);
  
  in.close();
  out.close();

  return 0;
}

int readin(fstream& in, string* lines) 
{
  int n = 0;
  while(1) 
  {
    //in >> lines[n];
    getline(in,lines[n],'\n');
    if ( in.eof() == 1 ) break;
    n++;
  } 
  return n;
}
    
void split(const string* str, const string delimiter, const int n, vector<STUDENT>& table)
{
    int nkol=6 ;
    string st_uppgift[n][nkol];
    unsigned int lastPos, start, pos;
    int i, j;
    STUDENT elev;

    //Split line and fill table 
    for ( i = 0; i < n; i++)
    {
      lastPos = str[i].size();
      start = 0;
      for ( j = 0; j < nkol; j++ )
      {
	pos = str[i].find(delimiter,start);
	st_uppgift[i][j] = str[i].substr(start,pos-start);
        start = pos+1; 
      }     
      elev.name = st_uppgift[i][0];
      elev.surname = st_uppgift[i][1];
      elev.klass = st_uppgift[i][2];
      elev.personnr = st_uppgift[i][3];
      elev.epost = st_uppgift[i][4];
      elev.mobil = st_uppgift[i][5];
      elev.username = create_username(elev.name,elev.surname);
      table.push_back(elev);
    }
}

//The STL algorithm way 
void toLower(string& str)
{      
   transform(str.begin(), str.end(), str.begin(), ::tolower);
}

string tlocale(const string s1)
{

  string lstr=s1;

  for(int i = 0; i < lstr.length(); i++)
     {
          switch(lstr[i])
          {
          case char('ä'):
	    lstr[i] = 'a';
	    break;
	  case char('ö'):
	    lstr[i] = 'o';
	    break;
          }
     }

  //replace(lstr.begin(), lstr.end(), char('ä'), 'a');
  //replace(lstr.begin(), lstr.end(), char('ö'), 'o');

  return lstr;
}

string create_username(const string s1, const string s2)
{
  string username;

  string namn = s1;
  string efternamn = s2;

  //Step # 1: Transform string to lowercase
  toLower(namn);
  toLower(efternamn); 

  //Step # 2: Manipulate locale: "ö", "å", "ä", "ü"
  string lsurname = tlocale(efternamn);


  //Step # 3: Create username: name.username
  username = namn + "." + lsurname;  

  return username;   
}

void writelistan(fstream& out, const string* listan, const int n)
{
  for( int i = 0; i<n; i++) {
    cout << i+1 << setw(10) << listan[i] << endl;   
   }
}

void writetable(fstream& out, const vector<STUDENT>& table )
{
     for ( int i = 0; i<table.size(); i++ )
     {
           out  << table.at(i).name << ","
                << table.at(i).surname << ","
                << table.at(i).username << ","
                << table.at(i).klass << "," 
	        << table.at(i).personnr << ","
	        << table.at(i).epost << ","
	        << table.at(i).mobil << endl;
     }
     cout << endl;  

}




