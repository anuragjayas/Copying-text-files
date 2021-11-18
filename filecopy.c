#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
 
#define BUF_SIZE 32768			//Buffersize is 2^15

int checkIfFileExists(const char *filename)
{
	struct stat buffer;
    	int exist = stat(filename,&buffer);
    	if(exist == 0)
        	return 1;
    	else
        	return 0;
}
 
int main(int argc, char* argv[])	//We want to return a number to check if evrything works fine 
{
 
    	int input_fd, output_fd;		//Assigning File descriptors
    	ssize_t bytes_rd,bytes_wr;    		//Number of bytes returned by the files
    	char buffer[BUF_SIZE];      		//Character buffer
 
    
    	if(argc != 3)		//To check that the file name arguments are missing
    	{
	    	printf ("Arguments not provided properly");
           	return 1;
    	}
 
    	input_fd = open (argv [1], O_RDONLY);		//Opening the input file
    	if (input_fd == -1) 				//If file doesn't exist than show error message
    	{
            	perror ("Error in opening input file");
            	return 2;
    	}
    
    	if (checkIfFileExists(argv[2]))		//To check whether output file exist or not
    	{
	    	int flag;
	    	printf("File Exist\n");
	    	printf("Press 0 to overwrite or press any other key to exit\n");
            	scanf("%d",&flag);
	    	if (flag==0)		//To overwrite the exixting file
	    	{
		    	if (remove(argv[2]) ==0)	//Deleting the data from existing file
		    	{
			    	printf("File Overwritten\n");
		    	}
	    	}
	    	else		//If the user doesn't want to overwrite exixting file
	    	{
			printf("File was not overwritten");
		    	return 3;
	    	}
    	}
 
    	output_fd = open(argv[2], O_WRONLY | O_CREAT, 0644);	//Creating output file
    	if(output_fd == -1)			//If file is not created than show error message
    	{
	    	perror("Error in creating output file");
            	return 4;
    	}
 
    	while((bytes_rd = read (input_fd, &buffer, BUF_SIZE)) > 0)		//Reading from input file and writing it in output file
    	{
            	bytes_wr = write (output_fd, &buffer, (ssize_t) bytes_rd);
            	if(bytes_wr != bytes_rd)
	    	{
                	perror("write");
                	return 5;
            	}
	    	else 
	    	{
		    	printf("File copied successfully\n");		//Process completion message
	    	}
    	}
 
    	close (input_fd);		//Closing input file descriptor
    	close (output_fd);		//Closing output file discriptor
 
    	return 0;
}
