# Introduction #

DViz supports a virtually unlimited number of outputs. DViz can output directly to screens attached to the local computer, or over the network to a remote [DViz Network Viewer](UsingDVizViewer.md).

# Local Outputs #

A "local" output is an output that is connected and rendered on the same computer on which the DViz control screen is located. A local output can either be a specific screen on a multi-screen system, or a custom rectangle on the screen.

## MJPEG Stream ##

For every local output, DViz can also output an MJPEG stream of frames for that output over the network as well for integration into video mixing programs such as VidBlaster, etc.

An MJPEG stream is also viewable in any standards-compliant web browser such as FireFox, Opera, or Google Chrome. To view the MJPEG stream from an output, first enable it in the settings dialog, then open your web browser and put in the host and chosen port like this: http://localhost:8081, where _localhost_ is the hostname or IP of the computer running DViz (or just use _localhost_ if you're opening the browser on the same computer as DViz), and _8081_ is the port you setup for the MJPEG server for that output.

# Network Outputs #

DViz supports sending the raw slide content over the network to a remote DViz Network Viewer for rendering on another computer on the network. For details on using the viewer, see [UsingDVizViewer](UsingDVizViewer.md).

## Performance Enhancement ##

One way to improve the performance of your DViz outputs is to run the Network Viewer on the same machine as DViz itself. You can configure your primary "Live" output as a Network output, then connect the DViz Network Viewer to that output (on the same machine.)

This improves performance by separating the "display" portion of DViz from the "control" portion of DViz, so that any minor slow downs or calculations in the control screen don't have to affect the live output. Now, this only holds true for minor performance issues - anything that slows down the computer to a great extent will likely have an adverse affect on the Network Viewer on that machine as well.

If the live output's performance absolutely **must not** be affected by the control screen's performance, it is recommended that you setup the live output on another computer via the Network Viewer.