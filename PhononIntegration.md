Scattered thoughts on using Phonon in DViz:
  * Need to test cross-fading between different files using the MediaObject() interface
  * If using Phonon as BG in a BackgroundContent, possibly keep a single VideoWidget always in the background of the scene...? (Experienced odd delays in cross fading, this may help...)
  * Need to proof-out/refine the "control widget" interface - seems buggy right now. Doesn't always show the control widget in live, often doesnt show it in preview.
