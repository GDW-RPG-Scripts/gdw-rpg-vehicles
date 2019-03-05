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

This application is designed to be extensible, and as a study in developing
cross platform applications. It uses the object-oriented principles of
polymorphic views and dynamic binding to achieve its extensibility. The object
model is quite simple: Vehicles aggregate zero or more Weapons, and both of
these are (model) Objects. To present the two types of Objects a Qt Form
and a TreeItem are created for each object type. The application's MainWindow
and ItemModel supply the presentation framework, and are defined in terms of
the general, top-level Object type. This gives the applications the ability to
deal with Vehicles and Weapons with equal ease, injecting their respective
views when necessary.

Defining the application in this way makes it easier to extend. By sub-classing
the Object class and adding a specialized Form and TreeItem class for the new
model object together with updating a couple of creator functions a new model
object can be added. These new objects can also build on existing objects,
extending and aggregating them. For example, a Unit object can be envisioned
representing a fireteam that would add a class representing a small number of
soldiers, but also having (aggregating) weapons and vehicles. Conglomerate
units can also easily be created as they are merely Units of Units, but also
contain their own Weapons and Vehicles. Down the line Ship objects representing
space- and starships can be envisioned and implemented in the same way.

The underlying storage model is based on the JavaScript Object Notation (JSON)
which gives the application a fast and extensible way to store (and share)
structured data. Though not as expressive and readable as YAML or maybe XML,
it does enjoy wide support. In particular, Qt5, on which this application is
built on, has fast native encoder/decoders as part of its framework, so we
chose this as our serialization medium. Since JSON code is actually also valid
YAML, the storage model can be upgraded and extended down the line.

---
The Traveller game in all forms is owned by Far Future Enterprises.
Copyright 1977 - 2008 Far Future Enterprises.
