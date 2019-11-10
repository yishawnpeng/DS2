//資工四甲 10527142 彭義翔
#include <iostream> 
#include <fstream> 
#include <vector> 
#include <cstdlib> 
#include <iomanip> 
#include <stdio.h>
#include <string.h>
#include <math.h>

using namespace std;

typedef struct datatree{ // its order and score for each node 
	int idnum;
	int Score;
} Data;

void printall( vector<Data> datatree ){ // print info inorder for mis1 and 2
	for ( int i = 0 ; i < datatree.size() ; i ++ ) 
		printf( "[%2d] (%d,%d)\n", i, datatree[i].Score, datatree[i].idnum+1 ) ; // the began is 0 so each order must+1
} // datatree

void printall3( vector<Data> datatree ){ // print info inorder for mis3
	for ( int i = 0 ; i < datatree.size() ; i ++ ) 
		if ( datatree[i].Score == -1 ) 
			printf( "[%2d] (  ,  )\n", i ) ;
		else
			printf( "[%2d] (%d,%d)\n", i, datatree[i].Score, datatree[i].idnum ) ;
} // datatree

int minormax( int place ){ // count the palce node is in max level or min
	int level = ( log2( place + 1 ));	
	level = level % 2;
	if( level == 0 )
		return 0; // 0 min 
	else
		return 1; // 1 max
} // minormax

int leftorright( int place ){  // count the palce node is in left level or right
	int LEVEL = (int)floor( log2( place + 1 )) ;
	int LR = exp2(LEVEL-1)*3-1;
	if ( place < LR ) 
		return 0; // 0 left
	else 
		return 1; // 1 right
} //leftorright

int displacement( int place ){ // count the relativelyplace which give palce node
	int LEVEL = (int)floor( log2( place + 1 )) ;
	int xg = exp2(LEVEL-1);
	if ( leftorright(place) == 0 ) 
		return ( place + xg ); // need add to find who is place at right
	else
		return ( place - xg ); // sub
} // displacement
 
int main(){
	//vector<Data> datatree ;
	//int sNum = 0;
	string command ; // end cmd for while
	int inputtemp ;
	while( command != "0" ){
		cout << endl << "[1]Mission1 or [2]Mission2 or [3]Mission3" << endl;
		cin >> command ;				// choice which mission
		if( command == "1" ){
			vector<Data> datatree ; 	// where the data save and operating
			cout << "Mission1" << endl;
			cout << "輸入[0,100](用空白隔開 其他任意符號結束):" ;
			int count = 0 ; // num of order
			//cin >> inputtemp ;
			//scanf( "%s", &inputtemp ) ;
			//cout << "BT" << endl;
			//printf( "%s\n", inputtemp ) ;
			//cout << "It is not legal scort" << endl;
			while ( scanf( "%d", &inputtemp ) == true ) { // just read int
				//printf( "%d\n", inputtemp ) ;
				if ( inputtemp >=0 && inputtemp <= 100 ) { // (0,100)
					Data tempD ;
					tempD.idnum = count ;
					tempD.Score = inputtemp ;
					datatree.push_back(tempD) ; // put new
					if ( datatree.size() > 1 ) { 
						int a = count ;
						int parent = (a-1)/2 ;
						while ( parent >= 0 && datatree[a].Score > datatree[parent].Score ){ // star rebuild
							swap(datatree[a], datatree[parent] ) ;
							a = parent;
							parent = (a-1)/2 ;
						} // while
					} // if
					count++ ;
				} //if
				else
					cout << "It is not legal score" << endl;

			} // while
			
			printf( "\nMission1建立最大堆積\n" ) ; // print data and clean
			printall( datatree ) ;
			datatree.clear() ;
			
		} // if 
		else if( command == "2" ){
			vector<Data> datatree ;
			cout << "Mission2" << endl;
			cout << "輸入[0,100](用空白隔開 其他任意符號結束):" ;
			int count = 0 ;
			while ( scanf( "%d", &inputtemp ) == true ) {
				//printf( "%d\n", inputtemp ) ;
				if ( inputtemp >=0 && inputtemp <= 100 ) {
					Data tempD ;
					tempD.idnum = count ;
					tempD.Score = inputtemp ;
					datatree.push_back(tempD) ;
					if ( datatree.size() > 1 && datatree.size() <= 3 ) { // if just in level1.2 don't need to check garndparent
						int a = count ;
						int parent = (a-1)/2 ;
						//printf( "**\n%d",datatree[parent].Score) ;
						//printf( "%d\n**",datatree[a].Score) ;
						if (datatree[a].Score < datatree[parent].Score) 
							swap(datatree[a], datatree[parent] ) ;
					} // if
					else if ( datatree.size() > 3 ) { //  need to check garndparent
						int a = count ;
						int parent = (a-1)/2 ;
						//while ( parent >= 0 ){ // && datatree[a].Score > datatree[parent].Score
						if ( minormax(a) == 0 ) { // this level min
							//printf( "%d",datatree[a].Score) ;
							//printf( "%d",datatree[parent].Score) ;
							if ( datatree[a].Score > datatree[parent].Score ){ // need change with parent
								swap(datatree[a], datatree[parent] ) ;
								a = parent; // move up to continu
								int grandparent = (((a-1)/2)-1)/2 ;
								while ( grandparent >= 0 ){ // check until top
									if ( datatree[a].Score > datatree[grandparent].Score ){ // in here just max level 
										swap(datatree[a], datatree[grandparent] ) ;
										a = grandparent ;
										grandparent = (((a-1)/2)-1)/2 ;
									} // if
									else // if don't change then meens done
										break ;
								} // while
							} // if
							else{ // not need change with parent
								int grandparent = (((a-1)/2)-1)/2 ;
								//printf("%d", grandparent ) ;
								while ( grandparent >= 0 ){ // check until top
									if ( datatree[a].Score < datatree[grandparent].Score ){ // in here just max level 
										swap(datatree[a], datatree[grandparent] ) ;
										a = grandparent ;
										grandparent = (((a-1)/2)-1)/2 ;
									} // if
									else // if don't change then meens done
										break ;
								} // while
							} // else
						} // if
						else if ( minormax(a) == 1 ) { // this level max
							if ( datatree[a].Score < datatree[parent].Score ){ // need change with parent
								swap(datatree[a], datatree[parent] ) ;
								a = parent; // move up to continu
								int grandparent = (((a-1)/2)-1)/2 ;
								while ( grandparent >= 0 ){ // check until top
									if ( datatree[a].Score < datatree[grandparent].Score ){ // in here just min level 
										swap(datatree[a], datatree[grandparent] ) ;
										a = grandparent ;
										grandparent = (((a-1)/2)-1)/2 ;
									} // if
									else // if don't change then meens done
										break ;
								} // while
							} // if
							else{ // not need change with parent
								int grandparent = (((a-1)/2)-1)/2 ;
								while ( grandparent >= 0 ){ // check until top
									if ( datatree[a].Score > datatree[grandparent].Score ){ // in here just min level 
										swap(datatree[a], datatree[grandparent] ) ;
										a = grandparent ;
										grandparent = (((a-1)/2)-1)/2 ;
									} // if
									else // if don't change then meens done
										break ;
								} // while
							} // else
						} // else if
							//swap(datatree[a], datatree[parent] ) ;
							//a = parent;
							//parent = (a-1)/2 ;
						//} // while
					} // if
					count++ ;
				} //if
				else // (0.100)
					cout << "It is not legal score" << endl;

			} // while
			
			printf( "\nMission2建立最小最大堆積\n" ) ; // print and clean
			printall( datatree ) ;
			datatree.clear() ;
		} // elif
		else if( command == "3" ){
			vector<Data> datatree ;
			cout << "Mission3" << endl;
			cout << "輸入[0,100](用空白隔開 其他任意符號結束):" ;
			int count = 1 ;
			Data tempD ; // it is empty for begin 
			tempD.idnum = 0 ;
			tempD.Score = -1 ;
			datatree.push_back(tempD) ; // push the root which is empty
			while ( scanf( "%d", &inputtemp ) == true ) {
				//printf( "%d\n", inputtemp ) ;
				if ( inputtemp >=0 && inputtemp <= 100 ) {
					tempD.idnum = count ;
					tempD.Score = inputtemp ;
					datatree.push_back(tempD) ;
					if ( datatree.size() > 3 ) {
						int a = count ;
						int relativelyplace = displacement(count) ; // find relativelyplace
						//printf("%d",relativelyplace) ;
						if ( leftorright(a) == 1 ) { // relatively is in left and exist or itself in right
							// relativelyplace < datatree.size() -1 
							if ( datatree[a].Score < datatree[relativelyplace].Score ){ // if small then left need swap first 
								swap(datatree[a], datatree[relativelyplace] ) ;
								a = relativelyplace;
								int parent = (a-1)/2 ;
								while ( parent > 0 && datatree[a].Score < datatree[parent].Score ){ // up check until top
									swap(datatree[a], datatree[parent] ) ;
									a = parent;
									parent = (a-1)/2 ;
								} // while 
							} // if
							else{														// still stay in right
								int parent = (a-1)/2 ;
								while ( parent > 0 && datatree[a].Score > datatree[parent].Score ){ // up check until top
									swap(datatree[a], datatree[parent] ) ;
									a = parent;
									parent = (a-1)/2 ;
								} // while 
							} // else 
						} // if
						else{ // relatively is not exist so need to compare with it parent
							relativelyplace = (relativelyplace-1)/2 ;
							if ( datatree[a].Score > datatree[relativelyplace].Score ){ // if biger then right then swap
								swap(datatree[a], datatree[relativelyplace] ) ;
								a = relativelyplace;
								int parent = (a-1)/2 ;
								while ( parent > 0 && datatree[a].Score > datatree[parent].Score ){ // up check until top
									swap(datatree[a], datatree[parent] ) ;
									a = parent;
									parent = (a-1)/2 ;
								} // while 
							} // if
							else{														// still stay in right
								int parent = (a-1)/2 ;
								while ( parent > 0 && datatree[a].Score < datatree[parent].Score ){ // up check until top
									swap(datatree[a], datatree[parent] ) ;
									a = parent;
									parent = (a-1)/2 ;
								} // while 
							} // else 
						} // else
					//	int a = count ;
					//	int parent = (a-1)/2 ;
					//	while ( parent >= 0 && datatree[a].Score > datatree[parent].Score ){
					//		swap(datatree[a], datatree[parent] ) ;
					//		a = parent;
					//		parent = (a-1)/2 ;
					//	} // while
					} // if
					count++ ;
				} //if
				else // (0,100)
					cout << "It is not legal score" << endl;
			} // while
			
			printf( "\nMission3建立雙向堆積\n" ) ; // print and clean
			printall3( datatree ) ;
			datatree.clear() ;
		} // elif
		else { // only 1.2.3
			cout << "It is not legal number" << endl;
		} // elif
			
		cout << endl << "[0]Quit or [Any other]continue?" << endl;
		cin >> command ;
		if( command == "0" )
			return 0;
	} // while
	
} // main
