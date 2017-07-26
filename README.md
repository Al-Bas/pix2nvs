# PIX2NVS: A Neuro-Morphic Vision Emulator 

Here we provide a straight-out-of-the-box implementation of **PIX2NVS**, a tool for converting RGB frames to Neurmorphic Vision data. 

A full description of the operation of the tool provided here can be found this paper by Yin Bi et. al.: 
> @inproceedings{auth,  arxiv link}

If you use this tool, please cite the paper above. This tool is provided under the [MIT license].

# Contact

For any any questions or bug reports, please contact Yin Bi at <yin.bi.16@ucl.ac.uk> or ALhabib Abbas at <alhabib.abbas.13@ucl.ac.uk>.

Below is a visualization of some flow maps of MPI Sintel's *alley_1* sequence:

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

##### Command-line options:

Option | Description
--- | ---
--help or -h | will output the usage info
--occupancy | will expect occupancy information from **mpegflow** and will visualize it as well

# Examples

- To extract motion vectors:
  > ./mpegflow examples/mpi_sintel_final_alley_1.avi > examples/alley_1.txt

- To visualize motion vectors:
  > mkdir -p examples/vis_dump && ./mpegflow examples/mpi_sintel_final_alley_1.avi | ./vis examples/mpi_sintel_final_alley_1.avi examples/vis_dump

Feel free to copy-paste and run the examples above. More runnable examples are in ```examples/extract_motion_vectors.sh``` and ```examples/vis_motion_vectors.sh```. Feel free to use ```vis.cpp``` and ```examples/vis_hue.m``` as examples of parsing **mpegflow** output. ```examples/vis_hue``` can also be used to produce hue flow visualizations like above.

# Building from source
**mpegflow** depends only on a recent FFmpeg, **vis** depends on FFmpeg, OpenCV and libpng. The tools are known to work with FFmpeg 2.7.2 and OpenCV 2.4.11. We strongly recommend running the following snippet to install the dependencies:

```bash
cd dependencies
bash install_ffmpeg_here_linux.sh  # to install ffmpeg
bash install_opencv_here_linux.sh  # to install opencv
cd ..                              # to move back from dependencies directory
```

Once the dependencies are visible to g++, run:
```bash
make     # to build mpegflow
make vis # to build vis
```

To build the tools on Windows:

1. Follow ```dependencies/install_dependencies_here_windows.txt```
2. Fix OPENCV_DIR, FFMPEG_DIR, VC_VERSION, OPENCV_ARCH in Makefile.nmake if needed
3. Run from Visual Studio Developer Command Prompt (VS2013 x64 Native Tools Command Prompt from VS2013 Community Edition worked for us):

 > nmake -f Makefile.nmake

