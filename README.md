2nd year C Programming -Project

CSV reader


CSV (Comma-Separated Values) files are a common way to store tabular data, making them a
valuable format for data interchange between applicaDons. Write a program that reads house
temperature data from a CSV-file and prints a horizontal bar graph of the temperature in the selected
room. The CSV file starts with a header row and then conDnues with lines of comma separated data.
The header row contains two Dtles: Room and Temperature. Data lines contain room name and the
temperature separated by commas.
Temperature,Room
22.5,Kitchen
18.7,Living Room
24.2,Bedroom
20.1,Kitchen
12.3,Living Room
23.8,Bedroom
16.9,Kitchen
19.4,Living Room
13.7,Bedroom
21.8,Kitchen
11.5,Living Room
24.9,Bedroom
Program must ask user to select a room and then print the temperatures with one decimal precision
followed with a bar graph using dashes (-). Each dash corresponds to 0.5 cenDgrade and
temperatures in the range of 0 – 30 are printed as horizontal bars. Temperatures that are outside or
the range are printed as a single X on the lee. If the selected room does not exist then program must
print an error message.
For example, (not based on the data above):
Bedroom
20.4 ----------------------------------------
22.5 -------------------------------------------
21.4 ------------------------------------------
21.6 -----------------------------------------
32.3 X
18.2 ------------------------------------
18.8 -------------------------------------
19.5 --------------------------------------
21.3 -----------------------------------------
