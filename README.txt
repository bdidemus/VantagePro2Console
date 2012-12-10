*	Name: Davis Vantage Pro2 Console Reader			 
*	Author: Brett Didemus		
*	Platform: Linux			 
*	Date: October 2012
*	Format: Raw C++ source

*	Pulls live data from the davis Vantage Pro 2 console
	weather station system


The Davis Vantage Pro 2 is a weather station console that measures a number
of enviromental variables. Temperature, Humidity, Rain Rate, barometric pressure.

The default application that came with the vantage Pro 2 console didn't suit the needs
of a project that required live data to  be streamed to a remote server. This application
runs an initite loop that queries and posts live data to a web server hosting php script that
saves the data to a database.


Setup
================
To setup the system:
1. Create a mysql database as defined in database.sql
2. Load the php scripts to a webserver and set login variables in Class.MySQLDatabase.php
3. Edit postdata.cpp and change m_webPath variable to the location of your web server
4. Compile
5. Run on computer with David Vantage Pro 2 conneced. Default path to console is /dev/ttyUSB0.
Execute with altenate path as a parameter if your console is location somewhere else

	