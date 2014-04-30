Abstract	{#mainpage}
========

This project implements a daemon which acts as a node in a bitmessage network (http://bitmessage.org)

the daemon itself holds the connection to other nodes and collects and distibutes objects.

To use the objects or to generate them you must use a plugin.

At the moment there are no plugins availabel. But there are planned plugins for:

- debugging
- SMTP bridging
- bitmessge API
- gateway to mobile appications

Example for a plugin
====================

\include main.cpp
