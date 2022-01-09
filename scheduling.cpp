#include<iostream>
#include <iterator>
#include<algorithm>
using namespace std;

struct processStructure {
    // Array within the structure
    int processus[6];
};

void insertInqueue(processStructure *scProcesses, int etime){
	for(int i=0; i<5; i++){
	//	cout<<scProcesses[i].processus[0]<<"\n";
		int *process = scProcesses[i].processus;
		if(process[5]==0 && process[1]==etime){
			process[5]=1;
			cout<<i<<" In queue \n";
		}
	}
}

void executionProcess(processStructure *eProcesses, int eProcessTE){
	int counter=0; 
	cout<<"executionProcess start\n";
	for(int i=0; i<5; i++){
		
		int *process = eProcesses[i].processus;
		if (i==eProcessTE && process[4]==0){
			process[0]=process[0]-1;
			cout<<process[0]<<"Process \n";
			if(process[0]==0){
					process[4]=1;
			}
			cout<<process[4]<<"End \n";
		}else{
			process[3]=process[3]+1;
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
	int c;
	cin>>c;
}

int schedulingProcessChoice(processStructure *scProcesses, int type){
	int processSelected =-1;
	int lowestProcess = 0;
	int counter=0;
	bool boolProcessSelected =false;
	cout<<"schedulingProcessChoice start\n";
	//cout<<sizeof(scProcesses)<<"\n";
	for(int i=0; i<5; i++){
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
	cout<<processSelected<<"selected \n";
	return processSelected;
}



void schedulingPreemptive(processStructure *pProcesses, int type){
	bool tester=true;
	int time=0;
	cout<<"schedulingPreemptive start\n";
	while(tester==true){
		insertInqueue(pProcesses, time);
		int processesToExecute=schedulingProcessChoice(pProcesses, type);
		if(processesToExecute==-1){
			tester=false;
		}
		else{
			executionProcess(pProcesses, processesToExecute);
			time++;
		}
		
	}
	cout<<"Scheduling Finish\n";
	cout<<time<<"time\n";
}

void schedulingNonPreemptive(processStructure *pProcesses, int type){
	bool tester=true;
	int time=0;
	cout<<"schedulingNonPreemptive start\n";
	insertInqueue(pProcesses, time);
	while(tester==true){
		int processesToExecute=schedulingProcessChoice(pProcesses, type);
		if(processesToExecute==-1){
			tester=false;
		}
		else{
			int *process = pProcesses[processesToExecute].processus;
			while(process[4]==0){
				executionProcess(pProcesses, processesToExecute);
				time++;
				insertInqueue(pProcesses, time);
			}
			cout<<process[4]<<"Finish\n";
		}
	}
	cout<<"Scheduling Finish\n";
	cout<<time<<"time\n";
}
/*
int p1[6]={5, 0, 3, 0, 0, 0};
int p2[6]={4, 1, 2, 0, 0, 0};
int p3[6]={3, 1, 1, 0, 0, 0};
int p4[6]={4, 2, 2, 0, 0, 0};
int p5[6]={3, 3, 1, 0, 0, 0};
*/

struct processStructure P1 = { {5, 0, 3, 0, 0, 0} };
struct processStructure P2 = { {4, 1, 2, 0, 0, 0}};
struct processStructure P3 = {{3, 1, 1, 0, 0, 0} };
struct processStructure P4 = { {4, 2, 2, 0, 0, 0} };
struct processStructure P5 = { {3, 3, 1, 0, 0, 0} };

processStructure processes[5]={
	P1,
	P2,
	P3,
	P4,
	P5
};
  
  int main ()
{
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
			case 1:
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
						schedulingPreemptive(processes, 1);
						
						break;
					case 3:
						cout<<"Shortest-Job-First Scheduling\n";
						schedulingPreemptive(processes, 0);
						break;
					case 4:
						cout<<"Priority Scheduling\n";
						schedulingPreemptive(processes, 2);
						break;
					case 5:
						cout<<"Round-Robin Scheduling\n";
						break;
					default:
						cout<<"you have to choose between 1 - 5";
					break;
				}
				break;
			case 2:
				int nonPreemptiveSchedulingType;
				cout<<"Choose Between the five Scheduling Non Preemptinve Type \n";
				cout<<"1. None\n";
				cout<<"2. First Come, First Served Scheduling\n";
				cout<<"3. Shortest-Job-First Scheduling\n";
				cout<<"4. Priority Scheduling\n";
				cin>>nonPreemptiveSchedulingType;
				switch(nonPreemptiveSchedulingType){
					case 1:
						cout<<"None\n";
						break;
					case 2:
						cout<<"First Come, First Served Scheduling\n";
						schedulingNonPreemptive(processes, 1);
						
						break;
					case 3:
						cout<<"Shortest-Job-First Scheduling\n";
						schedulingNonPreemptive(processes, 0);
						break;
					case 4:
						cout<<"Priority Scheduling\n";
						schedulingNonPreemptive(processes, 2);
						break;
					default:
						cout<<"you have to choose between 1 - 4";
					break;
				}
				break;
			case 3:
				cout<<"case 3";
				break;
			case 4:
				cout<<"case 4";
				finish=true;
				break;
			default:
				cout<<"you have to choose between 1 - 4";
				break;
		}
		//i++;
	}

	
   
	return 0;
}

