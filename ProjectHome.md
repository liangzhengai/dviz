# Introduction #
DViz is designed to be used for the production of visual scenes for use in presentational systems.

Alright, that's a nice, ambiguous definition. What's that mean? Basically, DViz is designed to manage groups of slides - it handles designing (layout) of the slides, and the output of the slides to one (or more) screens. DViz supports special types of slide groups, such as songs, videos, live web pages, or playlists of slide groups. DViz also supports video backgrounds, live HTTP MJPEG video streams, networked outputs, remote control via built-in webserver, automatic generation of lower-thirds from songs/other slide groups for use with video mixers such as [livepro](http://code.google.com/p/livepro/), MIDI triggers for changing slides, and more.

Even with all that complexity, it's simple and easy to use - I've had young teens (12 or 13yr olds) running the songs within 2 minutes of sitting down - now, this is during the youth group in the evenings, but they handled it well. (They love the ability to change the video backgrounds on the fly during the songs.)


# Latest News #

## SVN [r1073](https://code.google.com/p/dviz/source/detail?r=1073) ##
**2012-06-27**

The latest Windows 7 build of DViz available at: http://code.google.com/p/dviz/downloads/detail?name=dviz-r1073.zip

**Note:** There was a problem with recent previous Windows builds of DViz - I forgot to include a folder with the image format plugins in the archive, so they likely did not load JPEG images correctly, if at all. This omission has been rectified in this latest zip file - I apologize for any trouble caused by this error.

## Tablet Support ##

Support for iPads, Android tablets, etc was added since [r1038](https://code.google.com/p/dviz/source/detail?r=1038). This release provides a built-in webserver (defaulting to port 8082) which serves up a web interface designed for use on an iPad, Android tablet, or even large-screened mobile phones.

This tablet interface is designed for controlling the songs portion of DViz, with support for editing and displaying songs, complete with live slide highlighting (and control!)

With tablet support, I've also added support for username/password authentication to the various web apps integrated into DViz. Setup for users/passwords is available in the "Program Settings" menu option under the "File" menu.

Below is a screenshot of the tablet interface in action.

![![](http://www.mybryanlife.com/userfiles/dviz/DViz-TabletDemo1-small.png)](http://www.mybryanlife.com/userfiles/dviz/DViz-TabletDemo1.png)

**Note:** With proper firewall and VPN setups, you can also serve up the tablet interface via your church website. We're experimenting with doing just that to allow our music team to select and edit songs prior to Sunday morning, online and from their home. Then when the team arrives Sunday morning, their tablets on stage already are synchronized to DViz and loaded with the song and arrangements setup online.




## SVN [r1038](https://code.google.com/p/dviz/source/detail?r=1038) ##
**2012-06-14**

### Download ###
The latest Windows 7 build of DViz available at http://code.google.com/p/dviz/downloads/detail?name=dviz-r1038.zip

### 175 Bibles Available ###
The biggest change since the last update on this page ([r1019](https://code.google.com/p/dviz/source/detail?r=1019)) is the ability to use Bibles stored on your computer instead of relying solely on downloading verse text from the internet. This means that there are now over 175 Bible texts compatible with DViz that you can download and use - the full list of Bibles available is here: http://www.mybryanlife.com/dviz-bibles/ - DViz can download Bibles from that list in-program (you don't have to download them yourself and figure out where to put the files) - just select the button to the right of the Bible version list on the Bible tab and the Bible Download window will appear. Click the checkbox beside the versions you want to download and they will be immediately downloaded and available for your use. Here's the download dialog, showing a search for 'english' Bibles:

![![](http://www.mybryanlife.com/userfiles/dviz/DViz-BibleDialog-small.png)](http://www.mybryanlife.com/userfiles/dviz/DViz-BibleDialog.png)

You'll find a large number of English language Bible versions in that list, and an even larger number of non-English Bibles. All the Bibles in the list correctly display non-English (non-Latin) alphabets. This was driven largely by Issue # 114, a request for Tamil compatibility. Screenshot of the Tamil translation of John 3:16 below:

![![](http://www.mybryanlife.com/userfiles/dviz/DViz-Tamil1-small.png)](http://www.mybryanlife.com/userfiles/dviz/DViz-Tamil1.png)

**Note:** Some of the versions I'm hosting _may_ be copyrighted and not legal for distribution. However, I'm unsure of which (if any) of the versions are, in fact, not to be distributed. I will gladly remove any copyrighted works without hesitation if requested by the copyright holder.

If someone would like to host a mirror of the Bibles available for download, such an offer would be most welcome. Please email me at josiahbryan@gmail.com to offer to host a Bible mirror. The 175 Bibles weigh in at a total of 1.3 GB (approx) on disk.

### Copy and Paste ###

The slide editor in DViz has always been able to copy and paste it's own items on the current slide. However, as of [r1024](https://code.google.com/p/dviz/source/detail?r=1024), DViz has switched from an internal clipboard to using the computer's global clipboard.

This means that not only can you copy and paste slide items between slides or even between slide editor windows, but you can also do things such as copy an image from a webpage (right click and "Copy Image") and paste it directly into DViz without having to save the image on disk and then go into DViz, add an image item, and browse to the saved location. You can also copy DViz items, such as rich text or images, and paste them into other programs as desired.

### Misc Bug Fixes ###

A number of minor fixes have been added since [r1019](https://code.google.com/p/dviz/source/detail?r=1019). Of note are:

  * Bible slides now named properly (only "v X" unless appending to a group, then it's "Book X:Y")
  * New songs now properly use the template set in the song browser
  * Song templates _not_ stored in database _unless_ edited by user (e.g. add song to document, it picks up the default template from the song browser, edit and save song, only the song text is committed to the database UNLESS the template is also edited.)
  * "Reset template" button added to song editor window to delete any user-set template on the Song and reset that song template to the default template in the Song Browser
  * User event actions only play now when **actually** going live. For example, press Black then send a Video live - previously, user event actions would play right away even with Black checked. Now, user event actions only play when the Black button is un-clicked.
  * Minor fixes to HTML handling for certain song lyric providers for online downloading of Songs

### Issues ###

As always, issue reports are very much welcome and encouraged - visit http://code.google.com/p/dviz/issues/list to report an issue or bug with DViz, or to request a change or improvement. Or, just email me directly at josiahbryan@gmail.com.


## SVN [r1019](https://code.google.com/p/dviz/source/detail?r=1019) - User Actions, Advanced Text Importing, Song Arrangements/Templates in Database ##
**2012-05-10**

No screenshot to show for this update, I'll just review the major updates:

### Advanced Text Importing ###
Under the "Tools" menu is the little-used "Text Import Tool." I've extensively updated this tool to be able to preprocess text using a perl script, tweak the generated slides with javascript, and put the text in user-designed templates.

Currently, I make use of this tool in two areas: Importing sermon outlines each week and importing Bible trivia questions. The perl and javascript files I use to import the sermon outlines each week can be found in trunk/src/sermon2slides as [preproc.pl](http://code.google.com/p/dviz/source/browse/trunk/src/sermon2slides/preproc.pl) and [sermons.js](http://code.google.com/p/dviz/source/browse/trunk/src/sermon2slides/sermons.js), with a sample sermon outline (copy-pasted from the email Pastor sends out) is in [sample.txt](http://code.google.com/p/dviz/source/browse/trunk/src/sermon2slides/sample.txt).

The preproc.pl script is used to process the pasted text directly without any user intervention required. In fact, the Text Import Tool dialog has a second tab titled "Paste Text" where you can past text directly into the dialog without having to save to a file first.

The sermons.js script selects a random background for the slide group (from sermon2slides/backgrounds - not included in subversion, you can make your own folder though.) The script also selects the named slide from the template to use based on the content of the current slide, sets the name of the slide in the output, and even automatically uses the BibleBrowser module to download verses and add them to the main document.

### User Actions ###
User Actions are available for every slide group type, and are automatically triggered when the group goes live, goes "not-live", or a slide goes live/not-live. Actions can be either a URL to hit or a program to execute.

You can configure a set of default actions for each group type under File->Program Settings, tab "Default Actions" - just select the group type from the top and configure the actions. Multiple URLs or programs can be hit/run by separating the actions with a comma (","). To configure actions for a specific group in the schedule, just right-click on it and select "Slide Group Properties."

I currently use "User Actions" to automatically dim/raise lights in our church sanctuary in combination with [dmxsliderwin](http://code.google.com/p/dmxsliderwin/) which exposes presets as individual URLs that can be triggered via HTTP. For example, I've configured DViz at church in the default actions for the "Songs" slide group type to raise the lights over the worship band when the song group goes-live, then turn them off when the song ends (goes "not-live"). For video groups, I've set it up to dim the audience lights and stage lights when the video starts, then raise them when the video ends. You, too, can use "User Actions" to help automate parts of your service - if something can be triggered by a simple URL or running a program, then it can be triggered automatically by DViz.

### Song Arrangements and Templates in Database ###
The song module has been updated to store song arrangements in the song database itself, rather than just in the .dviz file. Templates are also stored now in the database itself. This means that arrangements/templates can persist across schedules and can be reused multiple time.


## SVN [r988](https://code.google.com/p/dviz/source/detail?r=988) - Raw Frame Transmission, Alternate Slide Groups, Bible and Song Template Updates, Song Arrangements ##
**2012-03-09**

![http://www.jdbryanphotography.com/dropbox/dviz-snapshot1.png](http://www.jdbryanphotography.com/dropbox/dviz-snapshot1.png)

Major updates in the last 14 revs - several major new features/updates added "behind the scenes." The most user-visible change probably is the new 'Song Arrangements' feature, visible in the screenshot above.

### Song Arrangements ###
Song Arrangements work by parsing the text for the "block headers" (E.g. "Intro","Verse 1", "Chorus", etc) and allowing you to work with the text under those headers as concrete units, even if its spread across multiple slides. This consideration makes it possible to rearrange the order of the song (the "arrangement") by simple re-ordering a list of block titles (visible in the screenshot above at the top and via the drag-and-droppable list on the right.) The original text is never changed, only the slides and text on the screen is re-ordered.

### Raw Frame Transmission ###
Under the hood, the change I'm perhaps most excited about is the "Raw Frame Transmission" feature added recently. It may not sound like much, but its the best way yet I've come up with to integrate DViz graphics with live video. The way it works, you use the "Program Settings" dialog to setup individual outputs and enable the MJPEG server any output you'd like. To enable "Raw frame" mode, set the FPS to "0". This special mode will change the server on the specified port to a server compatible with livepro.

As of [r105](http://code.google.com/p/livepro/source/detail?r=105), [livepro](http://code.google.com/p/livepro) can receive feeds from DViz via the raw frame server built into DViz using the "HTTP Image" object in the livepro mixerui editor. Simple enter a URL using the protocal "raw://", for example, "raw://192.168.0.10:8099" (assuming you used port 8099), and livepro will receive frames from DViz.

DViz will only send raw frames **when the slide changes** - so this mode is not suitable for videos or animated graphics. (For videos played by DViz that you wish to mix in via livepro, I suggest relying on an S-Video input from the DViz computer and capture it as another Camera input in livepro.) However, because DViz only sends frames when the slide changes, it puts very little strain on the DViz computer's CPU.

Livepro handles this raw connection different than a normal video feed - each frame it receives, it will cross-fade to from the previous frame via OpenGL on the GPU using the current crossfade speed set in livepro's mixerui. (This means that DViz is not in control of the crossfade speed, and that DViz does not have to render 30x intermediate partial-opacity frames - all the intermediate rendering is done by livepro on the GPU on that player computer.)

Livepro can use this raw connection via the "HTTP Image" object as either an overlay (e.g. for lowerthirds) or as a full screen image in a "Group Player" module in mixerui - both function as expected.

When combined with this next feature added in to DViz, this allows for some powerful visual flexibility.

### Alternate Slide Groups ###
DViz has been updated to allow for "alternate groups" to be assigned to specific outputs.

For example, say you have a slide group in your document titled "Sermon," which contains the primary graphics for Sunday's message, such as the title slide, main point slides, etc. Without Alternate Groups, when you send the Sermon group to the outputs, any active output (Say, "Live", "Foldback", "Secondary", etc) gets the exact same images (unless you turn on a filter on that output, like Text Only, but that's not relevant here.)

With Alternate Slide Groups - in our example, from within the Slide Editor Window, you can create an _Alternate Group_ specifically for, say, the _Secondary_ output. This "Alternate Group" can contain completely different graphics (for example, lowerthird graphics for livepro, or sermon notes for the foldback output for the Pastor), and multiple "alternate slides" from the Alternate Group can be linked to a single "primary" slide from the main slide group.

Now, with Alternate Groups, when our example "Sermon" is sent live, the Secondary output automatically displays the alternate graphics stored inside the Sermon group and synchronizes the display of the proper slide with the slide on the Live output.

The control screen has been updated so that when you click on a slide that has more than one alternate slide linked to it, the alternate slide cycles through the list of alternate slides available for the selected slide with each successive click. E.g. if the title slide for the Sermon has three alternate slides, the first click (or first time the title slide is shown), the first alternate slide is displayed. If the user clicks on the title slide again, the next alternate slide is displayed, and so on and so forth.

When combined with "Raw Frame" transmission on the Secondary (or any output), and transparent background on the alternate group (use the "No Background" option), this provides a suitable and powerful method for creating custom lowerthirds or other graphics for display over live video that are perfectly and effortlessly synchronized to the live graphics projected on the primary output.

Alternate Groups and Raw Frames are further combined to result in yet another powerful usage in the next feature.

### Bible and Song Template Updates ###
The entire slide group creation routine inside the Bible module has been reworked and rewritten to make use of the new Alternate Groups feature. Along the way, the Bible module template support has become much more flexible.

The Bible template module now supports the following "tags" in the template to allow the user to specify which text box gets which elements from the program:
  * #text - Use for the first slide's title text
  * #verses - The primary text box to display the verse content
  * #ref - The verse reference at the top of the slide, hidden if not used
  * #ref-bottom - The reference at the bottom of the slide, hidden if notused
  * #reading - Responsive reading label, hidden if not used

These changes in the Bible module template routines are backward-compatible with existing Bible templates in DViz - it will silently upgrade any tempaltes it finds in-place to bring them up to par.

Additionally, the Song module has been updated to support Alternate Groups designed into templates - e.g. if a template has an alternate group, the Song module will create slides based on both the primary template and the alternate group for the appropriate outputs.

Combined with appropriately-designed templates for lowerthirds for the Bible module and Song module, along with the Alternate Groups and Raw Frames feature, DViz now is capable of generating automatic lowerthirds for Songs and Bible text on-the-fly with no user intervention required, and automatically transmitting the lowerthirds for overlay onto live video feeds to livepro.


## SVN [r974](https://code.google.com/p/dviz/source/detail?r=974) - Features and Bug Fixes, LivePro Fork ##
**2012-02-29**

Crikey, almost a year since since updating this page. Sorry! The codebase has been mostly stable over the past year, especially with regards to DViz itself.

I've split off the video mixer code (from src/glvidtex) into it's own project on Google Code: http://code.google.com/p/livepro/ - up to [r90](https://code.google.com/p/dviz/source/detail?r=90) or so on that project - lots of clean up and organization of the codebase, new apps, performance enhancements, etc.

Features and bug fixes as of this rev:
  * Added 'titlesafe' margin setting to DViz, and updated the Song and Bible module to respect that margin (configurable in the Program Settings dialog, defaults to 7.5%) ([r974](https://code.google.com/p/dviz/source/detail?r=974))
  * Added an 'ignore aspect ratio' option to outputs - this allows one to design the document in, say, 16x9, but render to a 4x3 output, which would "squeeze" the 16x9 content to a 4x3 rect. This is useful for outputting a 4x3 feed to a device (say, projector) which stretches the 4x3 to 16x9. ([r973](https://code.google.com/p/dviz/source/detail?r=973))
  * Added template support to the Song browser module - e.g. a "default template" so you can use the default template to set a default background or style of the text. (The text is still auto-resized to fit the template.) ([r971](https://code.google.com/p/dviz/source/detail?r=971))
  * Added drag/drop from the Song browser to the main document list. ([r970](https://code.google.com/p/dviz/source/detail?r=970))
  * Fixed a bug in the 'auto sizing' text routine that affected the Bible module (and, with the new code changes, the song module as well) which caused the vertical centering of text on the screen to be off (typically, it centered too high.) Now it centers correctly. ([r973](https://code.google.com/p/dviz/source/detail?r=973))
  * Internally added a 'delay' before pre-rendering the textboxes in the background. This allows the UI to appear more responsive when adding long songs or Bible verses. (See notes on [r973](https://code.google.com/p/dviz/source/detail?r=973).)


## SVN [r927](https://code.google.com/p/dviz/source/detail?r=927) - Audio Delay Buffer ##
**2011-03-10**

Modifications made to the /src/audioinput\_example today added an audio delay buffer for live playback of the incoming audio stream with a configurable delay. A Windows binary has been released in the Downloads section called 'audiobuffer' as audiobuffer-[r927](https://code.google.com/p/dviz/source/detail?r=927).zip:

http://code.google.com/p/dviz/downloads/detail?name=audodelay-r927.zip

This standalone executable is designed to allow you to buffer an incoming audio feed from, say, a mixing board by an adjustable amount (I find 200ms works good for my needs) in order to sync with a video stream being recorded live.a

Enjoy!

## SVN [r916](https://code.google.com/p/dviz/source/detail?r=916) - LiveMix Director Updates ##
**2011-03-01**

![![](http://www.jdbryanphotography.com/images/LiveMixDirector4-small.jpg)](http://www.jdbryanphotography.com/images/LiveMixDirector4-large.png)

LiveMix Director has been extensively updated since [r900](https://code.google.com/p/dviz/source/detail?r=900) - from memory, the major changes/additions:

UI:
  * Camera Mixer added - mix 2 cameras as PiP, side by side, or 3D (seen above)
  * Property Editor - for dynamic updating of user-controllable drawables (such as the large text object in the overlay window in screenshot, above)
  * DViz integration via HTTP Viewer Server - Added an 'HTTP Image Drawable' to make use of the HTTP viewing server added in [r566](https://code.google.com/p/dviz/source/detail?r=566)/[r565](https://code.google.com/p/dviz/source/detail?r=565). Works equally well with polling any image via HTTP. Special code is added to also poll the DViz data stream for changes if flagged as a DViz server in the editor.
  * Switcher Window added with support for keyboard-based switching (e.g. press 1 to activate Camera 1, etc.)
  * Textured background added in Overlay window and Editor window

Under the Hood:
  * Cameras now are cross-faded as separate scenes/groups rather than changing the connection on a single GLVideoDrawable. This will allow brightness/contrast/hue/saturation to be dynamically adjusted via GLVideoDrawable properties as opposed to relying on the V4L subsystem and stored for later retrieval.
  * The API changes that enabled the camera crossfading change above also made possible the new camera mixer widget.

Related News:
  * LiveMix Director and Player ran their first live event with the new UI and codebase. The feed was recorded via S-Video on a secondary machine via Windows Movie Maker and uploaded to Vimeo: http://vimeo.com/20448619 - note that the camera quality was less than optimal due to the connection being ran from the stage to the soundbooth via RCA->1/4th inch->XLR on stage and XLR->RCA in the soundbooth, which caused noticeable color desaturation.
  * Dual S-Video and VGA output was achieved during the live event via an ATI graphics card cloning the VGA output to S-Video. The VGA was used to feed two 3200 lumen projectors at the front-of-house position, while the S-Video, as mentioned before, was feed to the recording machine. Audio arrived from the soundboard about 200ms out of sync with the final recording. Audio was resynced in Windows Movie Maker prior to upload to Vimeo.

Next up: work on recorded video and fleshing out GLVideoFileDrawable integration into the UI and internal work.

Email me: josiahbryan@gmail.com with questions, comments, or offers of large sums of cash. Cheers!

## SVN [r900](https://code.google.com/p/dviz/source/detail?r=900) - LiveMix Redesign ##
**2011-02-23**

![![](http://www.jdbryanphotography.com/images/LiveMixDirector-small.jpg)](http://www.jdbryanphotography.com/images/LiveMixDirector-large.png)

LiveMix has been completely redesigned - twice. The latest incarnation separates the live ("player") component (the binary responsible for all live graphics) from the controller ("director") component (the binary responsible for the user interface that controls the player.) So, we have two binaries now: gldirector and glplayer. In the above screenshot (click for larger view) you see the Director with five modules visible - a Monitor view (showing whats playing on the glplayer live via TCP stream), two camera inputs (streamed via TCP from the glplayer), an Overlay module (place graphics/text on top of any other content) and a Player module (display arbitrary 'slides' of content.)

I'll add a Wiki page on building and running LiveMix Director and Player tomorrow. Feel free to email me at josiahbryan@gmail.com with questions or comments.

Cheers!

## SVN [r679](https://code.google.com/p/dviz/source/detail?r=679) - LiveMix + CentOS 5.3 + Qt Mobility 1.1.0 Beta II ##
**2010-10-17**

I've finally managed to get Qt Mobility to build and run on CentOS 5.3 - my OS-of-choice for my multimedia systems as of late. The key was commenting out the use of v4l2 in the gstreamer plugin - that was easy. Then I had to install gstreamer-plugins-bad and gstreamer-plugins-ugly to get it to play MPEG files.

Thankfully, LiveMix ran against Qt Mob. 1.1.0b2 without any code changes - just had to remove the .build/LiveVideo(...).o files and rebuild with qmake CONFIG+=mobility and voila! Full motion video straight from gstreamer into a OpenGL textured quad - sweet action.

Now to flesh out the editor UI, add a "player" UI/binary, layout editor, web front end, and add usable widgets...lots to do, but its fun! Of course, any contributions and assistance welcome as well!

## SVN [r674](https://code.google.com/p/dviz/source/detail?r=674) - LiveMix Runs First Live Event ##
**2010-09-29**

![![](http://www.jdbryanphotography.com/images/LiveMix-snapshot20100929-small.png)](http://www.jdbryanphotography.com/images/LiveMix-snapshot20100929.png)

LiveMix ran it's first live service tonight with code rev [r674](https://code.google.com/p/dviz/source/detail?r=674) for our church - the annual Business Meeting. Fun stuff.

## SVN [r664](https://code.google.com/p/dviz/source/detail?r=664) - LiveMix Gets Video/Audio Playback Thru QtMobility ##
**2010-09-20**

![![](http://www.jdbryanphotography.com/images/LiveMixSnapshot-100920-small.png)](http://www.jdbryanphotography.com/images/LiveMixSnapshot-100920.png)

Video/Audio playback has been integrated into LiveMix using QMediaPlayer from QtMobility. Instead of using one of the built-in video renderers in QtMobility, we register a "fake" QAbstractVideoSurface to funnel video frames from QtMobity's video decoders into the OpenGL video texture renderer in glvidtex/GLVideoDrawable. Once we've got the video from QtMobility into our set of drawables, we can integrate it into any set of layers that we want!

As you can see in the screenshot above, I've got the video playing in it's own layer (layer list, left-side of the UI, see the item labeled '92\_Churchfamily'? That's the video playing using QtMediaPlayer as the backend.) Then I render an upper-third overlay, and a lower-third overlay with a text crawler. Since we're handling the rendering of the video instead of Qt's classes, we can do things like smooth transitions from one video to the next, or fade in/fade outs, etc.

Cheers!

## SVN [r658](https://code.google.com/p/dviz/source/detail?r=658) - LiveMix Gets a New Look and New Graphics Engine ##
**2010-09-10**

![![](http://www.jdbryanphotography.com/images/LiveMixLayersEditor-small.png)](http://www.jdbryanphotography.com/images/LiveMixLayersEditor.png)

Since the last post on LiveMix, I have **extensively** redesigned the internals and the UI of LiveMix. I've crafted a set of OpenGL-based video texture classes for use in a canvas-style setup. LiveMix has been changed to have the concept of "layers", where each layer represents a rectangular portion on the screen, and layers can be stacked, have transparency, and contain whatever you want - such as live video feeds, video files, text, static images (PNGs with alpha channels), etc.

The screenshot above shows the layering functionality in action - the live video feed is the bottom layer, with a static PNG as the lower third background, and three text layers over top of the lower third. You can see in the layers list (upper left), that there are a number of other layers in the scene, but they are not currently visible (no checkbox.)

LiveMix supports keyframes, with automatic animation between keyframes. The list in lower-left is the keyframe list. LiveMix takes a "snapshot" of the properties of all the layers (or just the selected layers) in the scene and stores them in a key frame. When you activate a key frame, livemix automatically does a smooth interpolation between the current value for each property and the value stored in the keyframe. Key frames can have a time length for the animation (the number directly to the left of the "Show" button in each row), as well as a "play time", which can be used to play key frames in a sequence automatically.

The screen shot above is just the "layer editor", which allows you to edit a group of layers, collectively called a "scene." I still need to write the "control window" (launches layer editor to edit scenes), and the "player window" which plays layers and receives commands from the "control window" via local socket, UDP, or TCP.

Lots more to come - keep your eye on this page for more updates.

## SVN [r572](https://code.google.com/p/dviz/source/detail?r=572) - LiveMix Gets Outputs ##
**2010-07-28**

![![](http://corp.productiveconcepts.com/dropbox/LiveMixSnapshot-small.jpg)](http://corp.productiveconcepts.com/dropbox/LiveMixSnapshot.jpg)

LiveMix, the internal video switching program I'm developing inside DViz, has achieved 'alpha' level functionality! Woohoo! As you can see in the above screen shots, Livemix is an OpenGL based-video mixer for live video, designed for outputing to external screens, much the same way as DViz. For more on LiveMix, see the [LiveMix](LiveMix.md) wikipage.

(Yes, in the screenshot, the viewers in LiveMix are running at <= 15fps - they are intentionally rate-limited to reduce the performance burden placed on the GUI/CPU by the control window. The full-screen output window, however, runs with no upper bound on FPS.)

The source for LiveMix is in the [/trunk/source/livemix](http://code.google.com/p/dviz/source/browse/trunk/src/livemix) directory - download it and check it out! Let me know what you think - email me at [josiahbryan@gmail.com](mailto:josiahbryan@gmail.com)

## SVN [r566](https://code.google.com/p/dviz/source/detail?r=566) - HTTP Viewing Server CSS Added ##
**2010-07-26**

Minor update, really. But I figured it newsworthy because I can add a screenshot to the front page to show off newly styled template. Anyway, here for your viewing pleasure, is a screenshot of the view in Firefox:

![http://corp.productiveconcepts.com/dropbox/DvizHttpViewer.jpg](http://corp.productiveconcepts.com/dropbox/DvizHttpViewer.jpg)

Cheers.

## SVN [r565](https://code.google.com/p/dviz/source/detail?r=565) - HTTP Viewing Server, Live Video Feeds ##
**2010-07-25**

A user-requested feature has been added: An HTTP viewing server. Basically, now DViz has a built-in web server showing whatever is on the 'Live' system output via an HTTP page served by default over port 8081. Port # is configurable via File->Program Settings. This feature is still being improved upon - the styling of the web page, for example, will be improved in the future.

With this feature, you can bring along a laptop and a copy of DViz to a meeting or gathering where people have WiFi and laptops or smartphones. You can use the HTTP viewing server to serve up a copy of your presentation via WiFi and their web browsers, rather than having to lug around a projector. Just open up File->Program Settings when you get your laptop online on the WiFi and give everyone the URL that appears in that window. They can punch it into their web browsers and voila! They can see the current slide on their screen. It updates automatically every 1/2 second - they don't have to press anything or click anything to update.

Also in this revision is a working and tested Live Video Feed feature (Insert menu -> Add Camera Viewer). I've worked very hard to reduce live latency to as small as possible - right now, it appears to be less than 1/10th of a second latency. Just be sure not to be previewing any videos in DViz or that will reduce the FPS and increase latency (time it takes for the image to travel from your camera to the screen.) This feature is under active development, with a lot of work going into reducing the latency and speeding up the rendering of live video feeds. Let me know if you have any problems with it. Thanks!

No updated windows build yet - if you want a windows build of [r565](https://code.google.com/p/dviz/source/detail?r=565), send me an email (josiahbryan@gmail.com) and I'll get something online ASAP. Cheers!

## SVN [r540](https://code.google.com/p/dviz/source/detail?r=540) - DViz 1.5 Release Candidate Available for Download ##
**2010-06-15**

I've uploaded a build of DViz for Windows to the Downloads area. You can go ahead and download it from the following URL:

http://dviz.googlecode.com/files/dviz-r540.zip

This is a Release Candidate - which means no new features will be added to this before the 1.5 release. Only bug fixes will be applied. Assuming that all things go well (no show-stopper bugs found), I'll plan to release DViz 1.5 by July 1st.

Cheers!

## SVN [r540](https://code.google.com/p/dviz/source/detail?r=540) - Media Browser Bookmarks and Feedback Wanted ##
**2010-06-14**

Four months since I've lasted updated this page - wow. Sorry, everyone. We've been using DViz every Sunday at PHC since our last update (well, really since October 26th - [r260](https://code.google.com/p/dviz/source/detail?r=260).) Since 2/25 (last update), I've done a lot of "tweaking" under the hood - minor updates, really. Most visible is in the "Media" tab - added a bookmark feature (titled "Saved" in the UI) so you can bookmark folders and jump to them without having to navigate the file system.

**Feedback Needed:** Very little feedback received from the Beta - either nobody is using it or interested, or noone wants to tell me how terrible it is. With 79 downloads of the beta, and who knows how many source checkouts, I'd like to think at least a few of you have some opinions! Let me know what you think: [josiahbryan@gmail.com](mailto:josiahbryan@gmail.com). Cheers!

## SVN [r500](https://code.google.com/p/dviz/source/detail?r=500) - Beta Release ##
**2010-02-25**

I've [a beta version http://dviz.googlecode.com/files/dviz-beta-r500.zip](released.md) (Zip file containing dviz.exe, dviz-viewer.exe, and libraries needed to run DViz), compiled from the SVN [r500](https://code.google.com/p/dviz/source/detail?r=500) source snapshot. Download it and check it out! [Report back on any issues you find](http://code.google.com/p/dviz/issues/list), let me know what can be done to improve functionality or make it better.

## SVN [r497](https://code.google.com/p/dviz/source/detail?r=497) - Video & Audio, Web Pages, and More ##
**2010-02-23**

It's been a while since I've updated this news feed, but a lot has been happening under the hood. A full 100 revisions since the last update and three months. It's been a bit slower in development due to the holidays and some family "issues" that have come up. But DViz has still been under heavy development - both in bug fixes and feature development.

Most significantly since the last update on this page:
**Web Pages** Video (with Audio)
**Bible Enhancements & Templates** Logo Feature

Web Page support has been included (brand new in [r497](https://code.google.com/p/dviz/source/detail?r=497)) via the WebKit rendering engine included in Qt. All navigation and control of the web page is done in the DViz control screen - no interaction with the "output" monitor required! However, the web page feature currently does not (yet) work over the network via dviz-viewer - only with local outputs.

![![](http://corp.productiveconcepts.com/images/DVizSnapshot1_sm.png)](http://corp.productiveconcepts.com/images/DVizSnapshot1.png)

(Click for larger view)

Video (with Audio) support has finally been included via integration with the Phonon multimedia engine included in Qt 4.6. DViz must be built in release mode for Phonon integration to work. Video controls do not work over the network.

![![](http://corp.productiveconcepts.com/images/DVizSnapshot2_sm.png)](http://corp.productiveconcepts.com/images/DVizSnapshot2.png)

(Click for larger view)

A variety of Bible module enhancements have been made in the past 100 releases - off the top of my head, there is template support included, additional reference location options, and verse "navigational" buttons (move to next chapter, next verse, etc.) Also a "send straight to live output, dont add to document" button is included. Screen shots of the additions can be seen in the first screenshot, above (under Web Page support).

Also, a dedicated Logo button has been included to allow you to pre-program any number of "logo" slides and cross-fade to those pre-designed slides on demand with a dedicated "Logo" button beside the Black and Clear buttons.

Please do download and build the latest version and let me know your thoughts. If you would like a pre-compiled Windows beta version, email me at josiahbryan@gmail.com and I'll see what I can do.

If you find any issues (crashes, bugs, etc) or if you have ideas for new features, please please **please** fill out a new Issue using the [Issues Tab](http://code.google.com/p/dviz/issues/list) (also at the top of this page). Thanks!

Cheers!


## SVN [r397](https://code.google.com/p/dviz/source/detail?r=397) - Bible Support ##
**2009-11-17**

Probably the most significant change in the past 5 days and 46 revisions is the addition of a "Bible Browser" tab to the main window of DViz:

![![](http://corp.productiveconcepts.com/images/DVizBibleSnapshot_sm.png)](http://corp.productiveconcepts.com/images/DVizBibleSnapshot.png)

(Click for large view)

Supports a large number of book name abbreviation (see [src/bible/book-abbrv-list.txt](http://code.google.com/p/dviz/source/browse/trunk/src/bible/book-abbrv-list.txt) for full list). Currently downloads bible text from BibleGateway.com, though the API is generic enough that other bible sources can be added in the future if an appropriate connector/parser is written.

**Group Player**: Another significant addition (specifically in [r383](https://code.google.com/p/dviz/source/detail?r=383)) was added: a "Group Player" slide group - basically a meta slide group that allows you to sequence a set of slide groups, either internal to the current document or from other documents, and play that set of slide groups in a loop. (Assuming all the slides have auto-change times specified.) A group player slide group is visible in the screen shot above with a set of several Bible-generated slides contained within.

To add a group player slide group, use the Tools menu and choose "Add Group Player." The "Edit Slide Group" window for the group player group is a custom editor which allows you to add/import slide groups into the group player.

To play the group player, just send it to the live output like any other slide group and it should work as expected.

Also, DViz [r391](https://code.google.com/p/dviz/source/detail?r=391) and following have been tested and built on the latest Qt 4.6 RC 1, available from http://qt.nokia.com/developer/qt-4.6-preview. Significant performance boost visible on Linux, not so much on windows - at least on the Windows laptop that we test with. Let us know your experience with the new Qt 4.6 RC 1 and note any issues above [in the Issues tab](http://code.google.com/p/dviz/issues/list).

That's all for now, folks. If you have any ideas or bug reports, please be sure to report them and/or vote on them [in the "Issues" tab](http://code.google.com/p/dviz/issues/list), at the top of this page!

Cheers!


## SVN [r351](https://code.google.com/p/dviz/source/detail?r=351) - HTTP Remote Control Completed ##
**2009-11-12**

The HTTP remote control functionality is now "completed" (e.g. in a production usable state.) It supports toggling Black/Clear, as well as changing the current slide group, and changing the slides within the group. The web page interface is fairly basic - much more that could/probably will be added to it - but it is very usable right now. Tested on a BlackBerry Curve (using the built-in browser in HotSpot mode), FireFox 3.5, and IE 6.

![![](http://corp.productiveconcepts.com/images/bb_sm.jpg)](http://corp.productiveconcepts.com/images/bb.jpg)

## SVN [r348](https://code.google.com/p/dviz/source/detail?r=348) - HTTP Remote Control ##
**2009-11-11**

Today I scratched an itch - I added an HTTP Remote Control server to DViz. It's NOT complete by any means - just a rough draft. Screenshot below. Current listens on port 8080 and serves up the current document along with icons. Designed to allow the user to change slide group & change the slides via HTTP. Small pages, designed to be usable over wifi from BlackBerry/iPhone/etc cellphones or PDAs. More news to come on this later.

![![](http://corp.productiveconcepts.com/images/ControlScreenShot-Small.jpg)](http://corp.productiveconcepts.com/images/ControlScreenShot.jpg)

## SVN [r339](https://code.google.com/p/dviz/source/detail?r=339) - PowerPoint Connector Rewritten, Network Viewer Faster ##
**2009-11-10**

Though PowerPoint technically was integrated with DViz, a showstopper cropped up for those who needed powerpoint: pptview.exe wouldn't render fades or animations when automated via OLE. This was a problem both when automated via Qt's ActiveQt code and also when using VBScript/wscript shell on windows - so it wasn't just Qt. Therefore, the automation method was rewritten to use PowerPoint itself (not the viewer), via the MS Script Control, via ActiveQt. Fun, eh? Anyway, it works "better" than the previous method - still lots of "screen flashes" when loading a group or going live, but only on the control screen, not on live. That is due to PowerPoint opening and then being resized quickly - haven't found a way around that - yet. PowerPoint does, however, support the 'Black' button and Clear (well, Clear = White Screen in PPT). Working on being able to 'Pause' timed presentations, but not there yet.

In other news, the transmission of large slide groups over the wire to the network viewer has been sped up significantly. Internally, we've converted from sending slides over the wire in XML and JSON to using pure byte arrays, thanks to the flexibility and ease-of-use of Qt's QVariant, QVariantMap, and QByteArray, it was a very easy conversion. The network viewer also now receives out-of-group slides such as the QuickSlides.

For more information on what's new and improved, see the [Updates List](http://code.google.com/p/dviz/updates/list) (linked from the top of the page as well) and read the notes from [r325](https://code.google.com/p/dviz/source/detail?r=325) through [r339](https://code.google.com/p/dviz/source/detail?r=339). For beta users: Download URL has been updated with latest Win32 builds as of rev 339.

Cheers!

## SVN [r325](https://code.google.com/p/dviz/source/detail?r=325) - PowerPoint Integration ##
**2009-11-07**

24 hours after installing the PowerPoint 2007 viewer, we've got it integrated into DViz. That means you can now add PowerPoint files straight into the DViz schedule as a special slide group. For the most part, integration is seamless from a control point of view - when you "go live" with a PowerPoint file, all the slides appear in the view control just like any other slide group in DViz.

Other than that minor bombshell, the Media Browser (and other icon-generating list models) have been greatly improved in terms of performance. The icon generation code has been moved to a queue formant - makes loading a directory with lots of pictures/videos a breeze. The files show up quite fast, and the icons load in one at a time without interrupting usability.

Tons of other minor improvements in the past 25 revisions - compile and see for yourself.

Cheers!

## SVN [r300](https://code.google.com/p/dviz/source/detail?r=300) - Network Viewer! ##
**2009-11-02**


Of worth noting: The Network Viewer is working! Woohoo! The viewer itself is in [/trunk/src/viewer](http://code.google.com/p/dviz/source/browse/#svn/trunk/src/viewer) and the .pro file contained therein builds the **dviz-viewer** executable.

To use:
  * Compile and run dviz (/trunk/src/dviz.pro), setup an output as a Network type, choose "Accept incomming", and select a port.
  * Compile and run dviz-viewer (/trunk/src/viewer.pro), click File->Setup Outputs to setup the output (only the first output in the list is used in the viewer), then click File->Connect and put in the port chosen in the first step.
  * Now go back to the main DViz window and send a slidegroup to all outputs. Voila! Network viewer magic.

The network viewer can be ran on any PC in the world (theoretically :-). It just needs a plain old socket connection back to the PC running the main DViz program.

## SVN [r295](https://code.google.com/p/dviz/source/detail?r=295) - Full Service DViz ##
**2009-11-02**

Ran the entire Morning and Evening worship services with DViz! Lots of work done on the multiple output functionality, including filters on outputs and a custom filter for song lyrics on the rear wall supporting foldback-only text such as chords, etc.

This week saw several additions to DViz:
  * The Media Browser now is the dialog used to find videos and images in the slide editor
  * An MJPEG server was integrated into each output, configurable from File->Program Settings
  * Custom filters added for outputs
  * Song lyric filter added for foldback-only texts
  * Large image handling improved
  * Text import tool added

A note on the large image handling: The large image handling has been improved to the point to where DViz can successfully handle over 200 12-megapixel images in a single slide group and iterate through them complete with smooth cross fades and timed advance. (Note that 200 is just the max I've tested so far, should be fine handling as much as you want.) What it does is now DViz scaled the image from 12 MP down to the size of the physical display right when it loads the image, then it keeps the scaled-down copy in RAM and caches it on disk for future use. This way, DViz isn't keeping a ton of data around, wasting memory on pixels that will just be scaled down and out when shown on screen anyway. This allows it to fit handle pictures much more efficiently, resulting in better performance and stability.

Welcome to anyone coming in from EasyWorship forums, by the way. No releases yet - but you can [send an email to dviz-users@googlegroups.com](mailto:dviz-users@googlegroups.com) to get a private beta version. Runs on Windows and Linux, not tested on Mac OSX yet. (Testers welcome for Mac as well, but you'll have to build it from the source yourself.)

Cheers!


## SVN [r260](https://code.google.com/p/dviz/source/detail?r=260) - First Live Run of DViz! ##
**2009-10-26**

Completed two live runs of DViz yesterday: During the morning church service, it ran the sermon portion of the service, handling over 40 slides and live edits without any problems at all. (Couldn't use the song portion due to a segflt bug, which was fixed during the afternoon.)

Then in the evening, we gave the song portion of DViz a workout: We ran both the HIS KROSS (kids) and PHYSH (teens) worship services. Everything ran quite smooth - changed video backgrounds on the fly, song cross faded smoothly, everything went great!

Through both live runs yesterday, a lot of usage data was collected and a lot of areas that need to be improved are noted in [/trunk/docs/Features.txt](http://code.google.com/p/dviz/source/browse/trunk/docs/Features.txt). No major show-stopping bugs were found (e.g. it's usable to run another service in its current form), however, many areas need touched up, fixed, improved, and generally polished before its ready for its first release.

Features of note since the last announcement:
  * Multiple output support with text-only filters and synchronized slide changing
  * Aggressive caching added to various parts of DViz in effort to make performance as smooth as possible
  * Property configs for items in the slide editor now are part of the editor instead of as a dialog
  * Media browser added with preview icons for images and videos
  * Song Database functionality completed.
  * Many critical bugs and minor features implemented

For the latest snapshot of where we're at with the project, see [/trunk/docs/Features.txt](http://code.google.com/p/dviz/source/browse/trunk/docs/Features.txt).

Cheers!

## SVN [r209](https://code.google.com/p/dviz/source/detail?r=209) - Pretty Shadows and More ##
**2009-10-17**

Not that I'm counting revisions or anything, but average 6.5 revisions a day seems overkill. None the less, its fun to commit and see that number climb, knowing work is getting done. For the latest snapshot of where we're at with the project, see [/trunk/docs/Features.txt](http://code.google.com/p/dviz/source/browse/trunk/docs/Features.txt).

Of mention in the past 26 revisions and four days of work is:
  * Blurred shadows with customizable blur radius, color, offset on text, boxes, and images
  * Image items with full support for SVG and "standard" images (jpeg, png, etc)
  * "Timed" slide changing (e.g. change to next slide after X seconds)
  * Increase/decrease text from toolbar in slide editor
  * Mid-point handles for resizing items
  * Keyboard movement of items in the editor
  * And a multitude of critical bugs and minor features implemented
  * "F5" key in editor sends current slide to live output

Many more updates completed, features added, and bugs swatted since the last headline. Check out the source and play around with it. This should be the most stable revision yet. If you do find any segfaults or program crashes, please do let us know by using the "Issues" tab above or emailing me using my profile on the right.

Cheers!


## SVN [r183](https://code.google.com/p/dviz/source/detail?r=183) - Version 0.8.2 ##
**2009-10-13**

In the past three days, we've added song templates, undo/redo support in the slide editor, made the UI a bit more pretty with the addition of icons from the Bluecurve theme (24x24/stock folder) from CentOS, and lots of features added and bugs swatted.

See [/trunk/docs/Features.txt](http://code.google.com/p/dviz/source/browse/trunk/docs/Features.txt) for an up-to-date snapshot of where we are at bug swatting and feature implementation. Notice that we've completed almost EVERY major feature slated for release 1.0 - only a "few" improvements and bugs to swat before we lock it down, add unit tests, document code and functionality, and prep for a 0.9 beta release. Assuming the beta release goes well (feedback is okay, no major bugs, no major missing features found), release 1.0 should be posted by end of next week (hopefully!)

Check out the code, download and compile, and let us know what you think. Cheers!

## SVN [r164](https://code.google.com/p/dviz/source/detail?r=164) - Version 0.7.0 ##
**2009-10-10**

Since [r100](https://code.google.com/p/dviz/source/detail?r=100) only 8 days ago, we've come a long way. Check out [/trunk/docs/Features.txt](http://code.google.com/p/dviz/source/browse/trunk/docs/Features.txt) (or, for pretty colors, see the [colored diff of r100 to today](http://code.google.com/p/dviz/source/diff?spec=svn99&old=99&r=163&format=side&path=%2Ftrunk%2Fdocs%2FFeatures.txt).

Highlights include Song database integration (SQLite backend), song editor window, song slide group (dynamic translation from paragraphs of lyrics into slides). Code for songs is in the [/trunk/src/songdb/ folder](http://code.google.com/p/dviz/source/browse/#svn/trunk/src/songdb).

Also included is very developmental code for audio input (backported from Qt 4.6) for use in generating visual effects (e.g. animations, beat analyzers, etc.) Also ported over is the visualizer code from amarok 2.2. See [audioinput\_example](http://code.google.com/p/dviz/source/browse/#svn/trunk/src/audioinput_example) for sample code. Not integrated at all into main branch yet - but the code is there for when we get to it. Along the same lines, I've imported RtMidi into the 3rdparty folder for future use in integrating with MIDI-controllable lighting consoles.

Ver 0.7.0, svn [r164](https://code.google.com/p/dviz/source/detail?r=164) features a lot of cleanup and general stabilization. It should run equally well on both windows and linux using Qt 4.5 or newer.

If you're keeping score, you'll notice we targeted rel 1.0 for today. I'm not quite finished with the slide editor portion of the code so I'm not ready to finalize rel 1.0. Additionally, I've got to write a lot of documentation and test cases. However, for almost everything, we've hit the target feature set for release 1.0. Just missing snap to grid, layout assist, and image items, along with minor UI cleanup and polish. That may happen as soon as Sunday, 10/12 or Monday 10/13. We'll see. Check back again soon!


## SVN [r100](https://code.google.com/p/dviz/source/detail?r=100) - Almost There! ##
**2009-10-02**

We're closing on on version  1.0 - the **Tasty Breakfast** Release. The most up-to-date roadmap of where we're at is in the [/trunk/docs/Features.txt](http://code.google.com/p/dviz/source/browse/trunk/docs/Features.txt) file - updated almost every day as to what's done, whats coming up, what bugs we've found (and killed!)

It's starting to really take shape and look like a real application. So far we've got drag and drop reordering support on the slide group list, as well as in the slide editor. We've also got a preliminary "live view" output and multiple-monitor support. You can setup your output monitor under File -> Setup Outputs. Preliminary code is in for supporting virtually unlimited number of outputs - although Ver 1.0 will probably only support one or two outputs, but Ver 1.5 has "many outputs" on the map.

Feel free to checkout the source and build it! I don't guarantee that the svn head will always be usable, or that it won't randomly delete or screw up your data. It's still a work in progress, and every revision brings new features and changes. The code base is still very much in a state of flux, but the core class model and relationships are pretty much nailed down.

And, finally, I welcome any contributions or partners in programming on this project. Anyone interested in joining up and contributing to the project? Send me an email - [josiahbryan@gmail.com](mailto:josiahbryan@gmail.com). Cheers!

## SVN [r58](https://code.google.com/p/dviz/source/detail?r=58) - Multi-Slide Support, Video Items ##
**2009-09-21**

A minor milestone of sorts: Included in svn [r58](https://code.google.com/p/dviz/source/detail?r=58) is support for multiple slides. Also included is a Document model (Document has many SlideGroups which have many Slides which have many AbstractItems). Also included (since the last homepage update) is support for video loops! SVN [r58](https://code.google.com/p/dviz/source/detail?r=58) builds on both windows and linux.

Cheers!

## SVN [r25](https://code.google.com/p/dviz/source/detail?r=25) - Custom Text Wrapping Code Released ##
**2009-09-15**

After working all weekend on the stubborn code, it looks like the text layout routines for HTML contained in a QTextDocument is somewhat complete. See [line 609 in items/TextBoxContent.cpp (svn r25)](http://code.google.com/p/dviz/source/browse/trunk/src/items/TextBoxContent.cpp?spec=svn25&r=25#609).

Any improvements or feedback welcome. Cheers!

## SVN [r13](https://code.google.com/p/dviz/source/detail?r=13) Builds on Windows! ##
**2009-09-09**

First windows build! I just tested SVN rev 13 and it builds straight out of the box on Windows XP using QtCreator from QT SDK 4.5. Yay!

I did notice a slight bug - TextContent doesn't seem to be saving the html text back to TextItem. Need to see if that's windows-only or the same problem on linux.

Other than that, it builds on windows without any problem whatsoever! Whahoo!

# Mailing Lists #

## User support ##
(E.g. Using the program, not hacking on the insides)
  * Email: [dviz-users@googlegroups.com](mailto:dviz-users@googlegroups.com)
  * Group: http://groups.google.com/group/dviz-users

## Development ##
(E.g. development-related questions and SVN commit messages)
  * Email: [dviz-devel@googlegroups.com](mailto:dviz-devel@googlegroups.com)
  * Group: http://groups.google.com/group/dviz-devel