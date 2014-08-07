# GisBin #

This project pretends to be an utility tool that performs binnig of geographic coordinates.

It is being developed in C using Visual Studio 2012.

## Context ##

Given a large amount of geographical information, there is the need to group that information into bins so that it can be easier to interpret and lighter to present. 

Given a set of coordinates this tool will give the correspondent bin coordinate.

Example for bins of aprox. 11 meters:

	┌───────────────────────┬──────────────────────┐
	│   Given coordinates   │    Bin Coordinates   │
	├───────────┬───────────┼──────────┬───────────┤
	│ Latitude  │ Longitude │ Latitude │ Longitude │
	├───────────┼───────────┼──────────┼───────────┤
	│ 38.756006 │ -9.133004 │ 38.75600 │ -9,13296  │
	│ 38.756036 │ -9.132974 │ 38.75600 │ -9,13296  │	
	│ 38.756066 │ -9.132944 │ 38.75610 │ -9,13296  │	
	│ 38.756096 │ -9.132914 │ 38.75610 │ -9,13296  │	
	│ 38.756126 │ -9.132884 │ 38.75610 │ -9,13284  │	
	│ 38.756156 │ -9.132854 │ 38.75620 │ -9,13284  │	
	│ 38.756186 │ -9.132824 │ 38.75620 │ -9,13284  │	
	│ 38.756216 │ -9.132794 │ 38.75620 │ -9,13284  │	
	│ 38.756246 │ -9.132764 │ 38.75620 │ -9,13272  │	
	└───────────┴───────────┴──────────┴───────────┘    


## Limitations ##

At this moment, and for the sake of simplicity, the tool only provides bins of 11, 27, 55 and 110 meters.

This is due to the way the latitude works: 1 Degree of latitude is arround 111.11 km.

Therefore it is very simple to have bins of 11 meters or 111 meters on the latitude, since all we have to do is to round the latitude on the 4ht or the 3rd decimal place, respectively.

## Calculations ##

As mentioned above, the latitude binning is made by simply rounding the latitude. Here is the table of the latitude binnings made:

	┌────────────┬─────────────────┬────────────────────────────────────────┐
	│ Name given │ Meters (aprox.) │ Method                                 │
	├────────────┼─────────────────┼────────────────────────────────────────┤
	│ 10         │       11        │ Rounded at the 4th decimal place       │
	│ 25         │       27        │ Rounded by 25 at the 5th decimal place │	
	│ 50         │       55        │ Rounded by 5 at the 4th decimal place  │	
	│ 100        │       111       │ Rounded at the 3rd decimal place       │	
	└────────────┴─────────────────┴────────────────────────────────────────┘

Since the earth is not a perfect sphere, the longitude binning was made accordingly to the formula presented in wikipedia for the [length of a degree of longitude](http://en.wikipedia.org/wiki/Longitude#Length_of_a_degree_of_longitude "Length of a degree of longitude")