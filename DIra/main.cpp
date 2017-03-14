#include "Screen.h"
#include "ncurses.h"
#include <fstream>
#include <iostream>
#include <list>
#include "Cannon.h"
#include "Pesawat.h"
#include <stdlib.h>
#include <time.h>
#include "../rapih.cpp"


using namespace std;

double getRatio(int x) {
	double ret = (double) x/417;
	return ret;
}

void drawTree(int x, int y, list<LineDetails*> listLine) {
	cout<<x<<" "<<y<<endl;
	//cout<<listLine.back()<<endl;
	listLine.push_back(new LineDetails(getRatio(x), getRatio(y), getRatio(x), getRatio(y+3)));
	listLine.push_back(new LineDetails(getRatio(x-3), getRatio(y), getRatio(x), getRatio(y-6)));
	listLine.push_back(new LineDetails(getRatio(x), getRatio(y-6), getRatio(x+3), getRatio(y)));
	listLine.push_back(new LineDetails(getRatio(x+3), getRatio(y), getRatio(x-3), getRatio(y)));
	//cout<<listLine.back()<<endl;
}

void printWords(LineDetails *it,Line lineManager,int movex,int movey){
		int newx1 = it->x1 * 300 +movex;
		int newy1 = it->y1 * 300 +movey;
		int newx2 = it->x2 * 300 +movex;
		int newy2 = it->y2 * 300 +movey;
		//cout<<"this is newx1 " << newx1<<endl;
		//cout<<"this is newx2 " << newx2<<endl;
		//cout<<"this is newy1 " << newy1<<endl;
		//cout<<"this is newy2 " << newy2<<endl;
			// draw line
		lineManager.insertLine(newx1, newy1, newx2, newy2, 255, 255, 255);
}


int main() {
	//PRINT OPENING
	list<LineDetails*> listLineUFO;
	fstream fileufo("UFOITB.txt", std::ios_base::in);
	//fstream fileufo("notready.txt", std::ios_base::in);
	list<int> intListUfo;

	int yow;
	Line lineManager;
   	while (fileufo >> yow){
		intListUfo.push_back(yow);
		//cout<<yow<<endl;
	}
	fileufo.close();

        int* tempz = new int[4];

	int loopz = 0;
    	for (std::list<int>::iterator it = intListUfo.begin(); it != intListUfo.end(); ++it) {
		tempz[loopz] = *it;
		loopz++;
		if (loopz == 4) {
			listLineUFO.push_back(new LineDetails(getRatio(tempz[0]), getRatio(tempz[1]), getRatio(tempz[2]), getRatio(tempz[3])));
			loopz = 0;
		}
	}
	list<LineDetails*> listLinePlay;
	fstream fileplay("letsplay.txt", std::ios_base::in);
	list<int> intListPlay;

	int moveline;
	//Line lineManager;
   	while (fileplay >> moveline){
		intListPlay.push_back(moveline);
		//cout<<yow<<endl;
	}
	fileplay.close();

        int* tempmove = new int[4];

	int loopmove = 0;
    	for (std::list<int>::iterator it = intListPlay.begin(); it != intListPlay.end(); ++it) {
		tempmove[loopmove] = *it;
		loopmove++;
		if (loopmove == 4) {
			listLinePlay.push_back(new LineDetails(getRatio(tempmove[0]), getRatio(tempmove[1]), getRatio(tempmove[2]), getRatio(tempmove[3])));
			loopmove = 0;
		}
	}
	int until = 0;
	while(until<6) {
		system("clear");
		usleep(200000);
		for(list<LineDetails*>::iterator it = listLineUFO.begin(); it != listLineUFO.end(); it++) {
			printWords((*it),lineManager,0,0);
			//cout<<*it<<endl;
		}
		//ANIMATION LETS PLAY
		int cekwords=0;
		if (until==1) {
			for(list<LineDetails*>::iterator it = listLinePlay.begin(); it != listLinePlay.end(); it++) {
				cekwords++;
				printWords((*it),lineManager,100,100);
				if (cekwords>5){
					break;
				}
				//cout<<*it<<endl;
			}
		} else if (until==2) {
			for(list<LineDetails*>::iterator it = listLinePlay.begin(); it != listLinePlay.end(); it++) {
				cekwords++;
				printWords((*it),lineManager,100,100);
				if (cekwords>10){
					break;
				}
				//cout<<*it<<endl;
			}

		} else if (until==3) {
			for(list<LineDetails*>::iterator it = listLinePlay.begin(); it != listLinePlay.end(); it++) {
				cekwords++;
				printWords((*it),lineManager,100,100);
				if (cekwords>15){
					break;
				}
				//cout<<*it<<endl;
			}
		} else if (until==4) {
			for(list<LineDetails*>::iterator it = listLinePlay.begin(); it != listLinePlay.end(); it++) {
				cekwords++;
				printWords((*it),lineManager,100,100);
				if (cekwords>20){
					break;
				}
				//cout<<*it<<endl;
			}

		} else if (until==5) {
			for(list<LineDetails*>::iterator it = listLinePlay.begin(); it != listLinePlay.end(); it++) {
				printWords((*it),lineManager,100,100);
				//cout<<*it<<endl;
			}

		}
		usleep(1000000);
		until++;
	}
	usleep(200000);
	//4 STAGE
	list<LineDetails*> listLineStage1;
	fstream filestage("stage1.txt", std::ios_base::in);
	list<int> intListStage1;

	int movestage1;
//	Line lineManager;
   	while (filestage >> movestage1){
		intListStage1.push_back(movestage1);
		//cout<<yow<<endl;
	}
	filestage.close();

        int* tempstage1 = new int[4];

	int loopstage1 = 0;
    	for (std::list<int>::iterator it = intListStage1.begin(); it != intListStage1.end(); ++it) {
		tempstage1[loopstage1] = *it;
		loopstage1++;
		if (loopstage1 == 4) {
			listLineStage1.push_back(new LineDetails(getRatio(tempstage1[0]), getRatio(tempstage1[1]), getRatio(tempstage1[2]), getRatio(tempstage1[3])));
			loopstage1 = 0;
		}
	}
	list<LineDetails*> listLineStage2;
	fstream filestage2("stage2.txt", std::ios_base::in);
	list<int> intListStage2;

	int movestage2;
//	Line lineManager;
   	while (filestage2 >> movestage2){
		intListStage2.push_back(movestage2);
		//cout<<yow<<endl;
	}
	filestage2.close();

        int* tempstage2 = new int[4];

	int loopstage2 = 0;
    	for (std::list<int>::iterator it = intListStage2.begin(); it != intListStage2.end(); ++it) {
		tempstage2[loopstage2] = *it;
		loopstage2++;
		if (loopstage2 == 4) {
			listLineStage2.push_back(new LineDetails(getRatio(tempstage2[0]), getRatio(tempstage2[1]), getRatio(tempstage2[2]), getRatio(tempstage2[3])));
			loopstage2 = 0;
		}
	}
	list<LineDetails*> listLineStage3;
	fstream filestage3("stage3.txt", std::ios_base::in);
	list<int> intListStage3;
	int movestage3;
//	Line lineManager;
   	while (filestage3 >> movestage3){
		intListStage3.push_back(movestage3);
		//cout<<yow<<endl;
	}
	filestage3.close();

        int* tempstage3 = new int[4];

	int loopstage3 = 0;
    	for (std::list<int>::iterator it = intListStage3.begin(); it != intListStage3.end(); ++it) {
		tempstage3[loopstage3] = *it;
		loopstage3++;
		if (loopstage3 == 4) {
			listLineStage3.push_back(new LineDetails(getRatio(tempstage3[0]), getRatio(tempstage3[1]), getRatio(tempstage3[2]), getRatio(tempstage3[3])));
			loopstage3 = 0;
		}
	}
	list<LineDetails*> listLineStage4;
	fstream filestage4("stage4.txt", std::ios_base::in);
	list<int> intListStage4;
	int movestage4;
//	Line lineManager;
   	while (filestage4 >> movestage4){
		intListStage4.push_back(movestage4);
		//cout<<yow<<endl;
	}
	filestage4.close();


        int* tempstage4 = new int[4];

	int loopstage4 = 0;
    	for (std::list<int>::iterator it = intListStage4.begin(); it != intListStage4.end(); ++it) {
		tempstage4[loopstage4] = *it;
		loopstage4++;
		if (loopstage4 == 4) {
			listLineStage4.push_back(new LineDetails(getRatio(tempstage4[0]), getRatio(tempstage4[1]), getRatio(tempstage4[2]), getRatio(tempstage4[3])));
			loopstage4 = 0;
		}
	}

	list<LineDetails*> listEnding;
	fstream fileEnding("Congrats.txt", std::ios_base::in);
	list<int> intListEnding;

	int moveending;
//	Line lineManager;
   	while (fileEnding >> moveending){
		intListEnding.push_back(moveending);
		//cout<<yow<<endl;
	}
	fileEnding.close();

	int* tempending = new int[4];

	int loopending = 0;
    	for (std::list<int>::iterator it = intListEnding.begin(); it != intListEnding.end(); ++it) {
		tempending[loopending] = *it;
		loopending++;
		if (loopending == 4) {
			listEnding.push_back(new LineDetails(getRatio(tempending[0]), getRatio(tempending[1]), getRatio(tempending[2]), getRatio(tempending[3])));
			loopending = 0;
		}
	}


	int stages[5];
	stages[0]=0;
	stages[1]=0;
	stages[2]=0;
	stages[3]=0;

	int varZoom = 3;
	// Big screen
	// !!! width:height ratio = 4:3
	int bigScreenWidth = 415;
	int bigScreenHeight = 415;
	srand(time(NULL));
	Screen bigScreen = Screen(0, 0, bigScreenWidth, bigScreenHeight);
	//RANDOM STAGE POSITION
	int stageMapX[5];
	stageMapX[0]=rand()%bigScreenWidth;
	stageMapX[1]=rand()%bigScreenWidth;
	stageMapX[2]=rand()%bigScreenWidth;
	stageMapX[3]=rand()%bigScreenWidth;
	stageMapX[4]=rand()%bigScreenWidth;
	int stageMapY[5];
	stageMapY[0]=rand()%bigScreenHeight;
	stageMapY[1]=rand()%bigScreenHeight;
	stageMapY[2]=rand()%bigScreenHeight;
	stageMapY[3]=rand()%bigScreenHeight;
	stageMapY[4]=rand()%bigScreenHeight;
	list<LineDetails*> listStageMap;
	int loopx=0;

	cout<<"TES";
	for (int it = 0; it <4; it++) {
		for (int it = 0; it <4; it++) {
			int stage_increment = 0;
			for (int i_it = 0; i_it <= it; i_it++ ){
				listStageMap.push_back(new LineDetails(getRatio(stageMapX[it]), getRatio(stageMapY[it]+stage_increment), getRatio(stageMapX[it]+5), getRatio(stageMapY[it]+stage_increment)));
				stage_increment += 2;
			}
		}

		listStageMap.push_back(new LineDetails(getRatio(stageMapX[it]), getRatio(stageMapY[it]-2), getRatio(stageMapX[it]+4), getRatio(stageMapY[it]-2)));
		listStageMap.push_back(new LineDetails(getRatio(stageMapX[it]), getRatio(stageMapY[it]-2), getRatio(stageMapX[it]+1), getRatio(stageMapY[it]-3)));
		listStageMap.push_back(new LineDetails(getRatio(stageMapX[it]+1), getRatio(stageMapY[it]-3), getRatio(stageMapX[it]+3), getRatio(stageMapY[it]-3)));
		listStageMap.push_back(new LineDetails(getRatio(stageMapX[it]+3), getRatio(stageMapY[it]-3), getRatio(stageMapX[it]+4), getRatio(stageMapY[it]-2)));
		listStageMap.push_back(new LineDetails(getRatio(stageMapX[it]+3), getRatio(stageMapY[it]-3), getRatio(stageMapX[it]+3), getRatio(stageMapY[it]-4)));
		listStageMap.push_back(new LineDetails(getRatio(stageMapX[it]+1), getRatio(stageMapY[it]-4), getRatio(stageMapX[it]+1), getRatio(stageMapY[it]-3)));
		listStageMap.push_back(new LineDetails(getRatio(stageMapX[it]+1), getRatio(stageMapY[it]-4), getRatio(stageMapX[it]+3), getRatio(stageMapY[it]-4)));
	}
	cout<<"TES";
//	usleep(200000000);
	// Small screen
	// !!! its size is relative to bigScreen
	int smallScreenWidth = bigScreenWidth/3;
	int smallScreenHeight = bigScreenHeight/3;
	Screen smallScreen = Screen(bigScreenWidth, bigScreenHeight-smallScreenHeight, smallScreenWidth, smallScreenHeight);

	//ZOOM Screen
	// size relative to bigscreen
	int zoomScreenWidth = bigScreenWidth/3;
	int zoomScreenHeight = bigScreenHeight/3;
	Screen zoomScreen = Screen(0, 0, zoomScreenWidth, zoomScreenHeight);
	int xa = 0;
	int ya = 0;

	//List of LineDetails
	int plus=0;
	//LineDetails is 2 point defining the line.
	list<LineDetails*> listLine;
	list<LineDetails*> listTree;
	list<LineDetails*> listPath;
	list<LineDetails*> listFlower;
	bool lineDisplay = 1;
	bool ufoDisplay = 1;
	bool treeDisplay = 1;
	bool pathDisplay = 1;
	bool flowerDisplay = 1;

	//read from file to built ITB depan
	fstream myfile("coordinat.txt", std::ios_base::in);

	list<int> intList;

    int a;
    while (myfile >> a)
    {
        intList.push_back(a);
    }

    int* temp = new int[4];

    int loop = 0;
    for (std::list<int>::iterator it = intList.begin(); it != intList.end(); ++it) {
		temp[loop] = *it;
		loop++;
		if (loop == 4) {
			listLine.push_back(new LineDetails(getRatio(temp[0]), getRatio(temp[1]), getRatio(temp[2]), getRatio(temp[3])));
			loop = 0;
		}
	}

	myfile.close();


	// DRAW TREE
	fstream treefile("coordinate_tree.txt",std::ios_base::in);
	list<int> intTreeList;

    int b;
    while (treefile >> b)
    {
        intTreeList.push_back(b);
    }

    int* tempT = new int[2];

    loop = 0;
    for (std::list<int>::iterator it = intTreeList.begin(); it != intTreeList.end(); ++it) {
		tempT[loop] = *it;
		loop++;
		if (loop == 2) {
			listTree.push_back(new LineDetails(getRatio(tempT[0]), getRatio(tempT[1]), getRatio(tempT[0]), getRatio(tempT[1]+5)));
			listTree.push_back(new LineDetails(getRatio(tempT[0]-5), getRatio(tempT[1]), getRatio(tempT[0]), getRatio(tempT[1]-10)));
			listTree.push_back(new LineDetails(getRatio(tempT[0]), getRatio(tempT[1]-10), getRatio(tempT[0]+5), getRatio(tempT[1])));
			listTree.push_back(new LineDetails(getRatio(tempT[0]+5), getRatio(tempT[1]), getRatio(tempT[0]-5), getRatio(tempT[1])));
			loop = 0;
		}
	}

	treefile.close();

	//Draw Path
	fstream pathfile("coordinat_path.txt", std::ios_base::in);

	list<int> intListP;

	int c;
    while (pathfile >> c)
    {
        intListP.push_back(c);
    }


	loop = 0;
    for (std::list<int>::iterator it = intListP.begin(); it != intListP.end(); ++it) {
		temp[loop] = *it;
		loop++;
		if (loop == 4) {
			listPath.push_back(new LineDetails(getRatio(temp[0]), getRatio(temp[1]), getRatio(temp[2]), getRatio(temp[3])));
			loop = 0;
		}
	}

	pathfile.close();
	//Draw FLower
	fstream flowerfile("coordinat_flower.txt", std::ios_base::in);

	list<int> intListF;

	int d;
    while (flowerfile >> d)
    {
        intListF.push_back(d);
    }


	loop = 0;
    for (std::list<int>::iterator it = intListF.begin(); it != intListF.end(); ++it) {
		temp[loop] = *it;
		loop++;
		if (loop == 4) {
			listFlower.push_back(new LineDetails(getRatio(temp[0]), getRatio(temp[1]), getRatio(temp[2]), getRatio(temp[3])));
			loop = 0;
		}
	}

	flowerfile.close();

	//Next Step
	system("clear");
	initscr();
	keypad(stdscr,TRUE);
	noecho();
	char ch;
	while(1) {

		system("clear");
		cout<<"                                                     Your Position-> X : ";
		cout<<zoomScreen.getOriginX();
		cout<<" Y : ";
		//cout<<zoomScreen.getOriginX()+zoomScreen.getWidth()<<endl;
		//cout<<stageMapX[0]<<endl;
		cout<<zoomScreen.getOriginY()<<endl;
		/*cout<<"Stage 1-> X : ";
		cout<<stageMapX[0];
		cout<<" Y : ";

		cout<<stageMapY[0]<<endl;
		cout<<"Stage 2-> X : ";
		cout<<stageMapX[1];
		cout<<" Y : ";

		cout<<stageMapY[1]<<endl;
		cout<<"                                          Stage 3-> X : ";
		cout<<stageMapX[2];
		cout<<" Y : ";

		cout<<stageMapY[2]<<endl;
		cout<<"                                          Stage 4-> X : ";
		cout<<stageMapX[3];
		cout<<" Y : ";

		cout<<stageMapY[3]<<endl;*/
//		cout<<zoomScreen.getOriginY()+zoomScreen.getHeight()<<endl;
//		cout<<stageMapY[0]<<endl;
		//usleep(200000);
		// example
		if (ufoDisplay){
			for(list<LineDetails*>::iterator it = listStageMap.begin(); it != listStageMap.end(); it++) {
				//bigScreen.renderLine((*it),0,255,255);
				//NOT SHOWN IN BIGSCREEN
			}
			smallScreen.renderSmall(listStageMap, zoomScreen, bigScreen,0,255,255);
		}
		if (lineDisplay){
			for(list<LineDetails*>::iterator it = listLine.begin(); it != listLine.end(); it++) {
				bigScreen.renderLine((*it),255,255,255);
			}
			smallScreen.renderSmall(listLine, zoomScreen, bigScreen,255,255,255);
		}
		if (treeDisplay) {
			for(list<LineDetails*>::iterator it = listTree.begin(); it != listTree.end(); it++) {
				bigScreen.renderLine((*it),0,255,0);
			}
			smallScreen.renderSmall(listTree, zoomScreen, bigScreen,0,255,0);
		}
		if (pathDisplay) {
			for(list<LineDetails*>::iterator it = listPath.begin(); it != listPath.end(); it++) {
				bigScreen.renderLine((*it),0,0,255);
			}
			smallScreen.renderSmall(listPath, zoomScreen, bigScreen,0,0,255);
		}
		if (flowerDisplay) {
			for(list<LineDetails*>::iterator it = listFlower.begin(); it != listFlower.end(); it++) {
				bigScreen.renderLine((*it),255,0,0);
			}
			smallScreen.renderSmall(listFlower, zoomScreen, bigScreen,255,0,0);
		}
		bigScreen.renderBorder();
		smallScreen.renderBorder();
		zoomScreen.renderBorder();
		ch = getch();
		//smallScreen.renderSmall(listLine, zoomScreen, bigScreen,0,0,0);

		//mvaddch(ya,xa,ch);
		switch(ch){
		case 'a':
		  if (xa>0) {
		  xa--;
		  zoomScreen.renderBorderCol(0,0,0);
		  zoomScreen.changeOrigin(xa,ya);
		  zoomScreen.renderBorder();
		  }
       		break;
		case 'd':
		//smallScreen.renderSmall(listLine, zoomScreen, bigScreen,0,0,0);
		  if (xa+zoomScreenWidth<bigScreenWidth) {
		  xa++;
		  zoomScreen.renderBorderCol(0,0,0);
		  zoomScreen.changeOrigin(xa,ya);
		  zoomScreen.renderBorder();
		  }
		break;
		case 'w':
		//smallScreen.renderSmall(listLine, zoomScreen, bigScreen,0,0,0);
			if (ya>0) {
			ya--;
			zoomScreen.renderBorderCol(0,0,0);
			zoomScreen.changeOrigin(xa,ya);
			zoomScreen.renderBorder();
			}
		break;
		case 's':
		//smallScreen.renderSmall(listLine, zoomScreen, bigScreen,0,0,0);
			if (ya+zoomScreenHeight<bigScreenHeight) {
			ya++;
			zoomScreen.renderBorderCol(0,0,0);
			zoomScreen.changeOrigin(xa,ya);
			zoomScreen.renderBorder();
		  }
		break;
		case 'i':
		//smallScreen.renderSmall(listLine, zoomScreen, bigScreen,0,0,0);
		  //3 6 9 18 60 102
		  if (varZoom == 3) {
				varZoom = 6;
		  }
		  else if (varZoom == 6) {
				varZoom = 9;
		  }
		  else if (varZoom == 9) {
				varZoom = 18;
		  }
		  else if (varZoom == 18) {
				varZoom = 60;
		  }
		  else if (varZoom == 60) {
				varZoom = 105;
		  }
		  else {
		  }
		  zoomScreenWidth = bigScreenWidth/varZoom;
		  zoomScreenHeight = bigScreenHeight/varZoom;
		  zoomScreen = Screen(xa, ya, zoomScreenWidth, zoomScreenHeight);
		break;
		case 'o':
		//smallScreen.renderSmall(listLine, zoomScreen, bigScreen,0,0,0);
		  if (varZoom == 105) {
				varZoom = 60;
		  }
		  else if (varZoom == 60) {
				varZoom = 18;
		  }
		  else if (varZoom == 18) {
				varZoom = 9;
		  }
		  else if (varZoom == 9) {
				varZoom = 6;
		  }
		  else if (varZoom == 6) {
				varZoom = 3;
		  }
		  else {
		  }
		  zoomScreenWidth = bigScreenWidth/varZoom;
		  zoomScreenHeight = bigScreenHeight/varZoom;
		  zoomScreen = Screen(xa, ya, zoomScreenWidth, zoomScreenHeight);
		break;
		case 'x':
			if (treeDisplay == 1){
				treeDisplay = 0;
			}
			else {
				treeDisplay = 1;
			}
		break;
		case 'c':
			if (pathDisplay == 1){
				pathDisplay = 0;
			}
			else {
				pathDisplay = 1;
			}
		break;
		case 'v':
			if (flowerDisplay == 1){
				flowerDisplay = 0;
			}
			else {
				flowerDisplay = 1;
			}
		break;

		case 'e':
			// STAGE 1
			if (zoomScreen.getOriginX()<=stageMapX[0] && zoomScreen.getOriginX()+zoomScreen.getWidth()>=stageMapX[0] && zoomScreen.getOriginY()<=stageMapY[0] && zoomScreen.getOriginY()+zoomScreen.getHeight()>=stageMapY[0]) {
				//YOU CAN'T ABORT THE MISSION
				system("clear");
				for(list<LineDetails*>::iterator it = listLineStage1.begin(); it != listLineStage1.end(); it++) {
					printWords((*it),lineManager,100,100);
					//cout<<*it<<endl;
				}
				usleep(1000000);
				system("clear");
				cout<<"You can't abort the mission! Continue? (Y/N)"<<endl;
				char inYes = getch();
				//smallScreen.renderSmall(listLine, zoomScreen, bigScreen,0,0,0);

				//mvaddch(ya,xa,ch);
				switch(inYes){
				case 'y':
					playUFO(1);
					stages[0]=1;
					system("clear");
					stageMapX[0]=rand()%bigScreenWidth;
					stageMapX[1]=rand()%bigScreenWidth;
					stageMapX[2]=rand()%bigScreenWidth;
					stageMapX[3]=rand()%bigScreenWidth;
					stageMapX[4]=rand()%bigScreenWidth;
					stageMapY[0]=rand()%bigScreenHeight;
					stageMapY[1]=rand()%bigScreenHeight;
					stageMapY[2]=rand()%bigScreenHeight;
					stageMapY[3]=rand()%bigScreenHeight;
					stageMapY[4]=rand()%bigScreenHeight;
					listStageMap = list<LineDetails*>() ;
					loopx=0;
					for (int it = 0; it <4; it++) {
						for (int it = 0; it <4; it++) {
							int stage_increment = 0;
							for (int i_it = 0; i_it <= it; i_it++ ){
								listStageMap.push_back(new LineDetails(getRatio(stageMapX[it]), getRatio(stageMapY[it]+stage_increment), getRatio(stageMapX[it]+5), getRatio(stageMapY[it]+stage_increment)));
								stage_increment += 2;
							}
						}

						listStageMap.push_back(new LineDetails(getRatio(stageMapX[it]), getRatio(stageMapY[it]-2), getRatio(stageMapX[it]+4), getRatio(stageMapY[it]-2)));
						listStageMap.push_back(new LineDetails(getRatio(stageMapX[it]), getRatio(stageMapY[it]-2), getRatio(stageMapX[it]+1), getRatio(stageMapY[it]-3)));
						listStageMap.push_back(new LineDetails(getRatio(stageMapX[it]+1), getRatio(stageMapY[it]-3), getRatio(stageMapX[it]+3), getRatio(stageMapY[it]-3)));
						listStageMap.push_back(new LineDetails(getRatio(stageMapX[it]+3), getRatio(stageMapY[it]-3), getRatio(stageMapX[it]+4), getRatio(stageMapY[it]-2)));
						listStageMap.push_back(new LineDetails(getRatio(stageMapX[it]+3), getRatio(stageMapY[it]-3), getRatio(stageMapX[it]+3), getRatio(stageMapY[it]-4)));
						listStageMap.push_back(new LineDetails(getRatio(stageMapX[it]+1), getRatio(stageMapY[it]-4), getRatio(stageMapX[it]+1), getRatio(stageMapY[it]-3)));
						listStageMap.push_back(new LineDetails(getRatio(stageMapX[it]+1), getRatio(stageMapY[it]-4), getRatio(stageMapX[it]+3), getRatio(stageMapY[it]-4)));
					}
					break;
				case 'n' : system("clear");
				}
			} else if (zoomScreen.getOriginX()<=stageMapX[1] && zoomScreen.getOriginX()+zoomScreen.getWidth()>=stageMapX[1] && zoomScreen.getOriginY()<=stageMapY[1] && zoomScreen.getOriginY()+zoomScreen.getHeight()>=stageMapY[1] && stages[0]==1) {
				//YOU CAN'T ABORT THE MISSION
				system("clear");
				for(list<LineDetails*>::iterator it = listLineStage2.begin(); it != listLineStage2.end(); it++) {
					printWords((*it),lineManager,100,100);
					//cout<<*it<<endl;
				}
				usleep(1000000);
				system("clear");
				cout<<"You can't abort the mission! Continue? (Y/N)"<<endl;
				char inYes = getch();
				//smallScreen.renderSmall(listLine, zoomScreen, bigScreen,0,0,0);

				//mvaddch(ya,xa,ch);
				switch(inYes){
				case 'y':
					system("clear");
					playUFO(2);
					stages[1]=1;
					system("clear");
					stageMapX[0]=rand()%bigScreenWidth;
					stageMapX[1]=rand()%bigScreenWidth;
					stageMapX[2]=rand()%bigScreenWidth;
					stageMapX[3]=rand()%bigScreenWidth;
					stageMapX[4]=rand()%bigScreenWidth;
					stageMapY[0]=rand()%bigScreenHeight;
					stageMapY[1]=rand()%bigScreenHeight;
					stageMapY[2]=rand()%bigScreenHeight;
					stageMapY[3]=rand()%bigScreenHeight;
					stageMapY[4]=rand()%bigScreenHeight;
					listStageMap = list<LineDetails*>() ;
					loopx=0;

					for (int it = 0; it <4; it++) {
						for (int it = 0; it <4; it++) {
							int stage_increment = 0;
							for (int i_it = 0; i_it <= it; i_it++ ){
								listStageMap.push_back(new LineDetails(getRatio(stageMapX[it]), getRatio(stageMapY[it]+stage_increment), getRatio(stageMapX[it]+5), getRatio(stageMapY[it]+stage_increment)));
								stage_increment += 2;
							}
						}

						listStageMap.push_back(new LineDetails(getRatio(stageMapX[it]), getRatio(stageMapY[it]-2), getRatio(stageMapX[it]+4), getRatio(stageMapY[it]-2)));
						listStageMap.push_back(new LineDetails(getRatio(stageMapX[it]), getRatio(stageMapY[it]-2), getRatio(stageMapX[it]+1), getRatio(stageMapY[it]-3)));
						listStageMap.push_back(new LineDetails(getRatio(stageMapX[it]+1), getRatio(stageMapY[it]-3), getRatio(stageMapX[it]+3), getRatio(stageMapY[it]-3)));
						listStageMap.push_back(new LineDetails(getRatio(stageMapX[it]+3), getRatio(stageMapY[it]-3), getRatio(stageMapX[it]+4), getRatio(stageMapY[it]-2)));
						listStageMap.push_back(new LineDetails(getRatio(stageMapX[it]+3), getRatio(stageMapY[it]-3), getRatio(stageMapX[it]+3), getRatio(stageMapY[it]-4)));
						listStageMap.push_back(new LineDetails(getRatio(stageMapX[it]+1), getRatio(stageMapY[it]-4), getRatio(stageMapX[it]+1), getRatio(stageMapY[it]-3)));
						listStageMap.push_back(new LineDetails(getRatio(stageMapX[it]+1), getRatio(stageMapY[it]-4), getRatio(stageMapX[it]+3), getRatio(stageMapY[it]-4)));
					}
					break;
				case 'n' : system("clear");
				}

			} else if (zoomScreen.getOriginX()<=stageMapX[2] && zoomScreen.getOriginX()+zoomScreen.getWidth()>=stageMapX[2] && zoomScreen.getOriginY()<=stageMapY[2] && zoomScreen.getOriginY()+zoomScreen.getHeight()>=stageMapY[2] && stages[0]==1 && stages[1]==1) {
				//YOU CAN'T ABORT THE MISSION
				system("clear");
				for(list<LineDetails*>::iterator it = listLineStage3.begin(); it != listLineStage3.end(); it++) {
					printWords((*it),lineManager,100,100);
					//cout<<*it<<endl;
				}
				usleep(1000000);
				system("clear");
				cout<<"You can't abort the mission! Continue? (Y/N)"<<endl;
				char inYes = getch();
				//smallScreen.renderSmall(listLine, zoomScreen, bigScreen,0,0,0);

				//mvaddch(ya,xa,ch);
				switch(inYes){
				case 'y':
					system("clear");
					playUFO(3);
					stages[2]=1;
					system("clear");
					stageMapX[0]=rand()%bigScreenWidth;
					stageMapX[1]=rand()%bigScreenWidth;
					stageMapX[2]=rand()%bigScreenWidth;
					stageMapX[3]=rand()%bigScreenWidth;
					stageMapX[4]=rand()%bigScreenWidth;
					stageMapY[0]=rand()%bigScreenHeight;
					stageMapY[1]=rand()%bigScreenHeight;
					stageMapY[2]=rand()%bigScreenHeight;
					stageMapY[3]=rand()%bigScreenHeight;
					stageMapY[4]=rand()%bigScreenHeight;
					listStageMap = list<LineDetails*>() ;
					loopx=0;

					for (int it = 0; it <4; it++) {
						for (int it = 0; it <4; it++) {
							int stage_increment = 0;
							for (int i_it = 0; i_it <= it; i_it++ ){
								listStageMap.push_back(new LineDetails(getRatio(stageMapX[it]), getRatio(stageMapY[it]+stage_increment), getRatio(stageMapX[it]+5), getRatio(stageMapY[it]+stage_increment)));
								stage_increment += 2;
							}
						}

						listStageMap.push_back(new LineDetails(getRatio(stageMapX[it]), getRatio(stageMapY[it]-2), getRatio(stageMapX[it]+4), getRatio(stageMapY[it]-2)));
						listStageMap.push_back(new LineDetails(getRatio(stageMapX[it]), getRatio(stageMapY[it]-2), getRatio(stageMapX[it]+1), getRatio(stageMapY[it]-3)));
						listStageMap.push_back(new LineDetails(getRatio(stageMapX[it]+1), getRatio(stageMapY[it]-3), getRatio(stageMapX[it]+3), getRatio(stageMapY[it]-3)));
						listStageMap.push_back(new LineDetails(getRatio(stageMapX[it]+3), getRatio(stageMapY[it]-3), getRatio(stageMapX[it]+4), getRatio(stageMapY[it]-2)));
						listStageMap.push_back(new LineDetails(getRatio(stageMapX[it]+3), getRatio(stageMapY[it]-3), getRatio(stageMapX[it]+3), getRatio(stageMapY[it]-4)));
						listStageMap.push_back(new LineDetails(getRatio(stageMapX[it]+1), getRatio(stageMapY[it]-4), getRatio(stageMapX[it]+1), getRatio(stageMapY[it]-3)));
						listStageMap.push_back(new LineDetails(getRatio(stageMapX[it]+1), getRatio(stageMapY[it]-4), getRatio(stageMapX[it]+3), getRatio(stageMapY[it]-4)));
					}
					break;
				case 'n' : system("clear");
				}
			} else if (zoomScreen.getOriginX()<=stageMapX[3] && zoomScreen.getOriginX()+zoomScreen.getWidth()>=stageMapX[3] && zoomScreen.getOriginY()<=stageMapY[3] && zoomScreen.getOriginY()+zoomScreen.getHeight()>=stageMapY[3] && stages[0]==1 && stages[1]==1 && stages[2]==1) {
				//YOU CAN'T ABORT THE MISSION
				system("clear");
				for(list<LineDetails*>::iterator it = listLineStage4.begin(); it != listLineStage4.end(); it++) {
					printWords((*it),lineManager,100,100);
					//cout<<*it<<endl;
				}
				usleep(1000000);
				system("clear");
				cout<<"You can't abort the mission! Continue? (Y/N)"<<endl;
				char inYes = getch();
				//smallScreen.renderSmall(listLine, zoomScreen, bigScreen,0,0,0);

				//mvaddch(ya,xa,ch);
				switch(inYes){
				case 'y':
					system("clear");
					playUFO(4);
					stages[3]=1;
					//CLEAR ALL THE STAGE
					// system("clear");
					// stageMapX[0]=rand()%bigScreenWidth;
					// stageMapX[1]=rand()%bigScreenWidth;
					// stageMapX[2]=rand()%bigScreenWidth;
					// stageMapX[3]=rand()%bigScreenWidth;
					// stageMapX[4]=rand()%bigScreenWidth;
					// stageMapY[0]=rand()%bigScreenHeight;
					// stageMapY[1]=rand()%bigScreenHeight;
					// stageMapY[2]=rand()%bigScreenHeight;
					// stageMapY[3]=rand()%bigScreenHeight;
					// stageMapY[4]=rand()%bigScreenHeight;
					// listStageMap = list<LineDetails*>() ;
					// loopx=0;

					// for (int it = 0; it <4; it++) {
					// 	for (int it = 0; it <4; it++) {
					// 		int stage_increment = 0;
					// 		for (int i_it = 0; i_it <= it; i_it++ ){
					// 			listStageMap.push_back(new LineDetails(getRatio(stageMapX[it]), getRatio(stageMapY[it]+stage_increment), getRatio(stageMapX[it]+5), getRatio(stageMapY[it]+stage_increment)));
					// 			stage_increment += 2;
					// 		}
					// 	}

					// 	listStageMap.push_back(new LineDetails(getRatio(stageMapX[it]), getRatio(stageMapY[it]-2), getRatio(stageMapX[it]+4), getRatio(stageMapY[it]-2)));
					// 	listStageMap.push_back(new LineDetails(getRatio(stageMapX[it]), getRatio(stageMapY[it]-2), getRatio(stageMapX[it]+1), getRatio(stageMapY[it]-3)));
					// 	listStageMap.push_back(new LineDetails(getRatio(stageMapX[it]+1), getRatio(stageMapY[it]-3), getRatio(stageMapX[it]+3), getRatio(stageMapY[it]-3)));
					// 	listStageMap.push_back(new LineDetails(getRatio(stageMapX[it]+3), getRatio(stageMapY[it]-3), getRatio(stageMapX[it]+4), getRatio(stageMapY[it]-2)));
					// 	listStageMap.push_back(new LineDetails(getRatio(stageMapX[it]+3), getRatio(stageMapY[it]-3), getRatio(stageMapX[it]+3), getRatio(stageMapY[it]-4)));
					// 	listStageMap.push_back(new LineDetails(getRatio(stageMapX[it]+1), getRatio(stageMapY[it]-4), getRatio(stageMapX[it]+1), getRatio(stageMapY[it]-3)));
					// 	listStageMap.push_back(new LineDetails(getRatio(stageMapX[it]+1), getRatio(stageMapY[it]-4), getRatio(stageMapX[it]+3), getRatio(stageMapY[it]-4)));
					// 
					for(list<LineDetails*>::iterator it = listEnding.begin(); it != listEnding.end(); it++) {
						printWords((*it),lineManager,100,100);
						//cout<<*it<<endl;

					}
					usleep(100000000);
					break;
				
					
				case 'n' : system("clear");
				}
			} else {

				//YOU'RE NOT READYg
				list<LineDetails*> listLineStage1;
				fstream filestage("notready.txt", std::ios_base::in);
				list<int> intListStage1;

				int movestage1;
				//	Line lineManager;
			   	while (filestage >> movestage1){
					intListStage1.push_back(movestage1);
					//cout<<yow<<endl;
				}
				filestage.close();

			    int* tempstage1 = new int[4];

				int loopstage1 = 0;
			    	for (std::list<int>::iterator it = intListStage1.begin(); it != intListStage1.end(); ++it) {
					tempstage1[loopstage1] = *it;
					loopstage1++;
					if (loopstage1 == 4) {
						listLineStage1.push_back(new LineDetails(getRatio(tempstage1[0]), getRatio(tempstage1[1]), getRatio(tempstage1[2]), getRatio(tempstage1[3])));
						loopstage1 = 0;
					}
				}

				system("clear");
				for(list<LineDetails*>::iterator it = listLineStage1.begin(); it != listLineStage1.end(); it++) {
					printWords((*it),lineManager,100,500);
					//cout<<*it<<endl;
				}
				usleep(1000000);
			}
		}
		refresh();
	}
	delete []temp;
	delete []tempT;

	return 0;
}
