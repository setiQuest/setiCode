/**
 * @mainpage openSonATA Documentation
 *
 * <center>
 * Waterfall and Basefile Display Programs<BR>
 * Release 2.1<BR>
 * Release Date Aug 20, 2010<BR>
 * Visit <a href="http://setiQuest.org" target="_setiquest">setiQuest.org</a>
 * for participation details.
 * </center>
 *
 * <br>
 * <p>The waterfall display shows the power for each bin in a subchannel. The power values are reported every .75 seconds. The brighter the dot, the stronger the power.
 * </p>
 * <p>The baseline display shows the average power in each subchannel over channel bandwidth. The baseline is averaged over time and is reported every 15 or so seconds.
 * </p>
 * <p>These programs read data files that are created by the DXs (the SonATA detector module) which filters and transforms a single channel into 768 711Hz-subchannels and further to 768  .694Hz-bins.
 * </p>
 *
 * <br>
 * <center><b>How you can use this software</b></center>
 * <p>This is the source code to the Waterfall and baseline Display programs that display on your screen when you run either the sonata-gen or sonata-vger scripts. You may investigate this code, make improvements, replace the existing WaterFallDisplay or BaselineDisplay programs and see if you can make improvements. Or just play!
 * <br>
 * <center><b>How You Can help</b></center>
 * <p>
 *  
 * </p>
 * <p>
 *   <ul>
 *     <li>Anyone want to do a code review?</li>
 *     <li>Can the FFT be faster?</li>
 *     <li>Can anyone suggest user interface improvements? A better user interface? Maybe combining these 2 programs into one?</li>
 *     <li>Could we add an option for these files to read from a TCP socket? Currently these programs read data files.</li>
 *     <li>Any other ideas? Please let us know via the forum!</li>
 * </ul>
 * 
 */

