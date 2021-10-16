//資工四甲 10527142 彭義翔
#include <iostream> 
#include <fstream> 
#include <vector> 
#include <cstdlib> 
#include <iomanip> 
#include <stdio.h>
#include <string.h>
#include <math.h>

using namespace std ;

struct dataS{
	int lline ; // if Record for PRINTEDGE it means small vertex
	int lleter ; // if Record for PRINTEDGE it means big vertex
	int isgoal ; // if is goal ==1
	int isvisited ; // for mis3  if it is visited then == 1
};

void mis3( vector<int> &tempS, vector<dataS> data, vector< vector<int> > GDS, int &conutstep, int &findgaol, int right ){
	while ( !tempS.empty() ){
		int findnext = tempS[tempS.size()-1] ; // take the TOP
		int successfind = -1 ; // where can we go (index of data)
		if ( right == 0 ){
			for ( int i = data.size()-1 ; i > 0 ; i-- ){ // find the next root we can go
				if ( GDS[findnext][i] == 1 ){ // P"findnext" to P"i"  has a root
					if ( data[i].isvisited == 0 ){
						successfind = i  ;
						break ;
					} // if
				} // if
			} // for
		} // if
		else if ( right == 1 ){
			for ( int i = 0 ; i < data.size() ; i++ ){ // find the next root we can go
				if ( GDS[findnext][i] == 1 ){ // P"findnext" to P"i"  has a root
					if ( data[i].isvisited == 0 ){
						successfind = i  ;
						break ;
					} // if
				} // if
			} // for
		} // elseif
				
		if ( successfind != -1 ){ // have some where we can go 
			conutstep++ ;
			data[successfind].isvisited = 1 ;
			tempS.push_back(successfind) ;
			//ans.push_back(successfind) ;
			if ( data[successfind].isgoal == 1 ){ // if this vertex is goal then can end
				findgaol = 1 ;
				break ;		
			} // if
		} // if
		else{
			conutstep-- ;
			//ans.pop_back() ;
			tempS.pop_back() ;
		} // else
	} // while 
} // mis3

int main(){
	//vector<Data> datatree ;
	//int sNum = 0;
	string command ; // end cmd for while
	//int inputtemp ;
	int mis1done = 0 ; // need to done mis1 then can do mis2
	int mis2done = 0 ; // same
	vector<dataS> data ;
	vector<dataS> dataforedge ;
	string filenametemp ;
	vector< vector<int> > GDS ; // row rr  colum cc
	//int rr = 0 ; // variable for row and clum then read file in mis1 and can creat data in mis2
	//int cc = 0 ; 
	while( command != "0" ){
		cout << "[1]Mission1 or [2]Mission2 or [3]Mission3" << endl ;
		cin >> command ;				// choice which mission
		if( command == "1" ){
			cout << "Mission1 : Read file and show the vertex and edge from path" << endl ;
			fstream file ;
			string fname ;
			cout << "Please input file name.(dont need .txt) : " ;
			cin >> fname ;
			filenametemp = fname ; // for mis2
			fname = fname + ".txt" ;
			file.open( fname, ios::in ) ;
			if ( !file )
				cout << "The file is not exit!" << endl ;
			else {
				char test ;
				string test1 ;
				string test2 ;
				file.get(test) ;
				while( test != ' ' && test != '	' ) { // read to white space
					test1 = test1 + test ;
					file.get(test) ;
				} // while
				int num1 = atoi( test1.c_str() ) ; // number of line
				//rr = num1 ;
				//cout << num1 << "**" ; // num1
				file.get(test) ; // empty
				while( test != ' ' && test != '	' && test != '\n' ) { // read to white space
					test2 = test2 + test ;
					file.get(test) ;
				} // while
				int num2 = atoi( test2.c_str() ) ; // number of leter in one line
				//cc = num2 ;
				//cout << num2 << endl ; // num2
				
				file.get(test) ; 
				int conut = 0 ; // conut for ans idex
				int lineC = 1 ; // count for what line is it
				cout << "ori daat" << endl ; //*******************************
				
				while( lineC <= num1 ) { // range in num1
					int leterC = 1 ; // count for what leter is it			
					while( leterC <= num2 ) { // range in num2
						if ( test == 'E' ) {
							dataS temp ;
							temp.lline = lineC ;
							temp.lleter = leterC ;
							temp.isgoal = 0 ;
							data.push_back(temp) ;
						} // if
						else if ( test == 'O' ) {
							; // pass dont do anything 
						} // elif
						else if ( test == 'G' ) {
							dataS temp ;
							temp.lline = lineC ;
							temp.lleter = leterC ;
							temp.isgoal = 1 ;
							data.push_back(temp) ;
						} // elif
						else 
							cout << "There have not legal leter in ( "<< leterC << " , " << lineC << " )" << endl ;
						leterC++ ;
						cout << test ;
						file.get(test) ;
					} // while
					
					file.get(test) ;
					leterC = 0 ;
					cout << endl ;
					lineC++ ;
				} // while
				
				cout << "All vertex :" << endl ; // print vertex
				for( int i = 0 ; i < data.size() ; i++, conut++ ) 
					cout << "[" << conut << "] (" << data[i].lleter << "," << data[i].lline << ")" << endl ;
					
				cout << "All edge :" << endl ; // print edge and save it
				for( int i = 0 ; i < data.size() ; i++ ) { // everyone just look RIGHT and DOWN
					if ( data[i].lline == data[i+1].lline && data[i].lleter +1 == data[i+1].lleter ){ //***RIGHT
						//cout << "<" << i << "," << i+1 << ">" << endl ;
						dataS edgetemp ;
						edgetemp.lline = i ;
						edgetemp.lleter = i+1 ;
						dataforedge.push_back(edgetemp) ;
						cout << "<" << dataforedge[dataforedge.size()-1].lline << "," << dataforedge[dataforedge.size()-1].lleter << ">" << endl ;
					} //if
					//  ***********DOWN
					int downW = i+1 ;
					int cc = 0 ;
					int finddown = 0 ;
					while( downW <= data.size() && cc < num2 ){ // Up limit is leterNUM
						if ( data[i].lline +1 == data[downW].lline && data[i].lleter == data[downW].lleter )
							finddown = downW ;
						cc++ ;
						downW++ ;
					} // while
					if ( finddown != 0 ) {
						//cout << "<" << i << "," << finddown << ">" << endl ;
						dataS edgetemp ;
						edgetemp.lline = i ;
						edgetemp.lleter = finddown ;
						dataforedge.push_back(edgetemp) ;
						cout << "<" << dataforedge[dataforedge.size()-1].lline << "," << dataforedge[dataforedge.size()-1].lleter << ">" << endl ;
					} //if
				} // for

				mis1done = 1 ;
				file.close() ;
				cout << endl << "MISSION1 is done" << endl << endl ;
			}  // else
		} // if 
		else if( command == "2" ){
			if ( mis1done == 1 ) {
				cout << "Mission2 : Create graph data struct for undirected graph" << endl ;
				//vector< vector<int> > GDS(data.size()) ; // row rr  colum cc
				//for( int i = 0 ; i < data.size() ; i++ ) // TWO Dimension
					//GDS[i].resize(data.size()) ;
				
				int datasize = data.size() ;
				
				for( int i = 0 ; i < datasize ; i++ ){ // initialization
					vector<int> gg ;
					for( int j = 0 ; j < datasize ; j++ ) 
						gg.push_back(-1) ;
					GDS.push_back(gg) ;
				} // for
					
				/*for( int i = 0 ; i < datasize ; i++ ) // initialization
					for( int j = 0 ; j < datasize ; j++ ) 
						GDS[i][j] = -1 ;*/
						
				for( int i = 0 ; i < datasize ; i++ ){ // star to fill DS
					for( int j = 0 ; j < datasize ; j++ ){
						if ( dataforedge[0].lline == i && dataforedge[0].lleter == j ){
							GDS[i][j] = 1 ; // Because this DS is undirected
							GDS[j][i] = 1 ; // i to j == j to i
							dataforedge.erase( dataforedge.begin( ) ) ; // release space
						} //if
						else 
							if ( GDS[i][j] == -1 )	// Because i to j == j to i 
								GDS[i][j] = 0 ;		// if dont set this place once then it is real obstacle
					} // for
				} //for

				fstream file ; // ******write all into file
				filenametemp = "out_" + filenametemp + ".txt" ;
				file.open( filenametemp, ios::out ) ;
				file << "    " ;
				for ( int i = 0 ; i < datasize ; i++ )
					file << i << "  " ;
					
				file << endl ;
				for ( int i = 0 ; i < datasize  ; i++ ){ 
					file << i << "   " ;
					 for ( int j = 0 ; j < datasize ; j++ ){
					 	if ( GDS[i][j] == 1 )	
							file << 1 << "  " ;
					 	else	 				
							file << 0 << "  " ;
					 } // for
					 file << endl ;
				} // for ******write all into file
					
				file.close() ;
				cout << endl << filenametemp << " is create." << endl ;
				cout << "MISSION2 is done." << endl << endl ;
				mis2done = 1 ;
			} // if
			else 	
				cout << "Please do mis1 first!" << endl ;

		} // elif
		else if( command == "3" ){
			if ( mis2done == 1 ) {
				cout << "Mission3 : Find the shortest path in graph data struct" << endl ;
				//vector<int> ans ;
				//ans.push_back(0) ;
				vector<int> tempS ; // to record all need to check 
				tempS.push_back(0) ;
				data[0].isvisited = 1 ;
				int findgaol = 0 ; // if find goal then ==1
				int conutstep = 0 ; // keep the step everytime
				//int lewstep = 100000 ; // keep the smallest step
				////////////////// look right priority
				vector<int> tempS1 ; 
				tempS1.push_back(0) ;
				int findgaol1 = 0 ;
				int conutstep1 = 0 ;
				//////////////////
				
				for ( int i = 1 ; i < data.size() ; i++ ) // initialization
					data[i].isvisited = 0 ;
				mis3( tempS, data, GDS, conutstep, findgaol, 0 ) ; 

				for ( int i = 1 ; i < data.size() ; i++ ) 
					data[i].isvisited = 0 ;
				mis3( tempS1, data, GDS, conutstep1, findgaol1, 1 ) ; // look right priority
				
				cout << conutstep << "1" << endl  ;
				cout << conutstep1 << "2" << endl  ;
				/*while ( !tempS.empty() ){
					int findnext = tempS[tempS.size()-1] ; // take the TOP
					int successfind = -1 ; // where can we go (index of data)
					//cout << "in" ;
					for ( int i = data.size()-1 ; i > 0 ; i-- ){ // find the next root we can go
						//cout << i << "(1)" ;
						//cout << findnext<< "*" ;
						//cout << &GDS[0][0] ;
						//cout << findnext<< "*" ;
						if ( GDS[findnext][i] == 1 ){ // P"findnext" to P"i"  has a root
							if ( data[i].isvisited == 0 ){
								successfind = i  ;
								break ;
							} // if
						} // if
					} // for
					
					//cout << "in" ;
					if ( successfind != -1 ){ // have some where we can go 
						conutstep++ ;
						data[successfind].isvisited = 1 ;
						ans.push_back(successfind) ;
						tempS.push_back(successfind) ;
						if ( data[successfind].isgoal == 1 ){ // if this vertex is goal then can end
							findgaol = 1 ;
							break ;
							
						} // if
					} // if
					else{
						conutstep-- ;
						ans.pop_back() ;
						tempS.pop_back() ;
					} // else
			
				} // while */

				if ( findgaol == 1 || findgaol1 == 1 ){ 	// if find the goal then print
					if ( conutstep <= conutstep1 )
						for ( int i = 0 ; i < tempS.size() ; i++ )
								cout << "[" << tempS[i] << "] (" << data[tempS[i]].lleter << "," << data[tempS[i]].lline << ")" << endl ;
					else
						for ( int i = 0 ; i < tempS1.size() ; i++ )
								cout << "[" << tempS1[i] << "] (" << data[tempS1[i]].lleter << "," << data[tempS1[i]].lline << ")" << endl ;

				} // if
				else
					cout << "Can not find the goal." << endl ;
				
				
				//ans.clear() ;
				//ans.push_back(0) ;
				tempS.clear() ;
				tempS.push_back(0) ;
				tempS1.clear() ;
				tempS1.push_back(0) ;
				data[0].isvisited = 1 ;
				findgaol = 0 ; 
				conutstep = 0 ;
				findgaol1 = 0 ; 
				conutstep1 = 0 ;
				//lewstep = 100000 ;
				mis1done = 0 ; 
				mis2done = 0 ;
				data.clear()  ;
				dataforedge.clear()  ;
				GDS.clear()  ;
				cout << endl << "MISSION3 is done." << endl ;
			} // if
			else
				cout << "Please do mis2 first!" << endl ;
		} // elif
		else { // only 1.2.3
			cout << "It is not legal number" << endl ;
		} // elif
			
		//mis1done = 0 ;
		//mis2done = 0 ;
		cout << endl << "[0]Quit or [Any other]continue?" << endl ;
		cin >> command ;
		if( command == "0" )
			return 0;
	} // while
	
} // main
