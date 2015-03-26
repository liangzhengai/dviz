# Introduction #

The Output Control Panel is located on the right side of the DViz window. There is one "Output Control" per Output, with tabs for each output along the top of the panel.

Each Output Control can be configured to function independently or in sync with another output (when that output changes slides, the one 'in sync' automatically changes slides as well.) The Output Control allows you to set the fade speed, as well as fade to Black or "Clear" (background only) for any slide.

Each Output Control can also have a number of filters applied to it to customize the display of the slide. An "Overlay Slide" can also be loaded from an external file and displayed on top of the current slide group.

The Output Control panel also allows you to type in "Quick Slides" - see below for details.

# Item-by-Item: General Controls #

![http://corp.productiveconcepts.com/images/DVizOutputControlPanelSnapshot_sm.png](http://corp.productiveconcepts.com/images/DVizOutputControlPanelSnapshot_sm.png)

### Basic Controls ###
  * Across the top is the row of tabs for each output configured. In the snapshot, you'll see its on the "Live" tab with a simple slide group loaded into the live output.
  * Right below the "Live" tab is two buttons labeled "Black" and "Clear."
    * The "Black" button fades the output to a black screen, using the Fade Speed to which the the "Fade Speed" slider is currently set.
    * The "Clear" button similarly fades the output screen to just the background of the current slide, fading out any foreground content using the "Fade Speed" slider speed.
  * The "Fade Speed" slider controls the speed at which the output executes cross fades. The left extreme of the slide represents virtually instantaneous cross fade (1ms/1 frame), while the right extreme give a nice, slow 2 second / 50 frame cross fade.
  * The "Advanced" button opens up the "Advanced" window, detailed below.

### Quick Slides ###

The "Quick Slide" box, right below the Black/Clear buttons is a unique feature that allows you to rapidly put text content on screen. Simply type the text you want to display in the Quick Slide box and press Enter (or click the "Show" button.)

Once you hit enter or click Show, the Output Control will clone the last slide in the current slide group, find the top-most text box, and replace that text with the text you typed, then display it live on the output.

This allows you to craft a slide in your slide group with the desired formatting (text/font/shadow settings, etc) and place it at the end of the slide group. Then, when you go live with that group, and you use the QuickSlide feature, it will pick up that slide at the end of the slide group which you've already formatted and use the formatting you gave it to display the text you type.

You may add the Quick Slide to the end of the slide group by clicking the "Add" button. This allows you to go back to previous QuickSlides without having to re-type the text - though sometimes re-typing is quicker than using your mouse to navigate to the end of the slide list.

### Slide List ###

The most obvious feature of the Output Control is the large slide list which displays snapshots of each slide in the slide group. To show a slide on the live output, just click on the icon, or use your arrow keys to highlight that slide. You may also use SPACE to "click through" the slides in sequence. At the bottom of the slide list also are "Prev" and "Next" buttons to move through the slide sequence.

### Timed Advance ###

You may set an "automatic advance time" on slides, after which dviz will automatically transition to the next slide without manual intervention required. If a slide has a timer set for it, it will appear below the "Slide X" text in the slide list.

When a slide goes live with a timer configured for the slide, the timer display below the slide list (bottom right) will activate and begin counting down in 1/10th second increments. When it falls below 3 seconds, it will go red. You may use the "Pause" button (labeled "Start" in the screenshot, but it changes to "Pause" when the timer activates) to pause the timer, or start it again if paused.

# Item-by-Item: Advanced Controls #

Clicking the "Advanced" button in the top-right of the Output Control displays the advanced options, as shown in the following snapshot:

![http://corp.productiveconcepts.com/images/DVizOutputControlPanelSnapshot-Advanced_sm.png](http://corp.productiveconcepts.com/images/DVizOutputControlPanelSnapshot-Advanced_sm.png)

### Sync / Live ###

The "Control Type" option has two values: "Live" or "Sync".
  * **Live**: When set to "Live", the Output Control displays the Slide List selector and allows you to set the slides on this output as described above under "Slide List")
  * **Sync**: When set to "Sync", the Output Control attaches itself to another output and changes slides in sync with the output listed in the "Sync With" box.

The "Sync" setting is used specifically with the "Foldback" output to display the same content on the foldback display as on the live display.

Take care not to create an infinite sync loop. It is possible to setup three outputs in sync with each other in a loop - don't do it. You will crash DViz when you go live with the next slide.

### Overlays ###

You can choose a slide to overlay on top of any slide displayed on the output.

To add an overlay:
  * Select a file by clicking "Browse" and choosing a previously designed DViz document.
    * DViz uses the first slide from the first slide group in the document as the overlay slide.
    * You will see a snapshot of the overlay slide appear below the filename box. If it's not the slide you expected, open the overlay document in DViz and re-arrange the slide or slide group sequence.
  * Click "Enable Overlay" to show the overlay on the live output.

Overlays will appear **above** any content on the slide displayed on the output. However, if the overlay has a background, the overlay **background** will override the current slide's background. To prevent this, open the overlay document, and edit the overlay slide's background, and choose "No Background" instead of a solid color, etc.

### Filters ###

DViz supports several built-in filters and an automatic text resizer facility.

The text resizer is used on the foldback output to ensure the text is as big as possible. It can be turned off if desired, but it will be turned back on for the next slide group that goes live. If enabled, the text resizer automatically resizes font size of the top-most text box be as large as possible without dropping off the sides of the screen.

The filters list displays the filters available, with a checkbox beside any filters currently active. When a song is live in the output control, an extra filter will be visible titled "Song Text Filter" (or something similar.) This is a special filter only compatible with songs. The filter names should be self-explanatory.