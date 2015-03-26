# Introduction #

DViz supports a network viewer for transmitting content over the network to be viewed on other computers. DViz only transmits the binary description of the items on the slide, not the actual rendered slide. It leaves the rendering of the slide up to the network viewer, allowing DViz to put some of the burden of rendering on the client.

The viewer can be run on any machine that has a network connection to the machine running dviz.exe. You can configure the port that dviz.exe listens to for each output using the Program Settings menu in dviz. Each output supports an virtually unlimited number of network viewers when using the "Network" option. The viewer just needs to be able to open a socket connection to the given port on the machine running dviz.exe.

# Images, Videos, and Other External Resources #

Currently, the Network Viewer load image and video resources directly from the file system. That means that for the viewer to load the same background image as you added on the machine running DViz, it needs to have the same image at the same path on the machine running the network viewer. In practice, this usually means using a shared network drive on Windows or an NFS share on Linux/Mac. It's possible in the future DViz may transmit the images and videos directly to the viewer over the same socket, but for now the viewer opens the images itself from the filesystem directly.

Note that this does not mean you **MUST** have a shared network drive. The network viewer will happily load images & videos from the local disk, as long as they are in the same folder and location as specified on the controlling PC. You could just use a thumbdrive to copy images & video resources over to the network viewer if you so choose.

## Shared Disk Caches ##

To speed up performance as much as possible, DViz stores the "rendered" version of items that take a "significant" amount of time to create, such as drop shadows, or the scaled version of large images used as backgrounds, large text boxes, etc.

DViz also caches these items in RAM (the amount of space allowed for the RAM cache is controlled under the Program Settings (or Setup Outputs in the viewer).

To take advantage of the performance increases offered by caching the rendered outputs of these items across all the network viewers used, you can point all the viewers and the DViz control program to the same cache folder, located on a shared network location. In the Program Settings dialog (or Setup Outputs in the Viewer), the "Cache" tab also has an option labeled "Disk Cache." This folder defaults to the Windows Temporary Files location (or /tmp on Linux.)

To make use of the same cache folder for all the viewers and the control PC, just set all the viewers and the DViz control PC's "Disk Cache Location" to the same shared folder. For example, all your PCs have access to a shared "P:\Misc\Temp" folder, set the DViz control PC and the Viewer PC's "Disk Cache Location" to "P:\Misc\Temp". Now DViz and the DViz Viewer will automatically store and load all the rendered items to/from that folder.

## Resource Path Translations ##

It's possible that the shared drive on the controller computer may not be mapped to the same drive letter on the computer running the viewer. To handle that, DViz Viewer provides "Resource Path Translations," setup from the File -> Setup Output menu option, under the "Resources" tab.

Say the "Control" PC has mounted the shared network storage as drive G:, and adds an image to a slide group from G:\Images\Foobar.jpg. However, a client running the Dviz-Viewer.exe has the same network share mounted as drive R:, and if it tried to load the original path of G:\Images..., it would fail. To fix this, you can use the Program Settings dialog to add a translation from "G:" to "R:". Note that this would also work for Linux or Mac clients in either direction. (E.g. the controller PC's drive G: is accessible on the Linux rendering client as /mnt/server2/groups/, so the translation in the linux client's program settings would be "G:" to "/mnt/server2/groups".)

## Fonts ##

You must be careful about using non-standard fonts in your designs.

For example, say you design a slideshow on a PC with Microsoft Office 2007 installed and use the 'Calbri' or 'Constantina' fonts (both come with Office 2007). However, if you use the DViz Network Viewer to display the show on a PC that does not have Office 2007 installed, you probably wont have "Calbri" or "Constantina" on that PC. Therefore, when the show you designed is displayed on that PC, the fonts which are used in place of, for example, Calbri, may have different widths than Calbri - causing the font to fall outside the textbox that you gave it when you designed it.

To fix that scenario, you have two options:

  1. Install Office 2007 on the viewer PC
  1. Or, copy the fonts from C:\Windows\Fonts on the "Designer" PC (with Office 2007 installed) to the C:\Windows\Fonts folder on the "Viewer" PC (without Office 2007) installed

Note that this "problem" is not unique to Office 2007 - it must be considered whenever you use a font that is not ubiquitous to every computer.

In the future, DViz may be able to automatically copy the font over for you or some other magic adjustment - but for now, you must use your own magic brain to assist in this are.


# Running the Viewer #

  1. Run dviz-viewer on your system. Right now, since there isn't an official release, this probably means locating the folder where you built the dviz-viewer executable and clicking on it.
  1. If this is your first time running the viewer on this machine, you'll want to tell setup the output.
    * The network viewer only supports a single output per viewer. (There's nothing stopping you from running multiple viewers on the same machine, each outputting to a different screen though.)
    * To setup the outputs, use the File->Setup Outputs menu option.
    * The information about setting up an individual output in [GuideToOutputs](GuideToOutputs.md) applies to the viewer here as well.
    * The output view will not appear until after the viewer has connected to DViz.
  1. To connect to DViz, select File->Connect To... and enter the host and port selected.
  1. Once you click Ok, the viewer will begin connecting to DViz. If it cannot connect right away (e.g. DViz isn't open), it will keep trying to reconnect every second or so, unless you turned off the "Automatically Reconnect" option in the "Connect To" window.
  1. To disconnect, choose File->Disconnect or just close the viewer control window.