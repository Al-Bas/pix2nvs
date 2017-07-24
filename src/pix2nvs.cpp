
#include "all_defines.h"
using namespace std ;

int tot_input = 0 ; int tot_pic_input = 0 ;

float d = DEFAULT_D ; int n_max = DEFAULT_N_MAX ;
float fixed_thres = DEFAULT_THRESHOLD ; int blocksize = DEFAULT_BLOCKSIZE ;
float adapt_thres_coef_shift = DEFAULT_ADAPT_THRES_COEF_SHIFT ;


int main(int argc, char *argv[])
{

	int status ; char *cmd ; struct MEDIA_FILE *media_file ;

	/* Parse user input */
	Helper::parse_input(argc, argv, &d, &fixed_thres, 
		&adapt_thres_coef_shift, &n_max, &blocksize) ;
        check_arguments(d, n_max, fixed_thres, adapt_thres_coef_shift, blocksize);
        
	
	cmd = (char *)calloc(MAX_STRING_SIZE, sizeof(char));
	media_file = (struct MEDIA_FILE *)calloc(MAX_FILES, sizeof(struct MEDIA_FILE));

	/* Create a log file */
	char *logfileName = (char *)calloc(MAX_STRING_SIZE, sizeof(char)) ;
	sprintf(logfileName, "nvs_log.txt") ; FILE *logfile = Helper::openFile(logfileName) ;
	
	// Check whether input folder exists --
	// Helper::openFolder("input", false) ; 	

	/* Load input video details */
	media_file = dir_media_parse(media_file, NULL);
	fprintf(logfile, "\nFound %d files in the ./input directory \n", tot_input);

	/* Generate events for each video */
	for (int ivid = 0; ivid < tot_input; ivid++)
	{
		clock_t begin_video = clock();
		printf("\n\n processing video: %s ... ", media_file[ivid].filename);
		fprintf(logfile, "\n processing video: %s ... ", media_file[ivid].filename);

		struct MEDIA_FILE *pic_file;
		pic_file = (struct MEDIA_FILE *)calloc(MAX_FILES, sizeof(struct MEDIA_FILE));


		/* Check whether ffprobe exists & run */
		if (access("ffprobe", F_OK) == 0)
		{
			sprintf(cmd, "./ffprobe -show_streams \"%s%s\" > ImPer.txt 2> err", 
					INPUT_FOLDER, media_file[ivid].filename) ;
			system(cmd);
		}
		else
		{
			printf("\n /* ffprobe binary does not exist.. refer to"
				       " the README file") ; exit(-1) ;
		}

		/* Get video parameters */
		struct VIDEO_PER video_per;
		video_per.FrameRate = (char *)calloc(MAX_STRING_SIZE, sizeof(char));
		video_per = get_video_per(video_per);


		/* Check temporary frames folder*/
		Helper::openFolder(TMP_FOLDER, false) ;
		fprintf(stdout, "\nExtracting frame from %s at %s\n", media_file[ivid].filename, 
			video_per.FrameRate) ;

		sprintf(cmd, "./ffmpeg -i \"%s%s\" -r %s %s/frame%%d.bmp > null 2> err", 
				INPUT_FOLDER, media_file[ivid].filename, video_per.FrameRate, 
				TMP_FOLDER) ; system(cmd);

		// Log time
		clock_t end_ffmpeg = clock();
		double time_spent = (end_ffmpeg - begin_video) / CLOCKS_PER_SEC;
		fprintf(logfile, "Finished FFMPEG for vid %d in %f seconds\n", ivid, time_spent);


		/* Count the number of frames */
		pic_file = dir_pic_parse(pic_file, NULL);
		printf("\n Found %d pictures in the ./tmp directory", tot_pic_input);
		fprintf(logfile, "\n Found %d pictures in the ./tmp directory", tot_pic_input);

		/* Check whether video is corrupted or empty */
		if (tot_pic_input == 0)
		{
			printf("\n %s is corrupted or empty, this video will be skipped.", 
				media_file[ivid].filename);
			fprintf(logfile, "\n %s is corrupted or empty, this video will be skipped.\n ", 
				media_file[ivid].filename);
		}
		else
		{

			/* Event generation  */

			status = generate_events(pic_file, video_per.TimeGap, media_file, 
					ivid, video_per.ImageWidth, video_per.ImageHeight);

			fprintf(logfile, "\n Generating events successfully for %s .... \n\n", 
				media_file[ivid].filename);

		}

		// Log time
		clock_t end_generate_events = clock();
		time_spent = (end_generate_events - end_ffmpeg) / CLOCKS_PER_SEC;
		fprintf(logfile, "Finished GEN_EVENT for vid %d in %f seconds\n", ivid, time_spent);

		// Clear temporary folder
		Helper::openFolder(TMP_FOLDER, true) ;

		// Free memory
		for (int i = 0; i < MAX_FILES; i++)
		{
			free(pic_file[i].filename);
		}
		free(pic_file) ; free(video_per.FrameRate) ;



	}

	fclose(logfile);
	// Free memory
	for (int i = 0; i < MAX_FILES; i++)
	{
		free(media_file[i].filename);
	}
	free(media_file);


	free(cmd);


}

