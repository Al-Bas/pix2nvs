# PIX2NVS: A Neuro-Morphic Vision Emulator 

Here we provide a straight-out-of-the-box implementation of **PIX2NVS**, a tool for converting RGB frames to Neurmorphic Vision data. 

A full description of the operation of the tool provided here can be found this paper by Yin Bi et. al.: 
> @inproceedings{auth,  arxiv link}

If you use this tool, please cite the paper above. This tool is provided under the [MIT license].

# Building from source
All dependencies are located in the source folder. To build from source, change your working directory to this repository's home folder and run:

```bash
g++ -o pix2nvs src/*.cpp  # to build from source  
./pix2nvs # to run using default parameters
```

##### Command-line options:

Option | Description

--reference or -r | set to (1, 2, or 3) to specify one of the reference frame update methods:
1: copy last input frame 
2: update reference frame using only generated events, without history decay 
3: update reference frame using only generated events, with history decay

--mexevents or -m | will specify the maximum number of events generated between two frames
--blocksize or -b | will set the block size for local inhibition
--adaptive  or -a | sets the co-efficient shift for adaptive thresholding, set to (0) to disable
--help      or -h | show usage syntax and parameter description

# Example Usage

- To extract events from videos located in the input folder:
  > ./pix2nvs -m 3 -a 0.05 -b 0
  All outputs will be located in the folder "Events"
 
 -- Add visualizing events
 -- Change frame extraction to libav
  
# Contact

For any any questions or bug reports, please contact Yin Bi at <yin.bi.16@ucl.ac.uk> or ALhabib Abbas at <alhabib.abbas.13@ucl.ac.uk>.
