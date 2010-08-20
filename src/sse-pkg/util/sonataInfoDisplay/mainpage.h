/**
 * @mainpage openSonATA sonataInfoDisplay Documentation
 *
 * <center>
 * sonataInfoDisplay<BR>
 * Release 2.0<BR>
 * Release Date Aug 13, 2010<BR>
 * Visit <a href="http://setiQuest.org" target="_setiquest">setiQuest.org</a>
 * for participation details.
 * </center>
 *
 * <br>
 * <p>The sonataInfoDisplay program uses a curses display window to present the status of the various system components such as the channelizers, dx's, archivers, etc.
 * </p>
 * <p>It reads in the file sse-system-status.txt as it is being generated by the SonATA software and parses the contents into a curses screen that you can page up and down. This comes in very handy when there are potentially hundreds of channelizers and Dxs running at one time. The good thing about a curses program is that it is very efficient to view remotely over the internet.
 * </p>
 * <p>There is a command line option -p that makes this program read from already created files.
 * </p>
 * <p>The code is C++. The main entry point to the program is in main.cpp. That would be a good place to start investigating the code.
 * </p>
 *
 * <br>
 * <center><b>How you can use this software</b></center>
 * <p>
 * This application is meant to act as a replacement for the System Status text window when SonATA is running. Future versions will hopefully also replace the System Log and SSE-Seeker windows as well. The result will be a much cleaner and easier to use SonATA interface. 
 * <p>When running SonATA (either by initiating the sonata-gen or sonata-vger scripts) this program can act as a replacement for the System Status window. You need to supply the program with the paths to 3 files:
 * <ul>
 *  <li><i>sse-system-status.txt</i> - Contains the status of the various system components such as channelizers, dx's, etc.</li>
 *  <li><i>error-2010-08-04.txt</i> - Contains the errors and warnings. Obviosly the date changes to the current date in the filename. Note that this file is not actually parsed in this version of sonataInfoDisplay. See below for information on how you can help.</li>
 *  <li><i>systemlog-2010-08-04.txt</i> - Contains signal detection reports. Also, this file is not actually parsed in this version of sonataInfoDisplay. See below for information on how you can help.</li>
 * </ul>
 * <p>To start sonataInfoDisplay, change to the root OpenSonATA_2.0 directory and initiate the following command:
 * <ul>
 *  <li>./sonata_install/bin/sonataInfoDisplay ./sonata_archive/templogs/sse-system-status.txt ./sonata_archive/permlogs/systemlogs/systemlog-2010-08-13.txt ./sonata_archive/permlogs/errorlogs/errorlog-2010-08-13.txt</li>
 * </ul>
 *  <p>Now when you run the sonata-gen or sonata-vger scripts the information will display in this sonataInfoDisplay window. 
 *  <p>With the limited number of components running as the result of the sonata-gen or sonata-vger scripts being run (only 4), this program may not seem that useful. The real usefullness comes into play when there are 20+ components (the real system may run hundreds) and you can then page through them all viewing their status. Also, once the error logs and signal detection reports are integrated (see suggestion below) then this program will really clean up the screen.
 *
 
 *
 * <br>
 * <center><b>How you can help</b></center>
 * <p>
 * This code is far from complete. We are looking for help with the following items. Please let us know if you are interested in helping.
 * </p>
 * <p>
 *   <ul>
 *     <li>This program opens and read from various system files and parse the information for display. When The seeker is restarted, the seeker reopens these files, thus, sonataInfoDisplay needs to be restarted to re-initiate the reading. It would be best if this situation could be handled in the program and reset the file pointers upon this type of event.</li>
 *     <li>Occasionally this program slows down to a crawl. It seems to be in components::addWithFilter() and be associated with resizing the screen. When the slow down occurs, resizing the terminal window brings it back to life. Can anyone spot a memory leak or something that is being done ineffiently?</li>
 *     <li>Does anyone have any suggestions for any open source (or free) memory checker applications that would be suitable to review this code for leaks.</li>
 *     <li>The code is built to be able to add more screens. For instance the systemlog-YYYY-MM-DD.txt file can be read and parsed to display the signal detection reports. The user could select between the component status screen and the latest signal detection reports. Support for adding this is already built in, follow the example of components.cpp. Create a new class like Components that uses Details as a base class and make it display and page through the signal reports that are continuall added to systemlog-YYYY-MM-DD.txt.</li>
 *     <li>The same for error reports, it would be good to create another screen that parses errorlog-YYYY-MM-DD.txt and distills the errors in another screen.</li>
 *     <li>Are there any curses programming experts that can help with the following:
 *       <ul>
 *         <li>Make sure this curses program works in any xterm? Some xterm programs use a different character set and drawing corners, boxes, etc. do not work. Is there a way to standardize to make it work everywhere?</li>
 *         <li>The same goes for keypress interpertation under curses. Note that this program uses 8 to page down and 9 to page up. Admittedly this is lame, but we could not figure out how to make the PageUp and PageDown and arrow buttons work the same across different platform. Obviously there is a way to do this. Can anyone help us figure this out?</li>
 *       </ul>
 *     </li>
 *     <li>It would actually be better if the seeker program (which created these files that sonataInfoDisplay reads) would output something like an RSS feed, or an XML stream, instead of writing to log files. If a suitably flexible format could be defined and integrated into the seeker, then better and different and more effient programs can be developed, leading to a really good UI. Does anyone have any suggestions? Can we start a thread on the setiQuest forum?</li>
 *     <li>A better alternaive to this curses screen would be a Java application that could run on your desktop. If we could develop an RSS like feed such a program can read, this would be the best. Then we could make it really fancy, even showing graphical representations of the antenna pointing and a sky may showing what is being observed. Such a thing could also morph into a java applet that can be run in a browser for real time display to anyone anywhere in the world over the web<li>
 *     <li>Any other ideas? Please let us know via the forum!</li>
 * </ul>
 * 
 */
