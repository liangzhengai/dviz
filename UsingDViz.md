# Introduction #

DViz is designed to be easy to use and quick to learn. You should be able to open it up and get something on screen with no trouble at all. However, there's more than one way to get the job done, and DViz has built in many advanced options and unique ways of meeting the challenges presented. To that end, explore this usage guide for tips, tricks, explanations, and general ramblings about DViz.

# Quick Start #

  1. Download and Install DViz
    * You can download the Beta from http://code.google.com/p/dviz/downloads/list as a zip file - just extract the archive and run **dviz.exe**
    * You may also download the source to DViz from [the Google Code Source repository](http://code.google.com/p/dviz/source/checkout). You'll need [Qt](http://qt.nokia.com/downloads) to compile DViz. For more information on building DViz, see [CompilingDVizFromSource](CompilingDVizFromSource.md).
  1. Open DViz
  1. Setup your "Live" output
    * Outputs are setup from the File menu under "Program Settings." Select "Configure Outputs" from the first tab.
    * DViz supports virtually unlimited number of outputs, and comes setup for three outputs to start with.
    * Your "Live" output is generally considered your "Primary" or main output, but thats just convention - no technical limitation.
    * The only "special" output is the "Foldback" output. This output automatically has a text-only filter turned on, and when viewing songs, it has a special "Song Text Filter" that gets enabled. Both of those filters can be disabled if you choose, but they are automatically turned on by default.
    * For more information on Outputs, see [GuideToOutputs](GuideToOutputs.md).
  1. Quick Fulfillment:
    * To show a song on the live output, select the "Songs" tab from the "Items" dock on the left
    * Double-click on a song to add it to the schedule list
    * The song will automatically display the first passage on the live output if no other content is live on the output.
    * If something else was already live on the output, just double-click on the song in the schedule to send it to the live output.
    * To change slides in the song, just click the passage of text in the Slide List. Song passages are separated by dotted lines, while other slide group's slides are displayed in a grid with a larger snapshot of the slide.
    * For more on changing slides and using the Output Control, see [GuideToOutputControl](GuideToOutputControl.md).

# Basic Concepts #

DViz's documents are a collection of "Slide Groups," which in turn are collections of "Slides." Every slide has a background and a number of visual items on them, such as videos, images, text boxes, etc. See [GuideToSlideEditing](GuideToSlideEditing.md) for information on content creation.

DViz includes a song database, and an advanced media browser for viewing and selecting videos and images as backgrounds for slides or songs. See [GuideToSongs](GuideToSongs.md) for information on editing and using songs.