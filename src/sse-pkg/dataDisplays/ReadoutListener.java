/*
 * An interface used with ReadoutPlot that is called when
 * a new x,y position is to be read out.
 *
 * Project: OpenSonATA
 * Version: 1.0
 * Author:  Jon Richards (current maintainer)
 *          The OpenSonATA code is the result of many programmers over many
 *          years.
 *
 * Copyright 2010 The SETI Institute
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0 Unless required by
 * applicable law or agreed to in writing, software distributed
 * under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * Attribution must be: “Licensed through SETI” in all published
 * uses of the software including analytics based on the software,
 * combined and merged software, papers, articles, books, reports,
 * web pages, etc.
 */

/**
 * @file ReadoutListener.java
 *
 * An interface used with ReadoutPlot that is called when
 * a new x,y position is to be read out.
 *
 * Project: OpenSonATA
 * <BR>
 * Version: 1.0
 * <BR>
 * Authors:
 * - Jon Richards (current maintainer)
 * - The OpenSonATA code is the result of many programmers over many
 * years.
 */

package opensonata.dataDisplays;

/**
 * An interface used with ReadoutPlot that is called when
 * a new x,y position is to be read out.
 */
public interface ReadoutListener 
{
    /** 
     * Notify that a given xValue, yValue in the specified plot has
     * been selected for readout.
     *
     * @param source The plot containing the readout data.
     * @param xPlotValue  The xvalue of the plot position.
     * @param yPlotValue  The yvalue of the plot position.
     */
    public void readoutData(ReadoutPlot source, double xPlotValue,
			    double yPlotValue);
}
