#include<iostream>
#include<vector>
#include<cmath>
//*************************************DISCLAIMER****************************
//it doesnt work
using namespace std;

int distance(int x1,int y1,int x2,int y2){
	return(ceil(sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1))));
}

bool solvemaze(int x,int y,vector<vector<int>> maze, vector<vector<int>> visited){
	int directions[8][2]={{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1}};
	int low;
	int lowdir[2]={0,0};
	bool vis;
	for(int d=0;d<8;d++){
		vis=false;
		if(x+directions[d][0]>=0&&x+directions[d][0]<maze[0].size()&&y+directions[d][1]>=0&&y+directions[d][1]<maze.size()){//if the square we need to check is on the board
			for(int p=0;p<visited.size();p++){//if the square hasnt been visited
				if(visited[p][0]==x+directions[d][0]&&visited[p][1]==y+directions[d][1]){
					vis=true;
				}
			}
			if(!vis){
				if(maze[y+directions[d][1]][x+directions[d][0]]==-1){//check if endpoint, print x,y coor
					for(int z=0;z<visited.size();z++){
						cout<<"x: "<<visited[z][0]<<" y: "<<visited[z][1]<<endl;
					}
					return(true);
				}
				if(maze[y+directions[d][1]][x+directions[d][0]]<=low){//get the lowest direction value
					low=maze[y+directions[d][1]][x+directions[d][0]];
					lowdir[0]=directions[d][0];
					lowdir[1]=directions[d][1];
				}
			}
		}
	}
	if(lowdir[0]!=0&&lowdir[1]!=0){//if there is a low direction, add to visited and solvemaze() at new point
		visited.push_back({x,y});
		return(solvemaze(x+lowdir[0],y+lowdir[1],maze,visited));
	}
	return(false);
}

int main(){
	vector<vector<int>> visited;
	vector<vector<int>> maze={{0,5,0,0,0},
							  {0,5,0,0,0},
							  {0,5,0,0,0},
							  {0,5,0,0,0},
							  {0,0,0,0,-1}};
	if(solvemaze(0,0,maze,visited)){
		cout<<"yeet"<<endl;
	}
}