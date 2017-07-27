# PIX2NVS: A Neuromorphic Vision Sensors Emulator 

We provide our implementation of **PIX2NVS**, a tool for converting pixel frames to brightness spike events as generated by neuromorphic vision sensors (e.g. DAVIS-240). 

A full description of the operation of this tool can be found in our paper: 
> @inproceedings{auth,  arxiv link}

If you use the code in this repository, please cite the paper above. This tool is provided under the [GNU General Public Use v3.0 license].

## Building Source
All dependencies are located in the source folder. To build from source, change your working directory to this repository's home folder and run:

```bash
g++ -o pix2nvs src/*.cpp  # to build from source  
./pix2nvs # to run using default parameters
```

## Running Options

Option | Description
--- | ---
-r or --reference | set to (1, 2, or 3) to specify one of the reference frame update methods.
-m or --maxevents | will specify the maximum number of events generated between two frames
-b or --blocksize | will set the block size for local inhibition
-a or --adaptive  | will set the co-efficient shift for adaptive thresholding, set to (0) to disable

The reference frame update option can be set to any of the following:

r | Reference Frame Update Method
--- | ---
1 | copy last frame from source
2 | update reference frame using only generated events, with history decay
3 | update reference frame using only generated events, without history decay 


## Example Usage

To extract events from videos located in the input folder:

```bash  
./pix2nvs -r 3 -a 0 -b 4
```
All outputs will be located in the folder "Events". The output from PIX2VNS using these parameters is visualized in the following figure:

Pixel Image | Emulated NVS Events  
--- | ---
<img width="321" alt="screen shot 2017-07-27 at 01 22 17" src="https://user-images.githubusercontent.com/18630131/28649110-5b57efd8-726a-11e7-9296-6eac104a2ebc.png"> | <img width="318" alt="screen shot 2017-07-27 at 01 20 04" src="https://user-images.githubusercontent.com/18630131/28649129-6996180e-726a-11e7-8631-0d8b4cf68653.png">

  
## Contact

For any questions or bug reports, please contact Yin Bi at <yin.bi.16@ucl.ac.uk> or Alhabib Abbas at <alhabib.abbas.13@ucl.ac.uk>.
