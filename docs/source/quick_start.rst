.. _quick_start:

===========
Quick Start
===========

.. _viewing_figures:

Viewing Figures
===============

A browser based viewer is supplied at `https://cpplot.herokuapp.com <https://cpplot.herokuapp.com>`__.
Navigate to that link and you'll be able to view and export figures created with **cpplot**.

The viewer always keeps your data local (files are never uploaded to a server).

If you've not created figure files yourself yet, you can
`download the examples from here <https://github.com/thclark/cpplot/tree/master/examples>`__
and then select them in the viewer. Some are simple, some are amazing ;)


.. _create_your_first_figure:

Create Your First Figure
========================

To create your first figure with **cpplot**, you can compile and run the program below:

.. code-block:: cpp

   /*
    * main.cpp - An example program to create your first figure as a Plotly-compliant .json file.
    *
    * Author:              YOU
    *
    * Copyright (c) YEAR YOU. All Rights Reserved.
    *
    */
   #include <stdio.h>
   #include <iostream>
   #include <Eigen/Dense>
   #include "cpplot.h"     // TODO these may need to change to something like <cpplot> for users
   #include "eigen.h"      //  who have installed the library rather than linking against source code
   #include "exceptions.h" //  directly

   using namespace std;
   using namespace Eigen;
   using namespace cpplot;

   int main(int argc, char* argv[]) {

       // Create a figure object
       Figure fig = Figure();

       // Create a scatter plot object and set its values
       ScatterPlot p1 = ScatterPlot();
       p1.x = Eigen::VectorXd::LinSpaced(10, 0.0, 1.0);
       p1.y = Eigen::VectorXd::LinSpaced(10, 1.0, 2.0);

       // Alter its properties
       p1.name = "my first trace";
       p.setWidth(1);
       p.setDash("dash");
       p.setColor("#e377c2");  // "Raspberry yoghurt pink", obviously the best selection

       // Add it to the figure
       fig.add(p1);

       // You can add multiple plots to a figure...
       ScatterPlot p2 = ScatterPlot();
       p2.name = "my second trace";
       fig.add(p2);

       // And whenever you want, you can write a figure to disc.
       // Note, writing is an async task so your calculations can
       // proceed whilst writing goes into the background.
       //
       // In this example we allow the write() method to automatically append a `.json` extension
       // to the file name (if not already present), and we prevent it from printing the json to stdout
       // (which can be a useful feature to enable if you want to use your program with bash pipes)
       std::cout << "Writing figure to current directory: " << std::endl;
       fig.write("my_first_cpplot_figure", true, false);

   }


.. _building_web_tools:

Building Your Own Web Tools
===========================

You (or the frontend team you work with!) will probably want to display figures in your own web tools, rather than
always our (fairly basic, right now) viewer utility.

The `browser viewer <https://cpplot.herokuapp.com>`__ is built in React (using ``react-plotly.js``).
It is also open-source, so you can use its components as a basis for your own. See
`https://github.com/thclark/cpplot-viewer <https://github.com/thclark/cpplot-viewer>`__
