#include<stdio.h>

void display(int matrix[][3], int row , int col);
void sparseAddition(int sparseA[][3], int sparseB[][3], int sparseC[][3]);

int main(){

    // sparse matrix A
    int sparseA[][3] = {
        {3,3,3},
        {0,0,1},
        {2,0,2},
        {2,2,3}
    };
    // sparse matrix B
    int sparseB[][3] = {
        {3,3,3},
        {0,1,2},
        {2,0,3},
        {2,2,4}
    };
	
    // sparse matrix C
    int sparseC[][3] ={
	{3,3,4},
	{0,0,3},
	{0,2,4},
	{1,0,5},
	{1,1,7}
   };

	

    int sparseTempSum[10][3]; // to store the sum of 2 matrix
    int sparseSum[15][3];
    

    // function call to display sparseA matrix
    int sizeOfSparseA = sizeof(sparseA)/sizeof(sparseA[0]);
    printf("\nsparse matrix A \n");
    display(sparseA,sizeOfSparseA,3);

    int sizeOfSparseB = sizeof(sparseB)/sizeof(sparseB[0]);
    printf("\nsparse matrix B \n");
    display(sparseB,sizeOfSparseB,3);

    int sizeOfSparseC = sparseC[0][2]+1;
    printf("\nsparse matrix C \n");
    display(sparseC,sizeOfSparseC,3);
    
    printf("\nsparse addition \n");
    sparseAddition(sparseA, sparseB, sparseTempSum);

    sparseAddition(sparseTempSum,sparseC,sparseSum);
    int sizeOfSparseSum = sparseSum[0][2] + 1 ;
    display(sparseSum,sizeOfSparseSum,3);




    return 0;
}

// function to display matrix
void display(int matrix[][3], int row , int col){

    for(int i=0 ; i<row ; i++){
        for(int j=0 ; j<col ; j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
}

void sparseAddition(int sparseA[][3], int sparseB[][3], int sparseC[][3]){
	
	sparseC[0][0] = sparseA[0][0];
	sparseC[0][1] = sparseA[0][1];
	
	int NonZeroInSparseA = sparseA[0][2];
	int NonZeroInSparseB = sparseB[0][2];
	
	int sparseA_index = 1 , sparseB_index = 1, sparseC_index = 1 ;
	
	while (sparseA_index <= NonZeroInSparseA && sparseB_index <= NonZeroInSparseB){
		
		if(  sparseA[sparseA_index][0] < sparseB[sparseB_index][0] || // comparing the row and checking sparseA element is less or not (eg :sA -> 0 0 ,sB -> 1 0 )
			(sparseA[sparseA_index][0] == sparseB[sparseB_index][0] && sparseA[sparseA_index][1] < sparseB[sparseB_index][1]) // check whether the colum is less or not ( eg : sA -> 0 0 sB -> 0 1 )
		  ){
		  	
		  		sparseC[sparseC_index][0] = sparseA[sparseA_index][0];
		  		sparseC[sparseC_index][1] = sparseA[sparseA_index][1];
		  		sparseC[sparseC_index][2] = sparseA[sparseA_index][2];		  	
		  		
		  		sparseA_index++ ;  // increment index pointers of sparse matrix A and C
		  		sparseC_index++ ;
		  		
		  } // end of if
		  else if (sparseB[sparseB_index][0] < sparseA[sparseA_index][0] // comparing the row and checking sparseA element is less or not (eg :sA -> 2 1 ,sB -> 0 1)
		  			|| // when the row is same check whether the colum is less or not ( eg : sA -> 1 2 sB -> 1 0 )
		   (sparseB[sparseB_index][0] == sparseA[sparseA_index][0]  &&  sparseB[sparseB_index][1] < sparseA[sparseA_index][1] ) 
		  			 
		  		  ){
		  		  	
		  		  	sparseC[sparseC_index][0] = sparseB[sparseB_index][0];
			  		sparseC[sparseC_index][1] = sparseB[sparseB_index][1];
			  		sparseC[sparseC_index][2] = sparseB[sparseB_index][2];	
		  		  
		  		  	sparseC_index++;
		  		  	sparseB_index++;
		  		 
		  		  } // end of else if
		  		  else {
		  		  	// if the row and column are same
		  		  	
		  		  	sparseC[sparseC_index][0] = sparseA[sparseA_index][0];
			  		sparseC[sparseC_index][1] = sparseA[sparseA_index][1];
			  		sparseC[sparseC_index][2] = sparseA[sparseA_index][2]+sparseB[sparseB_index][2];	
			  
			  		sparseA_index++;
			  		sparseB_index++;
			  		sparseC_index++;
				}// end of else;

		}// end of while 
		
		
		
		
		// add remaining values to the sparseC 
		// from sparse A
		while(sparseA_index <= NonZeroInSparseA){
				sparseC[sparseC_index][0] = sparseA[sparseA_index][0];
		  		sparseC[sparseC_index][1] = sparseA[sparseA_index][1];
		  		sparseC[sparseC_index][2] = sparseA[sparseA_index][2];	
				
				sparseA_index++;
				sparseC_index++;
		}
		
		// from sparse B
		while(sparseB_index <= NonZeroInSparseB){
				sparseC[sparseC_index][0] = sparseB[sparseB_index][0];
		  		sparseC[sparseC_index][1] = sparseB[sparseB_index][1];
		  		sparseC[sparseC_index][2] = sparseB[sparseB_index][2];	
				
				sparseB_index++;
				sparseC_index++;
		}
		//sparseC_index represents the number of non zero values in sparseC
		sparseC[0][2]=sparseC_index-1 ;
		
		
} // end of funciton sparseAddition

