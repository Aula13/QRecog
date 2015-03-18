QRecog
======

THIS IS A WORKING PROGRESS, STAY TUNED

# Install

## Mac OS X (Tested on OS X 10.10)

- install brew: http://brew.sh/
- $ brew update
- $ brew tap homebrew/versions
- $ brew install vtk5
- $ brew link vtk5 --force
- $ brew tap homebrew/science
- $ brew edit pcl
    replace:
      depends_on "vtk" => [:recommended,"with-qt"]
    with:
      depends_on "vtk5" => [:recommended,"with-qt"]
    replace:
      depends_on "vtk" => :recommended
    with:
      depends_on "vtk5" => :recommended
    save and close the editor's window
- $ brew install pcl --with-openni --with-openni2

- check the presence of the pcl/visualization directory for vtk
- check the presence of pcl/io/openni2 and pcl/io/openni_camera directories for openni and openni2
- install qt+qt creator: http://stanford.edu/~rawatson/qt/mac_install_gifs/
- set the qt4 located in usr/local/Cellar (the one installed by brew) as default qt kit
- if qt raise this error: Parse error at “BOOST_JOIN”
    apply this quick workaround (found here: http://stackoverflow.com/questions/15455178/qt4-cgal-parse-error-at-boost-join):
       edit the problematic boost header files, and
        add to the top:
            #ifndef Q_MOC_RUN
        add to the bottom:
            #endif
- Don't Bother if it don't works

Lo scopo di questo progetto è quello di riconoscere oggetti nello spazio tridimensionale grazie alle librerie PCL e OpenNI.

Questa repo contiene il progetto di sistemi meccatronici, all'interno della cartella project si può trovare il codice sorgente.
