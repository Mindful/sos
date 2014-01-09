#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int makeargv(const char *s, const char *delimiters, char ***argvp) {
	int error;
	int i;
	int numtokens;
	/*
	 * Note that const char * says the data is const, not the pointer.
	 */
	const char *snew;
	char *t;

	if ((s == NULL) || (delimiters == NULL) || argvp == NULL) {
		errno = EINVAL;
		return -1;
	}

	*argvp = NULL;
	/* skip any leading delimiters */
	snew = s + strspn(s, delimiters); //Calculate the number of leading characters that are delimeters, offset by that much
	if ((t = malloc(strlen(snew) + 1)) == NULL) //Reserve memory for the string starting from the end of the delimeters,
	//plus a null character because strlen() doesn't count the null
		return -1;
	strcpy(t, snew); //Copy the string snew into a new location t
	numtokens = 0; 
	if (strtok(t, delimiters) != NULL)
		for(numtokens = 1;  strtok(NULL, delimiters) != NULL; numtokens++) //Count delimeters by using strtok to find each
				;
	if ((*argvp = malloc((numtokens+1)*sizeof(char *))) == NULL) { 
		error = errno;
		free(t);
		errno = error;
		return -1;
	}

	if (numtokens == 0)
		free(t);
	else {
		strcpy(t, snew);
		**argvp = strtok(t, delimiters);
		for(i=1; i<numtokens; i++)
			*((*argvp)+i) = strtok(NULL, delimiters);
	}
	*((*argvp)+numtokens) = NULL;
	return numtokens;
}


int main(int argc, char *argv[]){
	char delim[] = " \t";
	int tokenCount;
	char** myargv;
	pid_t pid;
	char *newenviron[] = {NULL};

	if (argc!=2){
		fprintf(stderr, "Please pass in a single string");
	}

	tokenCount = makeargv(argv[1], delim, &myargv);

	if (tokenCount == -1){
		fprintf(stderr, "Failed to parse argument array");
		return 1;
	}

	pid = fork();
	if (pid == 0){
		printf("Child with PID: %u", getpid());
		execve(myargv[0], myargv, newenviron);
		perror("execve"); //Should never happen, because execve should overwrite this
		exit(EXIT_FAILURE);
	} else{
		wait(); //Don't print until our child is done
		printf("Parent with PID: %u and child PID: %u", getpid(), pid);
		exit(EXIT_FAILURE);
	}
	return 0;

}
