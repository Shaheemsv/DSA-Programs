 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 #include <stdbool.h>
 

// Maintain record Alphabetical order . sort using bubble sort.
// Given a student name display his details using binary search.

struct studentDetails	// to store the student details 
{
    char name[25];
    int regno;
    float cgpa;
};

// function declarations
void displayDetails(struct studentDetails stud[], int limit);
void bubbleSort(struct studentDetails stud[], int limit);
//void binarySearch(struct studentDetails stud[], int low,int high);
int binarySearch(struct studentDetails stud[], int limit, char *name);


int main()
{

    FILE *fptr = fopen("StudentDetails.txt", "r");	// file pointer open the file
	
	if (fptr == NULL) {
    	printf("Error opening file");
    	return 1;
	}
	
    struct studentDetails std[10];		// array of structures to student details
	struct studentDetails stdCopy[10];	
	
	// reading the details from the file and storing to the file
    int i = 0;
    
    while (fscanf(fptr, "%s %d %f", std[i].name, &std[i].regno, &std[i].cgpa) != EOF)
        i++;
        
	memcpy(stdCopy, std, sizeof(std));


    fclose(fptr);	// closing the file
	
	int choice ;
	int isSorted = 0;
	
	do{
	
	printf("List of Operations \n-------------------\n1. View Student Details (Unsorted) \n2. View Sorted Student List \n3. Search \n4. Exit \n\n");
	
	printf("Enter your choice (1-4) : ");
	scanf("%d",&choice);
	
	
	switch(choice){
		case 1 :
			printf("\nStudent Details \n--------------------\n");	
    		displayDetails(std, i);
    		break ;
    	case 2 :
    		bubbleSort(stdCopy,i); // calling sort function
    		isSorted = 1;
    		
    		printf("\nSorted Student List \n------------------\n");
			displayDetails(stdCopy,i);
    		break ;
    	case 3 :
    		//search(std,i);	// function to search name
    		//binarySearch(std,0,i);
    			
    		if(!isSorted){
    			bubbleSort(stdCopy,i);
    			isSorted=1;
    		}
    		char searchName[25];
    		
    		printf("Enter the name to search : ");
    		scanf("%s",searchName);
    		
    		int index = binarySearch(stdCopy,i,searchName);
    		
    		if(index != -1){
  				printf("\n\"Student founded...\"\n\nName : %s \nReg No : %d \nCGPA : %.2f \n\n",stdCopy[index].name,stdCopy[index].regno, stdCopy[index].cgpa);
  			}else{
			    printf("\nStudent not found!\n");
            }
            			
    		break;
		case 4 :
			printf("Exited....\n");
			exit(0);
			break;
		default :
			printf("Invalid input Try again...!\n");
			return 1;
	}
	
	
    }while(choice!=4);
	
	
	
    return 0;
}

// function to display Array 
void displayDetails(struct studentDetails stud[], int limit)
{

    for (int i = 0; i < limit; i++)
    {
        printf("Name : %s\n", stud[i].name);
        printf("Reg No : %d\n", stud[i].regno);
        printf("cgpa : %.2f\n\n", stud[i].cgpa);
    }
}

// function to sort names in alphabetical order
void bubbleSort(struct studentDetails stud[], int limit){

	struct studentDetails temp;
	
	for(int i=0 ; i<limit-1 ; i++){
		for(int j=0 ; j<limit-i-1 ; j++){
		
			 if(strcmp(stud[j].name, stud[j+1].name) > 0){	// compare using strcmp function
			 	temp = stud[j];
			 	stud[j]=stud[j+1];
			 	stud[j+1]=temp;
			 
			 
			 /*
			 	// swapping processes done with the help of strcpy function
			 	strcpy(temp,stud[j].name);
			 	strcpy(stud[j].name,stud[j+1].name);
			 	strcpy(stud[j+1].name,temp);
			 */
			 }
		}
	}
	
	

}

int binarySearch(struct studentDetails stud[], int limit, char *name){
	
	int low = 0 , high = limit-1 ;
	
	while (low <= high){
		int mid = low +(high -low) / 2 ;
		
		int cmp = strcmp(stud[mid].name , name);
		
		if(cmp==0)
			return mid;
		else if (cmp < 0)
			low = mid+1;
		else 
			high = mid-1;
	}
	return -1;
}


/*
void binarySearch(struct studentDetails stud[], int low, int high ){

	char searchName[15];
	char temp[15];
	for(int i=0 ; i<high-1 ; i++){
		for(int j=0 ; j<high-i-1 ; j++){
		
			 if(strcmp(stud[j].name, stud[j+1].name) > 0){	// compare using strcmp function
			 
			 	// swapping processes done with the help of strcpy function
			 	strcpy(temp,stud[j].name);
			 	strcpy(stud[j].name,stud[j+1].name);
			 	strcpy(stud[j+1].name,temp);
			 	
			 }
		}
	}
	
	printf("Enter the name to Search : ");
	scanf("%s",searchName);
	
	while(low <= high){
		
		int mid = low + (high-low)/2; // set the middle 
		
		if(strcmp(stud[mid].name,searchName)==0){
			printf("\n\"Student founded...\"\n\nName : %s \nReg No : %d \nCGPA : %.2f \n\n",stud[mid].name,stud[mid].regno, stud[mid].cgpa);
			return;
		}
		
		if (strcmp(stud[mid].name,searchName) < 0)
			low = mid+1;
		else
			high = mid-1;		
		
		}
		
		
}

*/

// function to search student
/*
void search(struct studentDetails stud[], int limit){

	char searchName[15];
	
	printf("Enter the name to Search : ");
	scanf("%s",searchName);
	bool finded = false ;
	
	for(int i=0 ; i<limit ; i++){
	
		if(strcmp(stud[i].name,searchName)==0){
			printf("\n\"Student founded...\"\n\nName : %s \nReg No : %d \nCGPA : %.2f \n\n",stud[i].name,stud[i].regno, stud[i].cgpa);
			finded = true ;
			break;
		}
	}
	
	if(finded == false )
		printf("\n\"Student Not found...!\"\n\n");
		

}
*/


/*

ompare: Use strcmp(array_of_strings[mid], target_string) to compare the string at the middle index with the string being searched for.
If strcmp() returns 0, the strings are equal, and the target string is found at mid.
If strcmp() returns a negative value, array_of_strings[mid] is lexicographically less than target_string. The search continues in the right half: low = mid + 1;
If strcmp() returns a positive value, array_of_strings[mid] is lexicographically greater than target_string. The search continues in the left half: high = mid - 1; 


*/



