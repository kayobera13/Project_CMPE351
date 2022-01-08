#include<iostream>
#include <iterator>
#include<algorithm>
using namespace std;

void executionProcess(int *eProcesses, int eProcessTE, int etime){
	int counter=0; 
	for(int i=0; i<sizeof(eProcesses); i++){
		int *process = &eProcesses[i];
		//if(process[5]==0 && process[1]>=etime){
		//	process[5]=1;
		//}else{
			if(counter==eProcessTE){
				process[0]=process[0]-1;
				if(process[0]==0){
					process[4]==1;
				}
			}else{
				process[3]=process[3]+1;
			}
		//}
		counter++;
	}
}

int schedulingProcessChoice(int *scProcesses, int type){
	int processSelected =-1;
	int lowestProcess = 0;
	int counter=0;
	bool boolProcessSelected =false;
	for(int i=0; i<sizeof(scProcesses); i++){
		int *process = &scProcesses[i];
		if((boolProcessSelected=false && process[5]==1) || 
			(boolProcessSelected=true && process[5]==1 && process[4]==0 && process[type]<lowestProcess))
		{
				lowestProcess=process[type];
				processSelected=counter;
				boolProcessSelected=true;
		}
		counter++;
	}
}


void schedulingPreemptive(int *pProcesses, int type){
	bool tester=true;
	int time=0;
	while(tester==true){
		int processesToExecute=schedulingProcessChoice(pProcesses, type);
		if(processesToExecute==-1){
			tester=false;
		}
		else{
			executionProcess(pProcesses, processesToExecute, time);
		}
		time++;
	}
}

int p1[6]={5, 0, 3, 0, 0, 0};
int p2[6]={4, 1, 2, 0, 0, 0};
int p3[6]={3, 1, 1, 0, 0, 0};
int p4[6]={4, 2, 2, 0, 0, 0};
int p5[6]={3, 3, 1, 0, 0, 0};
int processes[5][6]={
	*p1,
	*p2,
	*p3,
	*p4,
	*p5
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
				int schedulingType;
				cout<<"Choose Between the five Scheduling Preemptinve Type \n";
				cout<<"1. None\n";
				cout<<"2. First Come, First Served Scheduling\n";
				cout<<"3. Shortest-Job-First Scheduling\n";
				cout<<"4. Priority Scheduling\n";
				cout<<"5. Round-Robin Scheduling\n";
				cin>>schedulingType;
				switch(schedulingType){
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
				}
				break;
			case 2:
				cout<<"case 2";
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

