#include <vector>
#include<iostream>
#include <iterator>
#include<algorithm>
#include <getopt.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

struct processStructure {
    // Array within the structure
    int processus[6];
};

void insertInqueue(processStructure *scProcesses, int etime, int nbreline){
	for(int i=0; i<nbreline; i++){
	//	cout<<scProcesses[i].processus[0]<<"\n";
		int *process = scProcesses[i].processus;
		if(process[5]==0 && process[1]==etime){
			process[5]=1;
			//cout<<i<<" In queue \n";
		}
	}
}

void executionProcess(processStructure *eProcesses, int eProcessTE, int nbreline){
	int counter=0; 
	//cout<<"executionProcess start\n";
	for(int i=0; i<nbreline; i++){
		
		int *process = eProcesses[i].processus;
		if (i==eProcessTE && process[4]==0){
			process[0]=process[0]-1;
			//cout<<process[0]<<"Process \n";
			if(process[0]==0){
					process[4]=1;
			}
			//cout<<process[4]<<"End \n";
		}else if(process[5]==1 && process[4]==0){
			process[3]=process[3]+1;
			//cout<<process[3]<<"Waiting \n";
		}else{
			
		}
		
		/*if(process[5]==0 && process[1]>=etime){
			process[5]=1;
		}else{
			if(counter==eProcessTE){
				process[0]=process[0]-1;
				if(process[0]==0){
					process[4]==1;
				}
			}else{
				process[3]=process[3]+1;
			}
		}*/
		counter++;
	}
	//int c;
	//cin>>c;
}

int schedulingProcessChoice(processStructure *scProcesses, int type, int nbreline){
	int processSelected =-1;
	int lowestProcess = 0;
	int counter=0;
	bool boolProcessSelected =false;
	//cout<<"schedulingProcessChoice start\n";
	//cout<<sizeof(scProcesses)<<"\n";
	for(int i=0; i<nbreline; i++){
	//	cout<<scProcesses[i].processus[0]<<"\n";
		int *process = scProcesses[i].processus;
		
		if((boolProcessSelected==false && process[5]==1 && process[4]==0) || 
			(boolProcessSelected==true && process[5]==1 && process[4]==0 && process[type]<lowestProcess))
		{
				lowestProcess=process[type];
				processSelected=counter;
				boolProcessSelected=true;
		}
		counter++;
	}
	//cout<<processSelected<<"selected \n";
	return processSelected;
}



void schedulingPreemptive(processStructure *pProcesses, int type, int nbreline){
	bool tester=true;
	int time=0;
	cout<<"schedulingPreemptive start\n";
	while(tester==true){
		insertInqueue(pProcesses, time, nbreline);
		int processesToExecute=schedulingProcessChoice(pProcesses, type, nbreline);
		if(processesToExecute==-1){
			tester=false;
		}
		else{
			executionProcess(pProcesses, processesToExecute, nbreline);
			time++;
		}
		
	}
	cout<<"Scheduling Finish\n";
	cout<<time<<"time\n";
}

void schedulingNonPreemptive(processStructure *pProcesses, int type, int nbreline){
	bool tester=true;
	int time=0;
	cout<<"schedulingNonPreemptive start\n";
	insertInqueue(pProcesses, time,nbreline);
	while(tester==true){
		int processesToExecute=schedulingProcessChoice(pProcesses, type, nbreline);
		if(processesToExecute==-1){
			tester=false;
		}
		else{
			int *process = pProcesses[processesToExecute].processus;
			while(process[4]==0){
				executionProcess(pProcesses, processesToExecute, nbreline);
				time++;
				insertInqueue(pProcesses, time, nbreline);
			}
			//cout<<process[4]<<"Finish\n";
		}
	}
	cout<<"Scheduling Finish\n";
	cout<<time<<"time\n";
}

void schedulingRoundRobin(processStructure *pProcesses, int quantum, int nbreline){
	bool tester=true;
	int time=0;
	cout<<"schedulingRoundRobin start\n";
	insertInqueue(pProcesses, time, nbreline);
	int processListSize=nbreline;
	int currentprocess=0;
	while(tester==true){
		for(int i=0; i<quantum; i++){
			int processesToExecute=schedulingProcessChoice(pProcesses, 1, nbreline);
			int *process = pProcesses[currentprocess].processus;
			if(processesToExecute==-1){
				tester=false;
				break;
			}
			else if(process[4]==1){
				break;
			}
			else{
				executionProcess(pProcesses, currentprocess, nbreline);
				insertInqueue(pProcesses, time, nbreline);
				time++;
			}
			
		}
		currentprocess++;
		if(currentprocess==processListSize){
			currentprocess=0;
		}
	}
}

float getAverage(processStructure *pProcesses, int nbreline){
	int sum=0;
	for(int i=0; i<nbreline; i++){
		int *process = pProcesses[i].processus;
		sum=sum+process[3];
	}
	return (sum/5);
}
void showWaitingTime(processStructure *pProcesses, int nbreline){
	for(int i=0; i<nbreline; i++){
		int *process = pProcesses[i].processus;
		cout<<"P"<<i+1<<": "<<process[3]<<"ms \n";
	}
}


void writeFile(string output){
// Create and open a text file
	ofstream files;
	files.open(output);
					  
	cout<<"ENTER YOUR MESSAGE";

	files<<"Average :"<<"ms \n";

					  //We need to close every file which you open.
	files.close();	
}


char *input=NULL;
char *output=NULL;
  
  int main (int argc, char *argv[])
{
	int c;

	if(argc<2){
		cout<<"You should introduce 2 arguments";
		exit(0);
	}
	
	while((c = getopt(argc, argv, "f:o:")) != -1){
		switch (c){
			case 'f':
				input=optarg;
				break;
			case 'o':
				output=optarg;
				break;
			default:
				break;
		}
	}
	
	if(input==NULL || output==NULL){
		cout<<"use the parameter u for input and o for output";
		exit(0);
	}
	int nbreofline=0;
	vector<processStructure> tempArray{};

	std::ifstream file(input);
	std::string str;
	while(std::getline(file, str)){
		vector<string> words{};
		string delimiter=":";
		//cout<< str<<"\n";
		int pos;
		string text=str;
		
		while((pos = text.find(delimiter))!= string::npos){
			words.push_back(text.substr(0, pos));
			text.erase(0, pos+delimiter.length());
		}
		int p[6];
		int count=0;
		for(const auto &str :words){
			p[count]=stoi(str);
			count++;
		}
		p[2]=stoi(text); p[3]=0; p[4]=0; p[5]=0;
		 processStructure S1={{p[0],p[1],p[2],p[3],p[4],p[5]}};
		tempArray.push_back(S1);
		nbreofline++;
	}
	
	processStructure processes[nbreofline];
	int j=0;
	for(const auto &ar: tempArray){
		processes[j]=ar;
		j++;
	}	
	
	
	int userAction;
	int i=0;
	bool finish=false;
	while(finish==false){
		cout<<"Choose Action : \n";
		cout<<"1. Scheduling Preemptinve\n";
		cout<<"2. Scheduling Non-Preemptinve\n";
		cout<<"3. Show Result\n";
		cout<<"4. End Program\n";
		cin>>userAction;
		
		switch(userAction){
			case 1:{
				int preemptiveSchedulingType;
				cout<<"Choose Between the five Scheduling Preemptinve Type \n";
				cout<<"1. None\n";
				cout<<"2. First Come, First Served Scheduling\n";
				cout<<"3. Shortest-Job-First Scheduling\n";
				cout<<"4. Priority Scheduling\n";
				cout<<"5. Round-Robin Scheduling\n";
				cin>>preemptiveSchedulingType;
				switch(preemptiveSchedulingType){
					case 1:
						cout<<"None\n";
						break;
					case 2:
						cout<<"First Come, First Served Scheduling\n";
						schedulingPreemptive(processes, 1, nbreofline);
						break;
					case 3:
						cout<<"Shortest-Job-First Scheduling\n";
						schedulingPreemptive(processes, 0, nbreofline);
						break;
					case 4:
						cout<<"Priority Scheduling\n";
						schedulingPreemptive(processes, 2, nbreofline);
						break;
					case 5:
						cout<<"Round-Robin Scheduling\n";
						cout<<"Insert Quantum\n";
						int quantum;
						cin>>quantum;
						schedulingRoundRobin(processes, quantum, nbreofline);
						break;
					default:
						cout<<"you have to choose between 1 - 5";
					break;
				}
				
			}
				break;
			case 2:{
				int nonPreemptiveSchedulingType;
				cout<<"Choose Between the five Scheduling Non Preemptinve Type \n";
				cout<<"1. None\n";
				cout<<"2. First Come, First Served Scheduling\n";
				cout<<"3. Shortest-Job-First Scheduling\n";
				cout<<"4. Priority Scheduling\n";
				cin>>nonPreemptiveSchedulingType;
				switch(nonPreemptiveSchedulingType){
					case 1:
						cout<<"None Scheduling method choosen try again \n";
						break;
					case 2:
						cout<<"First Come, First Served Scheduling\n";
						schedulingNonPreemptive(processes, 1, nbreofline);
						
						break;
					case 3:
						cout<<"Shortest-Job-First Scheduling\n";
						schedulingNonPreemptive(processes, 0, nbreofline);
						break;
					case 4:
						cout<<"Priority Scheduling\n";
						schedulingNonPreemptive(processes, 2, nbreofline);
						break;
					default:
						cout<<"you have to choose between 1 - 4";
					break;
				}
				
			}
				break;
			case 3:{
				cout<<"The Result is:\n";
				cout<<"Processes waiting Time \n";
				float average;
				average= getAverage(processes, nbreofline);
				showWaitingTime(processes, nbreofline);
				cout<<"Average :"<<average<<"ms \n";
				}
				
				break;
			case 4:{
				cout<<"Exit Program, Thank you  \n";
				float averages;
				averages= getAverage(processes, nbreofline);
		
				ofstream file;
				file.open(output);
									  
				file<<"Processes waiting Time \n";
				for(int i=0; i<nbreofline; i++){
					int *process = processes[i].processus;
					file<<"P"<<i+1<<": "<<process[3]<<"ms \n";
				}

				file<<"Average :"<< averages <<"ms \n";

									  //We need to close every file which you open.
				file.close();	
				 	
					
				finish=true;
			}
				
				break;
			default: 
				cout<<"you have to choose between 1 - 4";
				break;
		}
		//i++;
	}

	
   
	return 0;
}

