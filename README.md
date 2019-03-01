GDW RPG Vehicles
================

Extensible vehicle database for Traveller and other GDW derived RPGs.

Building Vehicles from source
-----------------------------

1. Download and install Qt5 Creator and a suitable compiler kit for your
   platform.
2. Open Qt Creator and select "New Project". Click on the "Import Project"
   project template and then "Git Clone". Click on the "Choose..." button to
   continue.
3. Enter the repository URL in the "Repository" field and choose a path to
   check out the source into. Click on the "Continue" button.
4. Click on one of the green arrows in the the bottom right of the Qt Creator
   window to Run or Debug the application.

Design Notes
------------

This application is designed to be extensible and uses the object-oriented
principles of polymorphism and dynamic binding to achieve this. The object
model is quite simple: Vehicles aggregate zero or more Weapons, and both of
these are (model) Objects. To each Object a Qt Form (View) and a TreeItem are
created. The MainWindow and ItemModel supply the presentation framework and are
defined in terms of general top-level Objects, which gives them the ability to
deal with Vehicles and Weapons with equal ease.

Defining the application in this way makes it easier to extend. By sub-classing
the Object class and adding a specialized Form and TreeItem class for the new

model object. These new objects can also build on existing objects, extending
and aggregating them. For example, a Unit object can be envisioned representing
a fireteam that would add a class representing a small number of soldiers, but
also having weapons and vehicles. Conglomerate units can also easily be created
as they are merely Units of Units, but also contain their own Weapons and
Vehicles. Down the line Ship objects representing space- and starships can be
envisioned and implemented in the same way.

The underlying storage model is based on the JavaScript Object Notation (JSON)
which give a fast and extensible way to store (and send) structured data.
Though not as expressive and readable as YAML or maybe XML, it does enjoy wide
support. In particular, Qt5, which this application is built on, has fast
native encoder/decoders as part of its framework, so we chose this as our
serialization medium. Since JSON code is actually also valid YAML, the storage
model can be upgraded and extended down the line.
-------------------------------------------------------------------------------
---
The Traveller game in all forms is owned by Far Future Enterprises.
Copyright 1977 - 2008 Far Future Enterprises.
