#include<iostream>
#include<stdio.h>
#include<string>
#include <vector>
#include<stdint.h>
#include<stdlib.h>
using namespace std;

enum color{
	BLUE_WHITE,//0
	YELLOW_BLACK,//1
	WHITE_BLACK,//2
	BLACK_WHITE,//3
	RED_WHITE,//4
	WHITE_RED_BLACK,//4
	GREEN_WHITE//5
};
enum shape{
	SQUARE,
	CIRCLE,
	RECTANGLE_W,
	RECTANGLE_L,
	HEXAGON,
	DIAMOND
};

string colorNames[]={"BLUE_WHITE",//0
						"YELLOW_BLACK",//1
						"WHITE_BLACK",//2
						"BLACK_WHITE",//3
						"RED_WHITE",//4
						"WHITE_RED_BLACK",
						"GREEN_WHITE"//5
						};
						
string signShape[] ={"SQUARE",
					"CIRCLE",
					"RECTANGLE_W",
					"RECTANGLE_L",
					"HEXAGON",
					"DIAMOND"};
					
class sign{
	public:
	
		string name;
		color col;
		shape sh;
		
		//float sizeFactor;//
		uint8_t location; //Top=1, Middle=2, Bottom=3, Left=1, Middle=2, Right=3, use two hex digits
		sign(string n, color c, shape s, uint8_t l){
			this->name= n;
			this->col=c;
			this->sh = s;
			this->location=l;
		}
		sign(){
			//empty constructor
		}
	friend ostream & operator << (ostream &out, sign &s);
};

ostream & operator << (ostream &out, sign &s){
	
	out<<"NAME: "<<s.name<<" COLOR: "<<colorNames[s.col]<<" SHAPE: "<<signShape[s.sh]<<" LOCATION: "<<hex<<int(s.location)<<endl;
	return out;
}
int main(){
	string name,color, shape, location;
	vector <sign *> signList;
	
	sign stop("STOP",RED_WHITE, HEXAGON, 23);	
	signList.push_back(&stop);
	
	sign disabled("DISABLED_PARKING",BLUE_WHITE, SQUARE,22);
	signList.push_back(&disabled);
	
	sign railCrossing("RAIL_CROSSING",YELLOW_BLACK, CIRCLE, 23);
	signList.push_back(&railCrossing);
	
	sign bikeLane("BIKE_LANE",WHITE_BLACK, RECTANGLE_W, 23);
	signList.push_back(&bikeLane);
	
	sign oneWay("ONE_WAY", BLACK_WHITE, RECTANGLE_W, 23);
	signList.push_back(&oneWay);
	
	sign leftUTurn("LEFT_U_TURN",WHITE_BLACK, SQUARE, 21);
	signList.push_back(&leftUTurn);
	
	sign doNotEnter("DO_NOT_ENTER",RED_WHITE, SQUARE, 23);
	signList.push_back(&doNotEnter);
	
	sign pedestrian("PEDESTRIAN",YELLOW_BLACK,DIAMOND, 23);
	signList.push_back(&pedestrian);
	
	sign noLeftTurn("NO_LEFT_TURN",WHITE_RED_BLACK, SQUARE, 21);
	signList.push_back(&noLeftTurn);
	
	sign speedLimit("SPEED_LIMIT",WHITE_BLACK, RECTANGLE_L, 23);
	signList.push_back(&speedLimit);
	while(1){
	
	    cout<<"Enter the shape of the sign OR enter q to exit"<<endl;
	    cout<< "Possible values:SQUARE CIRCLE RECTANGLE_W RECTANGLE_L HEXAGON DIAMOND"<<endl;
	    cin>>shape;
	    if(shape=="q"){
	        break;
	    }
	    cout<<"Enter the color of the sign as Background_foreground "<<endl;
	    cout<< "Possible values:BLUE_WHITE YELLOW_BLACK,WHITE_BLACK,BLACK_WHITE,RED_WHITE,WHITE_RED_BLACK,GREEN_WHITE"<<endl;
	    cin>>color;
	
	    cout<<"Enter the location of the sign "<<endl;
	    cout<<"Possible values:Top=1, Middle=2, Bottom=3, Left=1, Middle=2, Right=3, use two digits"<<endl;
	    cin>>location;
	    //cout<<atoi(location.c_str())<<endl;
	
	    bool flag=false;
	
	    //temp=toupper(*temp.c_str());
	    for(vector<sign *>::iterator i= signList.begin(); i!= signList.end(); i++ ){
		    sign t;
		    t=**i;
		    if(shape.compare(signShape[t.sh])==0)
		    {
		        //cout<<"Shape match"<<endl;
		        //cout<<color<<" "<< signShape[t.col]<<endl;
		        if(color.compare(colorNames[t.col])==0)
		        {
		            //cout<<"Color match"<<endl;
		            if(atoi(location.c_str())==t.location)
		            {
		            flag=true;
		            cout<<t.name<<endl;
			        break;
			        }
		        }
			
		    }
	    }
	    if(!flag){
	        cout<<"Sign not found"<<endl;
	    }
	    //sign streetName();
	    
    }
	return 0;
}
