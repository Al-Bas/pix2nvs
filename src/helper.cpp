       
#include "all_defines.h"
struct stat info ;

void Helper::openFolder(const char *fn, bool clear){
	// Allocate CMD 
        char* cmd ; cmd = (char *)calloc(MAX_STRING_SIZE, sizeof(char)) ;
	fprintf(stderr, "\nCreating folder %s ..", fn) ;
	// Create events directory
        if(stat(fn, &info) != 0){ sprintf(cmd, "mkdir %s", fn) ; system(cmd) ; }
	else if (clear) { sprintf(cmd, "rm -rf %s/*", fn) ;      system(cmd) ; }
        }

FILE *Helper::openFile(char *fn){
        FILE *f = fopen(fn, "wt") ;
        if (f == NULL) { printf("File %s could not be created.\n", fn) ; exit(-1) ; }
	else { return f ; }
	}

void Helper::parse_input(int argc, char *argv[], float *d, float *fixed_thres,   
                float *adapt_thres_coef_shift, int *n_max, int *blocksize) {
	if (argc < 3)
	{
		printf("\n Run the default parameters");
	}

	int w ; // enum option {r, n, f, a, b} ;
	for (w = 1; w < argc; ++w)
	{

		switch (argv[w][0])
		{
		case 'r':  *d = atof(argv[(++w)]);                            break;
		case 'n':  *n_max = atoi(argv[(++w)]);                        break;
		case 'f':  *fixed_thres = atof(argv[(++w)]);                  break;
		case 'a':  *adapt_thres_coef_shift = atof(argv[(++w)]);       break;
		case 'b':  *blocksize = atoi(argv[(++w)]);                    break;
		}
	}
	fprintf(stderr, "argc= %d ; ", argc);
	fprintf(stderr, "D= %f ; ", *d);
	fprintf(stderr, "N_MAX= %d\n", *n_max);
	fprintf(stderr, "Fixed_Thres= %f ; ", *fixed_thres);
	fprintf(stderr, "Adapt_Thres_Coef_Shift= %f ; ", *adapt_thres_coef_shift);
	fprintf(stderr, "CompBlock= %d\n", *blocksize);

}


