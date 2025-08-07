#include<stdio.h>
// function declaration for display and sparseAddition
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
        {3,3,4},
        {0,1,2},
        {2,0,3},
        {2,2,4}
    };
	
    // sparse matrix C
    int sparseC[][3] = {
	{3,3,4},
	{0,0,3},
	{0,2,4},
	{1,0,5},
	{1,1,7}
    };
    
    // sparse Sum matrix
    int sparseSum[][3]={0};
    

    // function call to display sparseA matrix
    int sizeOfSparseA = sizeof(sparseA)/sizeof(sparseA[0]);
    printf("sparse matrix A \n");
    display(sparseA,sizeOfSparseA,3);

    int sizeOfSparseB = sizeof(sparseB)/sizeof(sparseB[0]);
    printf("sparse matrix B \n");
    display(sparseB,sizeOfSparseB,3);

	
    int sizeOfSparseC= sparseC[0][2];
    display(sparseC,sizeOfSparseC,3);


    printf("\nsparse addition \n");
    sparseAddition(sparseA, sparseB, sparseC,sparseSum); // function call for the addition

    int sizeOfSparseSum = sparseSum[0][2];
    display(sparseSum,sizeOfSparseSum,3);

    return 0;
}
i
// function to display matrix
void display(int matrix[][3], int row , int col){

    for(int i=0 ; i<row ; i++){
        for(int j=0 ; j<col ; j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n"); // line break after each row for visualizing actual form of matrix
    }
}

void sparseAddition(int sparseA[][3], int sparseB[][3], int sparseC[][3],int sparseSum[][3]){
	
	sparseSum[0][0] = sparseA[0][0]; // setting the row 
	sparseSum[0][1] = sparseA[0][1]; // setting the col // both are same for all the 3 matrix
	
	int NonZeroInSparseA = sparseA[0][2];  // number of non zero elements in sparse matrix A
	int NonZeroInSparseB = sparseB[0][2];  // in sparse matrix B
	int NonZeroInSparseC = sparseC[0][2]; // in sparse matrix C
					      

	int sparseA_index = 1 , sparseB_index = 1, sparseC_index = 1, sparseSum_index = 1 ;
	// setting the index for accessing the location . first row consist of row and column details . that's why assigned as 1 .
	
	// loop is only work when all the indexing of sparse matrixes are less than or equal to the nonzero elements.
	while (sparseA_index <= NonZeroInSparseA &&
	       sparseB_index <= NonZeroInSparseB && 
	       sparseC_index <= NonZeroInSparseC
	      ){
		// sparse matrix contains the row col postion and value . which matrix have the lowest row col position (like [0][0]) will store first the sum matrix
		if(  sparseA[sparseA_index][0] < sparseB[sparseB_index][0] < sparseC[sparseC_index][0] 
						   || // comparing the row and checking sparse matrix A value is less or not (eg :sA -> [0][0] ,sB -> [1][0] )
			 (sparseA[sparseA_index][0] == sparseB[sparseB_index][0] == sparseC[sparseC_index][0] 
			 			   && // in case the row value's same check which one has the lower column value 
			 sparseA[sparseA_index][1] < sparseB[sparseB_index][1] < sparseC[sparseC_index][1] )  // check whether the colum is less or not ( eg : sA -> [0][0] sB -> [0][2] )
		  ){
		  		
		  		sparseSum[sparseSum_index][0] = sparseA[sparseA_index][0];
		  		sparseSum[sparseSum_index][1] = sparseA[sparseA_index][1];
		  		sparseSum[sparseSum_index][2] = sparseA[sparseA_index][2];		  	
		  		
		  		sparseA_index++ ;  // increment index pointers of sparse matrix A and C
		  		sparseSum_index++ ;
		  		
		  } 

		else if (  sparseB[sparseB_index][0] < sparseA[sparseA_index][0] < sparseC[sparseC_index][0] // comparing the row and checking sparseA element is less or not (eg :sA -> [2][1] ,sB -> [0][1])
				 			|| // when the row is same check whether the colum is less or not ( eg : sA -> [1] [2] sB -> [1] [0] )
			 (sparseA[sparseA_index][0] == sparseB[sparseB_index][0] == sparseC[sparseC_index][0]
						       &&
			     sparseB[sparseB_index][1] < sparseA[sparseA_index][1] < sparseC[sparseC_index][1])
		  			 
		  	){
		  		  	
		  		  	sparseSum[sparseSum_index][0] = sparseB[sparseB_index][0];
			  		sparseSum[sparseSum_index][1] = sparseB[sparseB_index][1];
			  		sparseSum[sparseSum_index][2] = sparseB[sparseB_index][2];	
		  		  
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
				sparseSum[sparseSum_index][0] = sparseA[sparseA_index][0];
		  		sparseSum[sparseSum_index][1] = sparseA[sparseA_index][1];
		  		sparseSum[sparseSum_index][2] = sparseA[sparseA_index][2];	
				
				sparseA_index++;
				sparseSum_index++;
		}
		
		// from sparse B
		while(sparseB_index <= NonZeroInSparseB){
				sparseSum[sparseSum_index][0] = sparseB[sparseB_index][0];
		  		sparseSum[sparseSum_index][1] = sparseB[sparseB_index][1];
		  		sparseSum[sparseSum_index][2] = sparseB[sparseB_index][2];	
				
				sparseB_index++;
				sparseSum_index++;
		}
		// from sparseC 
		while (sparseC_index <= NonZeroInSparseC){
				sparseSum[sparseSum_index][0] = sparseC[sparseC_index][0];
				sparseSum[sparseSum_index][1] = spasreC[sparseC_index][1];
				sparseSum[sparseSum_index][2] = sparseC[sparseC_index][2];

				sparseC_index++;
				sparseSum_index++;
		}
		

		//sparseC_index represents the number of non zero values in sparseC
		sparseSum[0][2]=sparseSum_index-1 ;
		
		
} // end of funciton sparseAddition

