QRecog
======


![Acquisition View](https://raw.githubusercontent.com/danieleciriello/QRecog/master/documentation/acquisition.png)

![Clustering View](https://raw.githubusercontent.com/danieleciriello/QRecog/master/documentation/clustering.png)

![Correspondence Grouping View](https://raw.githubusercontent.com/danieleciriello/QRecog/master/documentation/recognition.png)


# Some Theory

## Point clouds

First, a little explanation. A point cloud as taken from a depth sensor consists of a series of points in 3D space, as simple as that. A "pcl::PointCloud<PointT>" object stores the points inside a "std::vector<PointT>" structure. The cloud object exposes some functions that let you get information about them, like the point count. As you can see, the class is templated so you can instantiate it for many types of points. For example, "PointXYZ", which stores three floats for the X, Y and Z coordinates, and "PointXYZRGB", which also stores color (texture) information for each point, the kind we would get with Kinect or Xtion RGB-D cameras. A list of point types and a basic description of the cloud object are available on PCL's website.

## 3D Object Recognition

### Overview

The basis of 3D object recognition is to find a set of correspondences between two different clouds, one of them containing the object we are looking for. In order to do this, we need a way to compare points in an unambiguous manner. Until now, we have worked with points that store the XYZ coordinates, the RGB color... but none of those properties are unique enough. In two sequential scans, two points could share the same coordinates despite belonging to different surfaces, and using the color information takes us back to 2D recognition, will all the lightning related problems.

### Features
 
A feature of a point is some characteristic that can help us to tell it apart from a different point. Of course, you could say that the XYZ coordinates would be characteristic enough, but when interpolating the data of two different, yet corresponding, clouds, they become useless. We need something better, that will have similar values when computed for the same spot of a surface in both sets.

Normals are an example of feature, because they encode information about the vicinity of the point. That is, the neighboring points are taken into account when computing it, giving us an idea of how the surrounding surface is. But this is not enough. For a feature to be optimal, it must meet the following criteria:

- **It must be robust to transformations:** rigid transformations (the ones that do not change the distance between points) like translations and rotations must not affect the feature. Even if we play with the cloud a bit beforehand, there should be no difference.
- **It must be robust to noise:** measurement errors that cause noise should not change the feature estimation much.
- **It must be resolution invariant:** if sampled with different density (like after performing downsampling), the result must be identical or similar.

This is where descriptors come in. 

### Descriptors

They are more complex (and precise) signatures of a point, that encode a lot of information about the surrounding geometry. The purpose is to unequivocally identify a point across multiple point clouds, no matter the noise, resolution or transformations. Also, some of them capture additional data about the object they belong to, like the viewpoint (that lets us retrieve the pose).

![Finding correspondences between point features of two clouds](http://robotica.unileon.es/mediawiki/images/a/ab/Correspondence.jpg)

There are many 3D descriptors implemented into PCL. Each one has its own method for computing unique values for a point. Some use the difference between the angles of the normals of the point and its neighbors, for example. Others use the distances between the points. Because of this, some are inherently better or worse for certain purposes. A given descriptor may be scale invariant, and another one may be better with occlusions and partial views of objects. Which one you choose depends on what you want to do.

check [robotica.unileon.es](http://robotica.unileon.es/mediawiki/index.php/PCL/OpenNI_tutorial_4:_3D_object_recognition_(descriptors)) for more informations about Descriptors


# Requirements
Project Requirements:
- Qt 4.8
- Qt Creator
- PCL 1.7.2

PCL dependencies:
- OpenNI
- OpenNI2
- VTK 5
- Boost
- Oost 
- Eigen 
- Flann 
- Cminpack 
- Chull 
- Libusb
- Sip

## Requirements Installation

Below are the instructions on how to install all the requirements on your OS X 10.10 and Ubuntu

### Mac OS X (Tested on OS X 10.10)

- Install brew: http://brew.sh/
- Update brew:

        $ brew update

- Tap versions formulas (in order to install VTK5):

        $ brew tap homebrew/versions

- Install VTK5:

        $ brew install vtk5

- Create symbolic links for VTK5:

        $ brew link vtk5 --force

- Tap science formulas (in order to install PCL):

        $ brew tap homebrew/science

- Edit PCL formula to run make with vtk5 instead of vtk (6):

        $ brew edit pcl

    - Replace:

            depends_on "vtk" => [:recommended,"with-qt"]

    - With:

            depends_on "vtk5" => [:recommended,"with-qt"]

    - Replace:

            depends_on "vtk" => :recommended

    - With:

            depends_on "vtk5" => :recommended

    - Save and close the editor's window.

- Install PCL with OpenNI and OpenNI2:

        $ brew install pcl --with-openni --with-openni2
        
- Install LibUSB:

        $ brew install libusb
        
        


- Check the presence of the pcl/visualization directory for VTK.
- Check the presence of pcl/io/openni2 and pcl/io/openni_camera directories for OpenNI and OpenNI2.
- Install Qt + Qt Creator: http://stanford.edu/~rawatson/qt/mac_install_gifs/ .
- Set the qt4 located in usr/local/Cellar (the one installed by brew) as default Qt kit.
- If qt raise this error: Parse error at “BOOST_JOIN” apply this quick workaround (found here: http://stackoverflow.com/questions/15455178/qt4-cgal-parse-error-at-boost-join): edit the problematic boost header files:

    - Add to the top:

            #ifndef Q_MOC_RUN

    - Add to the bottom:

            #endif

- Don't Bother if it don't works.

Lo scopo di questo progetto è quello di riconoscere oggetti nello spazio tridimensionale grazie alle librerie PCL e OpenNI.

Questa repo contiene il progetto di sistemi meccatronici, all'interno della cartella project si può trovare il codice sorgente.

# Sources
http://www.pointclouds.org/documentation/tutorials/correspondence_grouping.php

http://robotica.unileon.es/mediawiki/index.php/PCL/OpenNI_tutorial_2:_Cloud_processing_(basic)#Feature_estimation

http://robotica.unileon.es/mediawiki/index.php/PCL/OpenNI_tutorial_4:_3D_object_recognition_(descriptors)

http://www.vision.deis.unibo.it/fede/papers/icip11.pdf
