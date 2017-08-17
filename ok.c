# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <errno.h>
# include  <fcntl.h>
# include <unistd.h>
# define LEN 16																				// Length of the words in this dictionary

int ok (int fd, char* word);													// Search for the word

/* ********** MAIN FUNCTION ********** */
int main(int argc, char* argv[])
{
	char fileName[100] = "/encs_share/cs/class/cs360/lib/webster";			// on ENCS Machine
//	char fileName[100] = "webster";											// on my local Machine
	int fd = open(fileName, O_RDONLY);									// open(  char  *filename,  int  access,  int  permission  )

	if(fd == -1)
	{
		fprintf (stderr, "\tError! Unable to open the file.\n");
		exit(1);
	}
	if (argc != 2)
	{
		fprintf (stderr, "\tError! Wrong number of command line arguments.\n");
		exit(1);
	}
	if (strlen(argv[1]) > LEN)													// Dictionary only has the maximum length of letter of 16
	{
		fprintf (stderr, "\tThis Dictionary doesn't contain any word longer than 16 letters.\n");
		exit(1);
	}
	char word[LEN];																			// I can use argv[1] directly, but this makes coding much simpler
	strcpy(word, argv[1]);
	
	if (ok(fd,word)==0)		printf("no\n");								// serach the word returns Not Found
	else									printf("yes\n");							// serach the word returns Found

	close(fd);
	return 0;
}

/* ********** OK FUNCTION ********** */
int ok (int fd, char* word)
{
	char have[LEN];																			// a temporary string which holds mid on each read
	int top = 0, mid;
	int bot = (lseek(fd, 0, SEEK_END)) / LEN;						// get the number of the last line
	word[LEN-1]='\0';
	for(int i=strlen(word); i<LEN-2; i++)	word[i] = ' ';// adding extra spaces to the end of the word, for comparison
	while (bot > top)																		// if search range empty, then Not Found
	{
		mid = (bot+top)/2;																// find the mid line
		lseek(fd, mid*LEN, SEEK_SET);											// go to the mid line
		read(fd, have, LEN);															// read the mid line into have		read(  int  handle,  void  *buffer,  int  nbyte )
		have[LEN-2] = '\0';																// null terminator makes it possible to use strcmp later
//printf ("MID= %i HAVE= ---%s--- WORD= ---%s---\n", mid, have, word); //************************** FOR DEBUG
//printf ("MID= %i    TOP= %i    BOT= %i \n", mid, top, bot); //************************** FOR DEBUG
		if (strcmp(have, word) == 0)			return 1;				// we found the string and we are done
		else if (strcmp(word, have) < 0)	bot = mid;			// if word is less than have
		else															top = mid + 1;	// if word is greater than have
	}
	return 0;
}

