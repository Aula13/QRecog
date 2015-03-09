# CorrespondenceGrouping

Project based on the tutorial found at [PointClouds.org](http://pointclouds.org/documentation/tutorials/correspondence_grouping.php#correspondence-grouping)


## Usage

 1. Download the pcd data from [Github](https://raw.github.com/PointCloudLibrary/data/master/tutorials/correspondence_grouping) and extract files in a folder of your convenience.

 2. Download the CorrespondenceGrouping repository from [Github](https://github.com/danieleciriello/CorrespondenceGrouping)
 
 3. Uncompress the archive
 
 4. Move to the uncompressed directory, and create a build directory in there:

		$ cd path/to/CorrespondenceGrouping-<branch> && mkdir build && cd build
 
 
 5. Run the Cmake build system using the default options:
 		
 		$ cmake ..
   
    Or change them:
		
		$ cmake -DCMAKE_BUILD_TYPE=Release ..

 6. Compile everything:

 		$ make
 
 7. After you have created the executable, you can then launch it following this example:

 		$ ./CorresponseGrouping milk.pcd milk_cartoon_all_small_clorox.pcd

 	Or alternatively, if you prefer specifying the radii in units of cloud resolution:

 		$ ./correspondence_grouping milk.pcd milk_cartoon_all_small_clorox.pcd milk.pcd milk_cartoon_all_small_clorox.pcd -r --model_ss 7.5 --scene_ss 20 --rf_rad 10 --descr_rad 15 --cg_size 10
	
	Remember to replace milk.pcd and milk_cartoon_all_small_clorox.pcd with model and scene filenames, in this exact order. If you want you can add other command line options as described at the beginning of [this tutorial](http://pointclouds.org/documentation/tutorials/correspondence_grouping.php#correspondence-grouping).

After a few seconds, you will see an output similar to:

	Model total points: 12575; Selected Keypoints: 686
	Scene total points: 307200; Selected Keypoints: 3747
	Correspondences found: 1777
	Model instances found: 1

	    Instance 1:
	        Correspondences belonging to this instance: 21

	            |  0.968 -0.127  0.218 |
	        R = |  0.124  0.992  0.031 |
	            | -0.220 -0.003  0.975 |

	        t = < -0.158, 0.215, -0.042 >

The output window should look like this (depending on the command line options used):

![alt tag](http://s28.postimg.org/c4nt9cjfh/Schermata_2014_04_17_alle_14_43_32.png)

## Walkthrough

It’s important to say that the only command line parameters required when executing this tutorial are the filenames of the model and the scene, in this exact order. All other parameters are set to a default value that will make the tutorial work correctly with the supplied dataset, although with different models and scene some parameter values might need to be adjusted. You can play around with them to see how they influence the final result.

You can choose between two correspondence clustering algorithms with the command line switch --algorithm (Hough|GC)

 - Hough (default)

    This is a clustering algorithm based on a 3D Hough voting scheme described in:

    [F. Tombari and L. Di Stefano: “Object recognition in 3D scenes with occlusions and clutter by Hough voting”, 4th Pacific-Rim Symposium on Image and Video Technology, 2010.](http://vision.deis.unibo.it/fede/papers/psivt10.pdf)

 - GC

    This is a geometric consistency clustering algorithm enforcing simple geometric constraints between pairs of correspondences. It builds on the proposal presented in:

    [H. Chen and B. Bhanu: “3D free-form object recognition in range images using local surface patches”, Pattern Recognition Letters, vol. 28, no. 10, pp. 1252-1262, 2007.](http://webdocs.cs.ualberta.ca/~lihang/Campus/c414/presentation/added/3D%20Free-Form%20Object%20Recognition%20in%20Range%20Images%20Using%20Local%20Surface%20Patches.pdf)


Some other interesting switches are *-k*, *-c* and *-r*:

- *-k* shows the keypoints used to compute the correspondences as a blue overlay into the PCL visualizer.
- *-c* draws a line connecting each pair of model-scene correspondences that survived the clustering process.
- *-r* estimates the spatial resolution for the model point cloud and afterwards considers the radii used as parameters as if they were given in units of cloud resolution; thus achieving some sort of resolution invariance that might be useful when using this tutorial with the same command line and different point clouds.

## Notes

 - The CMakeLists.txt has been edited in order to let make correctly link and build on Mac OS X 10.9

 - If you are using different point clouds and you don’t know how to set the various parameters for this tutorial you can use the -r flag and try setting the LRF and descriptor radii to 5, 10, 15 or 20 times the actual cloud resolution. After that you probably will have to tweak the values by hand to achieve the best results.