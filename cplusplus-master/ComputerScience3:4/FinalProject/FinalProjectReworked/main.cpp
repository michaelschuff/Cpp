#include<iostream>
#include<vector>
#include<SFML/Graphics.hpp>
#include<ResourcePath.hpp>
using namespace std;
using namespace sf;
class ChessPiece{//A class piece that hold the texture sprite and color for each piece
public:
	Texture texture;
	Sprite sprite;
	ChessPiece(string,int,int);
};
ChessPiece::ChessPiece(string image,int piece,int color){//Constructor function basically divides up the sprite sheet image i have of the pieces
	if(!texture.loadFromFile(resourcePath()+image)){
		cout<<"Texture not working"<<endl;
	}
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(piece*1000/3,color*1000/3,1000/3,1000/3));
	sprite.setScale(.3,.3);
}
string findwb(string piece){//Function that just takes any string on the board and finds out if it is white, black or empty
	string white[6]={"WK","WQ","WB","WN","WR","WP"};//white pieces
	string black[6]={"BK","BQ","BB","BN","BR","BP"};//blackpieces
	for(int i=0;i<6;i++){
		if(piece==white[i]){
			return("W");//if string is in white pieces, return w
		}
		if(piece==black[i]){
			return("B");//if string is in white pieces, return b
		}
	}
	return(" ");//if string is not in either, return a space
}
string changecolor(string color){//changes the color, which keeps track of the turn
	if(color=="W"){
		return("B");
	}
	return("W");
}
bool kingincheck(string board[8][8],string color){//function that takes in the board, and a color (white or black) and returns if the color king is in check
	int horizontal[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};//list of horizontal directions that increment by one, assuming the board is a coordinate grid
	int diagonal[4][2] = {{1,1},{1,-1},{-1,-1},{-1,1}};//same but diagonal
	int knight[8][2] = {{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1},{-2,1},{-1,2}};//same but is the knights legal moves
	int kx,ky,changex=0,changey=0;//kx,ky is the kinds starting position, changex,y keeps track of how many times you have added the direction in the horizontal, diagonal etc
	string oppo;//string is the opposite color of who's turn
	for(int y=0;y<8;y++){//this loop goes through the board and finds out the x,y position of the king
		for(int x=0;x<8;x++){
			if(board[y][x]==color+"K"){
				kx=x;
				ky=y;
			}
		}
	}
	if(color=="W"){//Set the opposite color
		oppo="B";
		if(board[ky-1][kx+1]=="BP"||board[ky-1][kx-1]=="BP"){//because pawns move in one direction based on what color you are, I check here if there is a panw on the board that is checking the king
			return(true);
		}
	}
	else{
		oppo="W";//for the black side
		if(board[ky+1][kx+1]=="WP"||board[ky+1][kx-1]=="WP"){
			return(true);
		}
	}
	for(int h=0;h<4;h++){//this goes through each horizontal direction
		while((ky+changey+horizontal[h][1]>=0)&&(ky+changey+horizontal[h][1]<=7)&&(kx+changex+horizontal[h][0]>=0)&&(kx+changex+horizontal[h][0]<=7)){//this checks that the next square we are going to check is on the board, so we dont get an index error
			changex+=horizontal[h][0];//change x,y get incremented based on the direction
			changey+=horizontal[h][1];
			if(board[ky+changey][kx+changex]==oppo+"R"||board[ky+changey][kx+changex]==oppo+"Q"){//if the square we are checking has an opposite color rook or queen on it, the king is in check
				return(true);
			}
			if(board[ky+changey][kx+changex]!="  "){//if the square is not an empty piece, because pieces cannot attack through pieces, break out of the loop and move on to the next direction
				break;
			}
		}
		changex=0;//reset changex,y
		changey=0;
	}
	for(int d=0;d<4;d++){//same as abovw except checking for bishops and queens and uses diagonal directions
		while((ky+changey+diagonal[d][1]>=0)&&(ky+changey+diagonal[d][1]<=7)&&(kx+changex+diagonal[d][0]>=0)&&(kx+changex+diagonal[d][0]<=7)){
			changex+=diagonal[d][0];
			changey+=diagonal[d][1];
			if(board[ky+changey][kx+changex]==oppo+"B"||board[ky+changey][kx+changex]==oppo+"Q"){
				return(true);
			}
			else if(board[ky+changey][kx+changex]!="  "){
				break;
			}
		}
		changex=0;
		changey=0;
	}
	for(int k=0;k<8;k++){//this goes throught the knight directions. The way knights move, we dont need a change x,y, idk how to describe it
		if((ky+knight[k][1]>=0)&&(ky+knight[k][1]<=7)&&(kx+knight[k][0]>=0)&&(kx+knight[k][0]<=7)){//make sure the square we are checking is on the board
			if(board[ky+knight[k][1]][kx+knight[k][0]]==oppo+"N"){//if the square has a knight, return true
				return(true);
			}
		}
	}
	for(int alld=0;alld<4;alld++){//this checks each horizontal and diagonal directions once, if there is a king. This is important for getting legal moves
		if((ky+horizontal[alld][1]>=0)&&(ky+horizontal[alld][1]<=7)&&(ky+horizontal[alld][0]>=0)&&(ky+horizontal[alld][0]<=7)){//if its on the board
			if(board[ky+horizontal[alld][1]][kx+horizontal[alld][0]]==oppo+"K"){//if the piece is an opposite king
				return(true);
			}
		}
		if((ky+diagonal[alld][1]>=0)&&(ky+diagonal[alld][1]<=7)&&(ky+diagonal[alld][0]>=0)&&(ky+diagonal[alld][0]<=7)){
			if(board[ky+diagonal[alld][1]][kx+diagonal[alld][0]]==oppo+"K"){//same but diagonal
				return(true);
			}
		}
	}
	return(false);//return false if it gets through everything
}
void movepiece(string board[8][8],int piecex,int piecey,int squarex,int squarey){//function that acutally moves the piece
	if((board[piecey][piecex]=="WK"||board[piecey][piecex]=="BK")&&squarex==6&&piecex==4){//this checks if the king is castling. If it is, this moves the rook
		board[piecey][5]=findwb(board[piecey][piecex])+"R";
		board[piecey][7]="  ";
	}
	else if((board[piecex][piecey]=="WK"||board[piecex][piecey]=="BK")&&squarex==2&&piecex==4){//this checks the other castling posibility and moves the rook
		cout<<"Queenside castle"<<endl;
		board[piecey][3]=findwb(board[piecey][piecex])+"R";
		board[piecey][0]="  ";
	}
	else if(board[piecey][piecex]=="WP"&&board[squarey][squarex]=="  "&&board[squarey+1][squarex]=="BP"){//this checks if the move is an en passant move, and gets rid of the pawn
		board[squarey+1][squarex]="  ";
	}
	else if(board[piecey][piecex]=="BP"&&board[squarey][squarex]=="  "&&board[squarey-1][squarex]=="WP"){//same but for the other color
		board[squarey-1][squarex]="  ";
	}
	board[squarey][squarex]=board[piecey][piecex];//this is the basical move function, the square you are moving to become the piece, and the square you moved from becomes blank
	board[piecey][piecex]="  ";
}
vector<vector<int>> changenotation(string board[8][8],vector<vector<int>> notation,vector<int> lastmove,string textpieces[12],int piecex,int piecey,int squarex,int squarey){//this changes the notation, which keeps track of the game in the form of a 2d vector, which has the square you moved from x and y, the square you moved to x and y, and which piece you moved (I dont actually used the which piece you moved, but it can be helpful if you want to show the notation on the screen)
	lastmove[0]=piecex;//get all the variables we need in a vector
	lastmove[1]=piecey;
	lastmove[2]=squarex;
	lastmove[3]=squarey;
	for(int i=0;i<12;i++){
		if(board[piecey][piecex]==textpieces[i]){
			lastmove[4]=i;
		}
	}
	notation.push_back(lastmove);//add it to the vector
	return(notation);//return the notation
}
vector<vector<int>> addmove(vector<vector<int>> legalmoves,int piecex,int piecey,int squarex,int squarey){//this adds a move to the vector of legal moves, very similar to the change notation function
	vector<int> move={piecex,piecey,squarex,squarey};
	legalmoves.push_back(move);
	return(legalmoves);
}
vector<vector<int>> legalmovesincheck(string board[8][8],vector<vector<int>> legalmoves,int piecex,int piecey,int squarex,int squarey){//this checks if the legal move you want to add, when you move the piece, doenst leave your king in check
	string tempboard[8][8];//copy of the board
	for(int y=0;y<8;y++){
		for(int x=0;x<8;x++){
			tempboard[y][x]=board[y][x];
		}
	}
	if((tempboard[piecey][piecex]=="WK"||tempboard[piecey][piecex]=="BK")&&squarex==6&&piecex==4){
		tempboard[piecey][5]="WR";
		tempboard[piecey][7]="  ";
	}
	else if((tempboard[piecex][piecey]=="WK"||tempboard[piecex][piecey]=="BK")&&squarex==2&&piecex==4){
		tempboard[piecey][3]="WR";
		tempboard[piecey][0]="  ";
	}
	else if(tempboard[piecey][piecex]=="WP"&&tempboard[squarey][squarex]=="  "&&tempboard[squarey+1][squarex]=="BP"){
		tempboard[squarey+1][squarex]="  ";
	}
	else if(tempboard[piecey][piecex]=="BP"&&tempboard[squarey][squarex]=="  "&&tempboard[squarey-1][squarex]=="WP"){
		tempboard[squarey-1][squarex]="  ";
	}
	tempboard[squarey][squarex]=tempboard[piecey][piecex];
	tempboard[piecey][piecex]="  ";//move the piece on the temporary board, same code as the movepiece funciton
	if(!kingincheck(tempboard,findwb(tempboard[squarey][squarex]))){//check if the king is in check
		legalmoves=addmove(legalmoves,piecex,piecey,squarex,squarey);//send the move to the function above
	}
	return(legalmoves);
}
vector<vector<int>> castling(string board[8][8],vector<vector<int>> legalmoves,string lr,string color){//this checks if the king can castle, but only checks if the king is in check. The other requirements for castling are held in the main king legal moves function
	string tempboard[8][8];//temporary board
	for(int y=0;y<8;y++){
		for(int x=0;x<8;x++){
			tempboard[y][x]=board[y][x];
		}
	}
	int ncolor=0;//this is a number color, which is 0 or 7, based on what color. Basically lets us not have to write the same code with the numbers changed
	if(color=="W"){
		ncolor=7;
	}
	if(!kingincheck(board,color)){//if the king isnt in check
		if(lr=="L"){//if he passed all the requirements for calstling to the left
			tempboard[ncolor][3]=tempboard[ncolor][4];
			tempboard[ncolor][4]="  ";//move the king one to the left
			if(!kingincheck(tempboard,color)){//if hes not in check
				tempboard[ncolor][2]=tempboard[ncolor][3];//move him again
				tempboard[ncolor][3]="  ";
				if(!kingincheck(tempboard,color)){//if hes not in check
					legalmoves=addmove(legalmoves,4,ncolor,2,ncolor);//add castling to the left as a legal move
				}
			}
		}
		if(lr=="R"){//basically the same code as the above, but it check to the right
			tempboard[ncolor][5]=tempboard[ncolor][4];
			tempboard[ncolor][4]="  ";
			if(!kingincheck(tempboard,color)){
				tempboard[ncolor][6]=tempboard[ncolor][5];
				tempboard[ncolor][5]="  ";
				if(!kingincheck(tempboard,color)){
					legalmoves=addmove(legalmoves,4,ncolor,6,ncolor);
				}
			}
		}
	}
	return(legalmoves);
}
vector<vector<int>> pawnlegalmoves(string board[8][8],vector<vector<int>> notation,vector<vector<int>> legalmoves,int piecex,int piecey){//gets the legal pawn moves if the piece you have selected is a pawn
	string color=findwb(board[piecey][piecex]);//get the color of the piece you have selected
	if(color=="W"){//pawns move differently based on color so we have to have 2 seperate legal move finders
		if(board[piecey-1][piecex]=="  "){// if the square in front of it is empty
			legalmoves=legalmovesincheck(board,legalmoves,piecex,piecey,piecex,piecey-1);//and when you move the piece it isnt in check, add the move
			if(board[piecey-2][piecex]=="  "&&piecey==6){//if the square 2 squares in front isnt occupied and the pawn is on its starting square, then it can move two squares
				legalmoves=legalmovesincheck(board,legalmoves,piecex,piecey,piecex,piecey-2);
			}
		}
		if(piecex>0){//if it isnt on the left edge, check if it can take a piece diagonally to the left
			if(findwb(board[piecey-1][piecex-1])=="B"){//if that square is black
				legalmoves=legalmovesincheck(board,legalmoves,piecex,piecey,piecex-1,piecey-1);// if its not in check move the piece
			}
			if(notation[notation.size()-1][0]==piecex-1&&notation[notation.size()-1][1]==1&&notation[notation.size()-1][2]==piecex-1&&notation[notation.size()-1][3]==3&&piecey==3&&board[piecey][piecex-1]=="BP"){//complicated if statement that just checks if you can take a pawn using en passant
				legalmoves=legalmovesincheck(board,legalmoves,piecex,piecey,piecex-1,piecey-1);// if its not in check, move the piece
			}
		}
		if(piecex<7){//same code as above, but checks the right side
			if(findwb(board[piecey-1][piecex+1])=="B"){
				legalmoves=legalmovesincheck(board,legalmoves,piecex,piecey,piecex+1,piecey-1);
			}
			if(notation[notation.size()-1][0]==piecex+1&&notation[notation.size()-1][1]==1&&notation[notation.size()-1][2]==piecex+1&&notation[notation.size()-1][3]==3&&piecey==3&&board[piecey][piecex+1]=="BP"){
				legalmoves=legalmovesincheck(board,legalmoves,piecex,piecey,piecex+1,piecey-1);
			}
		}
	}
	else{//same code as above but for black pawns
		if(board[piecey+1][piecex]=="  "){
			legalmoves=legalmovesincheck(board,legalmoves,piecex,piecey,piecex,piecey+1);
			if(board[piecey+2][piecex]=="  "&&piecey==1){
				legalmoves=legalmovesincheck(board,legalmoves,piecex,piecey,piecex,piecey+2);
			}
		}
		if(piecex>0){
			if(findwb(board[piecey+1][piecex-1])=="W"){
				legalmoves=legalmovesincheck(board,legalmoves,piecex,piecey,piecex-1,piecey+1);
			}
			if(notation[notation.size()-1][0]==piecex-1&&notation[notation.size()-1][1]==6&&notation[notation.size()-1][2]==piecex-1&&notation[notation.size()-1][3]==4&&piecey==4&&board[piecey][piecex-1]=="WP"){
				legalmoves=legalmovesincheck(board,legalmoves,piecex,piecey,piecex-1,piecey+1);
			}
		}
		if(piecex<7){
			if(findwb(board[piecey+1][piecex+1])=="W"){
				legalmoves=legalmovesincheck(board,legalmoves,piecex,piecey,piecex+1,piecey+1);
			}
			if(notation[notation.size()-1][0]==piecex+1&&notation[notation.size()-1][1]==6&&notation[notation.size()-1][2]==piecex+1&&notation[notation.size()-1][3]==4&&piecey==4&&board[piecey][piecex+1]=="WP"){
				legalmoves=legalmovesincheck(board,legalmoves,piecex,piecey,piecex+1,piecey+1);
			}
		}
	}
	return(legalmoves);
}
bool promotion(string board[8][8]){//this checks if we need to run a promotion program
	for(int x=0;x<8;x++){
		if(board[0][x]=="WP"||board[7][x]=="BP"){//if there is a pawn at the end of the board, return true
			return(true);
		}
	}
	return(false);
}
vector<vector<int>> knightlegalmoves(string board[8][8],vector<vector<int>> legalmoves,int piecex,int piecey){//gets knights legal moves
	int knightmoves[8][2]={{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1},{-2,1},{-1,2}};//list of knight move directions assuming board is a coordinate grid
	for(int k=0;k<8;k++){// for each direction
		if(piecex+knightmoves[k][0]>=0&&piecex+knightmoves[k][0]<=7&&piecey+knightmoves[k][1]>=0&&piecey+knightmoves[k][1]<=7){//if the square is on the board
			if(findwb(board[piecey][piecex])!=findwb(board[piecey+knightmoves[k][1]][piecex+knightmoves[k][0]])){//if the square we are checking is empty of has a opposite color piece on it
				legalmoves=legalmovesincheck(board,legalmoves,piecex,piecey,piecex+knightmoves[k][0],piecey+knightmoves[k][1]);// add the move if you arent in check
			}
		}
	}
	return(legalmoves);
}
vector<vector<int>> rooklegalmoves(string board[8][8],vector<vector<int>> legalmoves,int piecex,int piecey){//gets legal rook moves
	int rookmoves[4][2]={{0,1},{1,0},{0,-1},{-1,0}};//rook move directions
	int changex=0,changey=0;
	for(int r=0;r<4;r++){
		while(piecex+changex+rookmoves[r][0]>=0&&piecex+changex+rookmoves[r][0]<8&&piecey+changey+rookmoves[r][1]>=0&&piecey+changey+rookmoves[r][1]<8){//if the square you are checking is on the board
			changex+=rookmoves[r][0];//increment change x,y
			changey+=rookmoves[r][1];
			if(findwb(board[piecey][piecex])!=findwb(board[piecey+changey][piecex+changex])){//if the square you are checking is empty or of opposite color
				legalmoves=legalmovesincheck(board,legalmoves,piecex,piecey,piecex+changex,piecey+changey);//add the moves
			}
			if(board[piecey+changey][piecex+changex]!="  "){//if the square isnt empty, meaning the rook cannot move to any square beyond this one (because pieces cant jump over pieces), break out of the loop
				break;
			}
		}
		changex=0;//reset changex,y
		changey=0;
	}
	return(legalmoves);
}
vector<vector<int>> bishoplegalmoves(string board[8][8],vector<vector<int>> legalmoves,int piecex,int piecey){// same code as above but for diagonal moves for bishops
	int bishopmoves[4][2]={{1,1},{1,-1},{-1,-1},{-1,1}};
	int changex=0,changey=0;
	for(int b=0;b<4;b++){
		while(piecex+changex+bishopmoves[b][0]>=0&&piecex+changex+bishopmoves[b][0]<8&&piecey+changey+bishopmoves[b][1]>=0&&piecey+changey+bishopmoves[b][1]<8){
			changex+=bishopmoves[b][0];
			changey+=bishopmoves[b][1];
			if(findwb(board[piecey][piecex])!=findwb(board[piecey+changey][piecex+changex])){
				legalmoves=legalmovesincheck(board,legalmoves,piecex,piecey,piecex+changex,piecey+changey);
			}
			if(board[piecey+changey][piecex+changex]!="  "){
				break;
			}
		}
		changex=0;
		changey=0;
	}
	return(legalmoves);
}
vector<vector<int>> queenlegalmoves(string board[8][8],vector<vector<int>> legalmoves,int piecex,int piecey){//queen legal moves are easy, just get the legal moves for the rook and bishop
	legalmoves=rooklegalmoves(board,legalmoves,piecex,piecey);
	legalmoves=bishoplegalmoves(board,legalmoves,piecex,piecey);
	return(legalmoves);
}
vector<vector<int>> kinglegalmoves(string board[8][8],vector<vector<int>> legalmoves,vector<vector<int>> notation,int piecex,int piecey){//gets king legal moves
	int directions[8][2]={{0,1},{1,0},{0,-1},{-1,0},{1,1},{1,-1},{-1,-1},{-1,1}};//each horzintla vertical and diagonal direction
	bool left=true,right=true;// bools to tell if the king can castle to the right and/or the left
	legalmoves.clear();//clear any legal moves. For some reason I still don't know, even though in the function right before this I clear the legal moves, I am getting extra moves
	for(int d=0;d<8;d++){//for each direction
		if(piecex+directions[d][0]>=0&&piecex+directions[d][0]<=7&&piecey+directions[d][1]>=0&&piecey+directions[d][1]<=7){//if its on the board
			if(findwb(board[piecey][piecex])!=findwb(board[piecey+directions[d][1]][piecex+directions[d][0]])){//if the square is empty or of opposite color
				legalmoves=legalmovesincheck(board,legalmoves,piecex,piecey,piecex+directions[d][0],piecey+directions[d][1]);//if you arent in check afterwards, add the legal move
			}
		}
	}
	if(board[piecey][piecex]=="WK"){//if the piece is white
		for(int n=0;n<notation.size();n++){//this basically says if you moved your rook or king before, you cant castle
			if(notation[n][0]==4&&notation[n][1]==7){
				left=false;
				right=false;
				break;
			}
			if(notation[n][0]==0&&notation[n][1]==7){
				left=false;
			}
			if(notation[n][0]==7&&notation[n][1]==7){
				right=false;
			}
		}
		if(left&&board[7][3]=="  "&&board[7][2]=="  "&&board[7][1]=="  "){//this checks if the square between castling are empty
			legalmoves=castling(board,legalmoves,"L","W");
		}
		if(right&&board[7][5]=="  "&&board[7][6]=="  "){// same but for the other side
			legalmoves=castling(board,legalmoves,"R","W");
		}
	}
	else{//if the piece is black, same code but different values
		for(int n=0;n<notation.size();n++){
			if(notation[n][0]==4&&notation[n][1]==0){
				left=false;
				right=false;
				break;
			}
			if(notation[n][0]==0&&notation[n][1]==0){
				left=false;
			}
			if(notation[n][0]==7&&notation[n][1]==0){
				right=false;
			}
		}
		if(left&&board[0][3]=="  "&&board[0][2]=="  "&&board[0][1]=="  "){
			legalmoves=castling(board,legalmoves,"L","B");
		}
		if(right&&board[0][5]=="  "&&board[0][6]=="  "){
			legalmoves=castling(board,legalmoves,"R","B");
		}
	}
	return(legalmoves);
}
vector<vector<int>> getlegalmoves(string board[8][8],vector<vector<int>> legalmoves,vector<vector<int>> notation,int piecex,int piecey){// this takes in the piece you have selected
	legalmoves.clear();
	string piece=board[piecey][piecex];//set the piece
	if(piece=="WP"||piece=="BP"){//if it piece is == n, then send it to function that finds piece n's legal moves
		legalmoves=pawnlegalmoves(board,notation,legalmoves,piecex,piecey);
	}
	else if(piece=="WR"||piece=="BR"){
		legalmoves=rooklegalmoves(board,legalmoves,piecex,piecey);
	}
	else if(piece=="WN"||piece=="BN"){
		legalmoves=knightlegalmoves(board,legalmoves,piecex,piecey);
	}
	else if(piece=="WB"||piece=="BB"){
		legalmoves=bishoplegalmoves(board,legalmoves,piecex,piecey);
	}
	else if(piece=="WQ"||piece=="BQ"){
		legalmoves=queenlegalmoves(board,legalmoves,piecex,piecey);
	}
	else if(piece=="WK"||piece=="BK"){
		legalmoves=kinglegalmoves(board,notation,legalmoves,piecex,piecey);
	}
	return(legalmoves);
}
bool checkmate(string board[8][8],vector<vector<int>> notation,string color){//check if the game is over
	vector<vector<int>> checkmatemoves;//new vector of legal moves, if it is empty when we get all the legal moves, than the person cannot
	for(int y=0;y<8;y++){
		for(int x=0;x<8;x++){// go through the board
			if(findwb(board[y][x])==color){//if the square has one of your pieces on it
				checkmatemoves=getlegalmoves(board,checkmatemoves,notation,x,y);//get the legal moves for that piece and put it in checkmate moves
				if(checkmatemoves.size()>0){//if you have at least one possible legal move then you arent in checkmate
					return(false);
				}
			}
		}
	}
	return(true);//if you have no legal moves, you are in checkmate
}
void printboardsfml(string board[8][8],RenderWindow &window,ChessPiece sfmlPieces[12],string textPieces[12],int piecex,int piecey,bool pieceup,bool pieceselected,ChessPiece sfmlpieces[12],vector<vector<int>> legalmoves,int nturn,int nfix){
	//This meaty, thicc block of text makes all the rectangles and circles that tell you what piece is selected, if you are in check, what moves you can make et
	RectangleShape lightsquare(Vector2f(100,100));//creates a light brown square for the checkerdboard pattern
	lightsquare.setFillColor(Color(222,184,135));//set the color
	RectangleShape darksquare(Vector2f(100,100));//dark square
	darksquare.setFillColor(Color(139,69,19));//set the color
	RectangleShape highlightedsquare(Vector2f(100,100));//selected piece square
	highlightedsquare.setFillColor(Color(255,255,0));//set the color
	RectangleShape inchecksquare(Vector2f(100,100));//in check square color
	inchecksquare.setFillColor(Color(255,0,0));//set the color
	CircleShape possiblemove(25);//a dot that appears over square that are legal moves for the selected piece
	possiblemove.setFillColor(Color(127,127,127));//set the color to gray
	possiblemove.setOrigin(-25,-25);//set the origin to the middle of the circle
	RectangleShape tlb(Vector2f(2,20));//this creates the possible move if the move you want to make is taking a piece, the basical formula for the names is the vertical position, top(t) or bottom(b), then the horizontal position left(l)or right(r), and then, because there are two rectangles per corner, if it is on the higher side or the lower side, top(t), bottom(b).
	tlb.setFillColor(Color(0,0,0));
	RectangleShape tlt(Vector2f(20,2));
	tlt.setFillColor(Color(0,0,0));
	RectangleShape trb(Vector2f(2,20));
	trb.setFillColor(Color(0,0,0));
	trb.setOrigin(-98,0);
	RectangleShape trt(Vector2f(20,2));
	trt.setFillColor(Color(0,0,0));
	trt.setOrigin(-80,0);
	RectangleShape blb(Vector2f(20,2));
	blb.setFillColor(Color(0,0,0));
	blb.setOrigin(0,-98);
	RectangleShape blt(Vector2f(2,20));
	blt.setFillColor(Color(0,0,0));
	blt.setOrigin(0,-80);
	RectangleShape brb(Vector2f(20,2));
	brb.setFillColor(Color(0,0,0));
	brb.setOrigin(-80,-98);
	RectangleShape brt(Vector2f(2,20));
	brt.setFillColor(Color(0,0,0));
	brt.setOrigin(-98,-80);
	for(int y=0;y<8;y++){//goes through each position on the board
		for(int x=0;x<8;x++){
			if(y%2==x%2){//this creates the checkerdboard pattern. I actually figured this out in a chess camp, we were doing an activity that improved visualizing the board in your head. The instructor would say a square, like c6, and we would have to tell them if it was a light or dark square. There was a formula for this that said if the rank is odd and the column is odd, or the rank is even and the column is even, then it is a light square, otherwise its a dark square
				lightsquare.setPosition(100*(nturn-nfix*x),100*(nturn-nfix*y));//sets the position of the light square. The (nturn-nfix*(x or y))is used throught this program. Nturn switches between 7 and zero. If nturn is 7, nfix is 1. If nturn is zero, nfix is -1. This means that depending on what nturn is, which is based on whos turn it is, each x and y value will either be their true x and y values (in the case of nturn(0) - nfix(-1)*(x or y). The negatives cancel.), or they will be 7- their x and y values (in the case of nturn(7) - nfix(1)*(x or y)). This has the effect of flipping the board when it is black move.
				window.draw(lightsquare);
			}
			else{
				darksquare.setPosition(100*(nturn-nfix*x),100*(nturn-nfix*y));//dark square set position
				window.draw(darksquare);
			}
			if((board[y][x]=="WK"&&kingincheck(board,"W"))||(board[y][x]=="BK"&&kingincheck(board,"B"))){//if the king is in check, draw the in check square on the king
				inchecksquare.setPosition(100*(nturn-nfix*x),100*(nturn-nfix*y));
				window.draw(inchecksquare);
			}
			if(y==piecey&&x==piecex&&!pieceup&&pieceselected){//draw the pieceselected square on the square you have selected
				highlightedsquare.setPosition(100*(nturn-nfix*x),100*(nturn-nfix*y));
				window.draw(highlightedsquare);
			}
			for(int i=0;i<12;i++){//this loop draws the actual pieces (it is after the other ones so it appear son top. This for loop goes through each text piece
				if(board[y][x]==textPieces[i]){//If the board at x,y position is equal to text piece[i]
					if(!(y==piecey&&x==piecex&&pieceup)){//if the piece isnt picked up. (because if the piece is picked up, we are going to draw it at the x,y position of the mouse
						sfmlPieces[i].sprite.setPosition(100*(nturn-nfix*x),100*(nturn-nfix*y));//draw the sprite at the position. Note that sfmlpieces and text pieces are ordered the same, so text[0] is a pawn, and sfml[0] is also a pawn, etc
						window.draw(sfmlPieces[i].sprite);
					}
				}
			}
			if(pieceselected||pieceup){//if you have some piece selected, draw the legal moves
				for(int i=0;i<legalmoves.size();i++){//for each legal move
					if(x==legalmoves[i][2]&&y==legalmoves[i][3]){//if the square we are checking in the big loop is one of the legal moves
						if(board[y][x]!="  "){//if the square is occupied, draw the square thingies
							tlb.setPosition(100*(nturn-nfix*x),100*(nturn-nfix*y));
							tlt.setPosition(100*(nturn-nfix*x),100*(nturn-nfix*y));
							trb.setPosition(100*(nturn-nfix*x),100*(nturn-nfix*y));
							trt.setPosition(100*(nturn-nfix*x),100*(nturn-nfix*y));
							blb.setPosition(100*(nturn-nfix*x),100*(nturn-nfix*y));
							blt.setPosition(100*(nturn-nfix*x),100*(nturn-nfix*y));
							brb.setPosition(100*(nturn-nfix*x),100*(nturn-nfix*y));
							brt.setPosition(100*(nturn-nfix*x),100*(nturn-nfix*y));
							window.draw(tlb);
							window.draw(tlt);
							window.draw(trb);
							window.draw(trt);
							window.draw(blb);
							window.draw(blt);
							window.draw(brb);
							window.draw(brt);
						}
						else{//if the square is empty, draw the dot
							possiblemove.setPosition(100*(nturn-nfix*x),100*(nturn-nfix*y));
							window.draw(possiblemove);
						}
					}
				}
			}
			if(pieceup){//if the piece is up
				for(int i=0;i<12;i++){//find the piece
					if(board[piecey][piecex]==textPieces[i]){//find the piece
						sfmlpieces[i].sprite.setPosition(Mouse::getPosition(window).x-50,Mouse::getPosition(window).y-50);//draw the piece and the mouse position
						window.draw(sfmlpieces[i].sprite);
					}
				}
			}
		}
	}
}
int main(){
	ChessPiece WK("ChessSpriteSheet.png",0,0),WQ("ChessSpriteSheet.png",1,0),WB("ChessSpriteSheet.png",2,0),WN("ChessSpriteSheet.png",3,0),WR("ChessSpriteSheet.png",4,0),WP("ChessSpriteSheet.png",5,0),BK("ChessSpriteSheet.png",0,1),BQ("ChessSpriteSheet.png",1,1),BB("ChessSpriteSheet.png",2,1),BN("ChessSpriteSheet.png",3,1),BR("ChessSpriteSheet.png",4,1),BP("ChessSpriteSheet.png",5,1);//Create each chess piece
	ChessPiece sfmlpieces[12]={WK,WQ,WB,WN,WR,WP,BK,BQ,BB,BN,BR,BP};//put the pieces in a list
	Sprite whitepromopieces;//this is for promoting, just the four pieces you can promote to
	Sprite blackpromopieces;
	Texture promopieces;//texture for the promo pieces
	if(!promopieces.loadFromFile(resourcePath()+"ChessSpriteSheet.png")){//load promopieces
		cout<<"Texture not working"<<endl;
	}
	whitepromopieces.setTexture(promopieces);//set the texture and fix its size
	whitepromopieces.setTextureRect(IntRect(1000/3,0,4000/3,1000/3));
	whitepromopieces.setScale(.5,.5);
	whitepromopieces.setOrigin(2000/3,500/3);
	whitepromopieces.setPosition(400,400);
	blackpromopieces.setTexture(promopieces);
	blackpromopieces.setTextureRect(IntRect(1000/3,1000/3,4000/3,1000/3));
	blackpromopieces.setScale(.5,.5);
	blackpromopieces.setOrigin(2000/3,500/3);
	blackpromopieces.setPosition(400,400);
	Font arial;//Arial font
	if(!arial.loadFromFile(resourcePath()+"FinalProjectArial.ttf")){//loading the font
		cout<<"Font not working"<<endl;
	}
	Text whitewin;//Text that is white wins, set arial font, "White wins",50 character size, and set the position to the center. Then the same for black
	whitewin.setFont(arial);
	whitewin.setString("White Wins!!!");
	whitewin.setCharacterSize(50);
	FloatRect whitewinRect=whitewin.getLocalBounds();
	whitewin.setOrigin(whitewinRect.width/2,whitewinRect.height/2);
	whitewin.setPosition(400,400);
	Text blackwin;
	blackwin.setFont(arial);
	blackwin.setString("Black Wins!!!");
	blackwin.setCharacterSize(50);
	FloatRect blackwinRect=blackwin.getLocalBounds();
	blackwin.setOrigin(blackwinRect.width/2,blackwinRect.height/2);
	blackwin.setPosition(400,400);
	Text stalemate;
	stalemate.setFont(arial);
	stalemate.setString("Stalemate!!!");
	stalemate.setCharacterSize(50);
	FloatRect stalemateRect=stalemate.getLocalBounds();
	stalemate.setOrigin(stalemateRect.width/2,stalemateRect.height/2);
	stalemate.setPosition(400,400);
	string textpieces[12]={"WK","WQ","WB","WN","WR","WP","BK","BQ","BB","BN","BR","BP"};//an array of text pieces that corrospond to the sfml pieces
	string board[8][8]={{"BR","BN","BB","BQ","BK","BB","BN","BR"},
						{"BP","BP","BP","BP","BP","BP","BP","BP"},
						{"  ","  ","  ","  ","  ","  ","  ","  "},
						{"  ","  ","  ","  ","  ","  ","  ","  "},
						{"  ","  ","  ","  ","  ","  ","  ","  "},
						{"  ","  ","  ","  ","  ","  ","  ","  "},
						{"WP","WP","WP","WP","WP","WP","WP","WP"},
						{"WR","WN","WB","WQ","WK","WB","WN","WR"}};//2d vector of the board
	int piecex=-1,piecey=-1,squarex=-1,squarey=-1,promox=0,promoy=0,nturn=0,nfix=-1;//the variables that are used. Piecex,y is the xy coordinate of the piece you have selected. Suarex,y is the xy position of the square you want to move to. lastpiece,promox,y is used for which promotion square we are dealing with. nturn and nfix are used to flip the board
	bool pieceselected=false,pieceup=false;//More variables, pieceselected is just that. Is the piece selected. Piece up is whether the piece is "picked up" or not. Clear legal moves tells me whether I should clear legal moves or not, because whenver you click on a new piece you need to clear the legal moves and get new ones.
	string color="W",promopiece;//color keeps track of the turns but is a string, promopiece is a string of which piece is being promoted
	vector<vector<int>> notation;//Notation keeps track of all the moves made in the game
	vector<vector<int>> legalmoves;//legal moves stores the legal moves for the piece you have selected
	vector<int> lastmove={-1,-1,-1,-1,-1};//last move is used to add moves into the notation
	notation.push_back(lastmove);//add one element to notation so we dont get an index error at the start
	RenderWindow window(VideoMode(800,800),"Chess");//800x800 chess window
	while(window.isOpen()){
		Event event;
		while(window.pollEvent(event)){
			if(event.type==Event::Closed){
				window.close();
			}
			if(!promotion(board)){//if we arent promoting
				if(Mouse::isButtonPressed(Mouse::Left)&&findwb(board[nturn-nfix*Mouse::getPosition(window).y/100][nturn-nfix*Mouse::getPosition(window).x/100])==color&&!pieceup){//if they press the button and the clicked a piece and the piece is not "picked up"
					legalmoves.clear();//clear the legal moves
					piecex=nturn-nfix*Mouse::getPosition(window).x/100;//get x,y pos of mouse and store it (nturn and nfix fixing if the screen is flipped or not
					piecey=nturn-nfix*Mouse::getPosition(window).y/100;
					legalmoves=getlegalmoves(board,legalmoves,notation,piecex,piecey);//get the legal moves for the current piece
					pieceup=true;//the piece is now picked up
				}
				else if(!Mouse::isButtonPressed(Mouse::Left)&&pieceup){//if the button is not pressed and the piece is up (meaning the person clicked the mouse, up and down)
					squarex=nturn-nfix*Mouse::getPosition(window).x/100;//get the x,y pos of the mouse and store it
					squarey=nturn-nfix*Mouse::getPosition(window).y/100;
					for(int i=0;i<legalmoves.size();i++){//for each legal move
						if(squarex==legalmoves[i][2]&&squarey==legalmoves[i][3]){//if the square they clicked on is a "legal move"
							movepiece(board,piecex,piecey,squarex,squarey);//move the piece
							notation=changenotation(board,notation,lastmove,textpieces,piecex,piecey,squarex,squarey);//change the notation
							pieceup=false;//the piece is no longer help up
							piecex=-1;//reset these
							piecey=-1;
							legalmoves.clear();//clear the legal moves, as you no longer have a piece selected
							color=changecolor(color);//change the turn
							if(color=="W"){//set nturn and nfix to flip the board
								nturn=0;
								nfix=-1;
							}
							else{
								nturn=7;
								nfix=1;
							}
							break;
						}
					}
					if(pieceup){//if the piece is still up, meaning the square they dropped it down on was not a legal move
						squarex=-1;//reset squarex,y
						squarey=-1;
						pieceselected=!pieceselected;//switch pieceselected
						pieceup=false;//the piece is not up, meaning it goes back to its origional square
					}
				}
				else if(Mouse::isButtonPressed(Mouse::Left)&&pieceselected&&!pieceup){//if the mouse is clicked, and a piece is selected but not "up". This is for the chance that the click the piece and then click the square they want to move to
					if(findwb(board[nturn-nfix*Mouse::getPosition(window).y/100][nturn-nfix*Mouse::getPosition(window).x/100])!=color){//if the square is not your own piece
						squarex=nturn-nfix*Mouse::getPosition(window).x/100;//same code from now on as above
						squarey=nturn-nfix*Mouse::getPosition(window).y/100;
						for(int i=0;i<legalmoves.size();i++){
							if(squarex==legalmoves[i][2]&&squarey==legalmoves[i][3]){
								movepiece(board,piecex,piecey,squarex,squarey);
								notation=changenotation(board,notation,lastmove,textpieces,piecex,piecey,squarex,squarey);
								pieceselected=false;
								piecex=-1;
								piecey=-1;
								legalmoves.clear();
								color=changecolor(color);
								if(color=="W"){
									nturn=0;
									nfix=-1;
								}
								else{
									nturn=7;
									nfix=1;
								}
								break;
							}
						}
						pieceselected=false;
					}
				}
			}
			else{//if we need to promote a piece
				if(Mouse::isButtonPressed(Mouse::Left)){//when the piece is clicked
					promox=Mouse::getPosition(window).x;//get the xy pos of the mouse
					promoy=Mouse::getPosition(window).y;
					if(promox>=200/3&&promox<=700/3&&promoy<=1450/3&&promoy>=950/3){//find if they clicked on the piece. The values are correct, same code for each one
						if(color=="B"){
							board[notation[notation.size()-1][3]][notation[notation.size()-1][2]]="WQ";
						}
						else{
							board[notation[notation.size()-1][3]][notation[notation.size()-1][2]]="BQ";
						}
					}
					if(promox>=700/3&&promox<=400&&promoy<=1450/3&&promoy>=950/3){
						if(color=="B"){
							board[notation[notation.size()-1][3]][notation[notation.size()-1][2]]="WB";
						}
						else{
							board[notation[notation.size()-1][3]][notation[notation.size()-1][2]]="BB";
						}
					}
					if(promox>=400&&promox<=1700/3&&promoy<=1450/3&&promoy>=950/3){
						if(color=="B"){
							board[notation[notation.size()-1][3]][notation[notation.size()-1][2]]="WN";
						}
						else{
							board[notation[notation.size()-1][3]][notation[notation.size()-1][2]]="BN";
						}
					}
					if(promox>=1700/3&&promox<=2200/3&&promoy<=1450/3&&promoy>=950/3){
						if(color=="B"){
							board[notation[notation.size()-1][3]][notation[notation.size()-1][2]]="WR";
						}
						else{
							board[notation[notation.size()-1][3]][notation[notation.size()-1][2]]="BR";
						}
					}
				}
			}
		}
		window.clear(Color(127,127,127));
		if(!promotion(board)&&!checkmate(board,notation,color)){
			printboardsfml(board,window,sfmlpieces,textpieces,piecex,piecey,pieceup,pieceselected,sfmlpieces,legalmoves,nturn,nfix);
		}
		else if(promotion(board)){
			if(color=="B"){
				window.draw(whitepromopieces);
			}
			else{
				window.draw(blackpromopieces);
			}
		}
		if(!promotion(board)&&checkmate(board,notation,color)&&kingincheck(board,color)){
			if(color=="W"){
				window.draw(blackwin);
			}
			else{
				window.draw(whitewin);
			}
		}
		if(!promotion(board)&&checkmate(board,notation,color)&&!kingincheck(board,color)){
			window.draw(stalemate);
		}
		window.display();
	}
}