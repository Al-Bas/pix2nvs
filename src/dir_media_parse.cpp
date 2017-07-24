#include "all_defines.h"

extern int tot_input;

struct MEDIA_FILE *dir_media_parse(struct MEDIA_FILE *media_file, char *dir_query)
{
	DIR *dp;
	struct dirent *ep;
	dp = opendir(INPUT_FOLDER);

	if (dp != NULL)
	{
		while (ep = readdir(dp))
		{
			for (int i = 0; i < TOT_MEDIA_TYPES; i++)
			{
				int useful_file = 0;

				if (strstr(ep->d_name, media_type[i]) != NULL) { useful_file = 1 ; }

				if (useful_file)
				{
					media_file[tot_input].filename = 
						(char *)calloc(MAX_STRING_SIZE, sizeof(char)) ;
					strcpy(media_file[tot_input].filename, ep->d_name) ;
					media_file[tot_input].extension = i ;
					if (tot_input == MAX_FILES - 1)
					{
						printf("\n\nWarning: more than %d media files detected, " 
							"stopping the directory parsing to the first %d.\n\n", 
							MAX_FILES, MAX_FILES) ;
						break;
					}
					tot_input++;
					break;
				}
			}
		}

		(void)closedir(dp);
	}
	else
		perror("Could not open ./input");

	return(media_file);
}
