#include <stdio.h>
#include <time.h>

int main(int argc, char** argv){
	
	char time_text[100];
	time_t now = time(NULL);
	struct tm *t = localtime(&now);
	strftime(time_text, sizeof(time_text)-1, "%Y-%d-%m %H:%M", t);
	
	FILE* fh = fopen("C:\\bin\\log.txt", "a");
	if (!fh)
		return 1;
	
	if(argc == 0)
	{
		fclose(fh);
		return 2;
	}
	
	fprintf(fh, "%s was called at %s with", argv[0], time_text);
	
	if(argc == 1)
	{
		fprintf(fh, " no parameters\n");
	} else {
		fprintf(fh, " %d parameters:\n", argc-1);
	}
	
	for (int i=1; i<argc; i++)
	{
		fprintf(fh, "  %s\n", argv[i]);
	}
	
	fprintf(fh, "\n");
	
	fclose(fh);
	
	return 0;
}