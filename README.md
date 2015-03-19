QRecog
======

THIS IS A WORKING PROGRESS, STAY TUNED

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
- Libusbx (only for OSX)
- Sip

# Requirements Installation

Below are the instructions on how to install all the requirements on your OS X 10.10 and Ubuntu

## Mac OS X (Tested on OS X 10.10)

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


- Check the presence of the pcl/visualization directory for VTK.
- Check the presence of pcl/io/openni2 and pcl/io/openni_camera directories for OpenNI and OpenNI2.
- Install Qt + Qt Creator: http://stanford.edu/~rawatson/qt/mac_install_gifs/ .
- Set the qt4 located in usr/local/Cellar (the one installed by brew) as default Qt kit.
- If qt raise this error: Parse error at “BOOST_JOIN” apply this quick workaround (found here: http://stackoverflow.com/questions/15455178/qt4-cgal-parse-error-at-boost-join): edit the problematic boost header files, and add to the top:

            #ifndef Q_MOC_RUN

add to the bottom:

            #endif

- Don't Bother if it don't works.

Lo scopo di questo progetto è quello di riconoscere oggetti nello spazio tridimensionale grazie alle librerie PCL e OpenNI.

Questa repo contiene il progetto di sistemi meccatronici, all'interno della cartella project si può trovare il codice sorgente.
