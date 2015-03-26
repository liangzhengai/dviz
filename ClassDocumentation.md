# Disclaimer #

This project was started using the [fotowall](http://code.google.com/p/fotowall/) codebase. My hat is off to the gentlemen behind fotowall - an excellent program which provided a huge amount of structure when I was trying to get this program off the ground. The src/items tree is the biggest part of their code that remains. The AbstractContent.cpp and CornerItem.cpp is largely their work - I've just adjusted and hacked at those two classes to adjust their behaviour to my liking. Again, the credit goes to the fotowall project for those items and much of the editing structure that this project started with. Thanks again!

# Main Window #

The core is **MainWindow** which holds a list of songs using the code in the **songdb/** folder to load and manage the songs. The list of slide groups is a QListView displayed using the model in **DocumentListModel**. That model interfaces with the **Document** class (under model/Document.cpp) to pull a list of **SlideGroups** (model/SlideGroup.cpp) and renders icons of the first **Slide** (model/Slide.cpp) using **SlideGroupFactory** (model/SlideGroupFactory.cpp).

# Slide Groups #

Each SlideGroup is composed of one or more Slides (model/Slide.cpp), which, in turn, are composed of one or more AbstractItem's (well, really the relevant subclass is the actual object, but all items on the slide inherit from AbstractItem as the grandparent, and **AbstractVisualItem** as the parent, or **AbstractNonVisualItem** as the parent for "hidden" items like sounds, scripts, etc.

# Item Properties / Attributes #

AbstractItem and all children use Qt Properties (Q\_PROPERTY() macro) to describe the various attributes relevant to the specific class. All items inheriting from AbstractItem have an "itemName()", which is primarily relevant for use in debugging output (say, "TextBox12345"). AbstractItem also provides an itemChanged() signal which is fired whenever a property value is set on it or an inherited class. (Either through the direct settor (setColor(), for example), or thru the Qt Property interface (setProperty(). The itemChanged() signal is propogated up thru the Slide and the SlideGroup for easy monitoring of changes. This signal is used by the various list models to update their icons, and by the viewers to keep their visuals in sync.

# Visual Delegates #

AbstractVisualtem is the model that **describes** the attributes of an item. It does no drawing itself - it is just a basic QObject. It does, however, know how to **create** a proper visual delegate which will render the model on a QGraphicsScene. The relevant method is:

AbstractContent **AbstractVisualItem::createDelegate(QGraphcisScene**,QGraphicsItem\*parent);

AbstractContent (in items/AbstractContent.cpp) syncs from the model item using AbstractContent::syncFromModelItem() and attaches a slot to the itemChanged() signal inorder to keep the QGraphicsItem up to date with the model. Each AbstractVisualItem must have a corresponding visual delegate in the /items/ folder inorder to be added to a graphics scene.

# Visual Items Implemented #

In the /model/ source folder, you'll find an increasing number of model items that implement the **AbstractVisualItem** interface. As of this writing (2009-10-15) there are the following items implemented:

  * **BackgroundItem** - Describes the background attributes of a slide. Only one per slide expected/allowed. (Not really enforced - probably should be.)
  * **TextBoxItem** - Describes a text box (with text wrapping.)
  * **BoxItem** - A basic rectangular box (with drop shadow.)
  * **VideoFileContent** - Looped video file using FFMPEG (no sound yet)
  * **ImageFileContent** - Still to be written here in a day or so.

The corresponding visual delegates are:

  * **BackgroundContent** - Renders the background as described. Currently supports video loops and solid colors. Video is loaded using **QVideoProvider** (in qvideo/QVideoProvider.cpp), which uses FFMPEG internally as the decoder provider.
  * **TextBoxContent** - Renders the text with QTextDocument and applies a drop shadow if needed, caching the results in the QPixmapCache for speed.
  * **BoxContent** - Renders a basic rectangle with support for variable width outlines and configurable drop shadow. The drop shadow itself is cached in the QPixmapCache for speed.
  * **VideoFileContent** - Renders a video loop using QVideoProvider/
  * **ImageFileContent** - Not yet implemented.

# Using the Visual Elements #

A custom QGraphicsScene, **MyGraphicsScene** (MyGraphicsScene.cpp) handles basic support and props to use the visual delegates. It also provides a single point to load a slide into the scene: setSlide(). The MyGraphicsScene class also manages cross-fading between slides.

**SlideGroupViewer** (SlideGroupViewer.cpp) manages the live output view and the preview in the main window.

A word about the outputs: MyGraphicsScene provides a context hint to the items within the scene. This allows, for example, video items to not play in preview or the editor, while dedicated all the sharpness and power needed to the live outputs.

# Outputs #

The "live outputs" are described in the **Output** class (model/Output.cpp). An output can be either a secondary (or third) video card (e.g. full screen), or a custom rectangle anywhere on the display. There is also support in the config dialogs and the Output model for output over the network, but that code has not yet been written to actually render the outputs over the network.

This project is envisioned to have multiple outputs, but as of this date (2009-10-15), I've only added support for a single live output. However, the model and the config dialogs are setup for more than one output. I just need to integrated the viewer structure.

The outputs are stored in QSettings using the **AppSettings** class (AppSettings.cpp), which also stores a few user preferences such as snap to grid, etc.