import re
import string
import os.path



def ItemCount():
     f = open("CS210_Project_Three_Input_File.txt", "r") #opens the file

     dictionary = dict() #creates an emtpy dictionary for store words
     
     for line in f:
        line = line.strip() #remove any garbage spaces and newline characters

        word = line.lower() #lower case to help match better
        
        #Checking if the word is already in the dictionary and increasing by one
        if word in dictionary:
            dictionary[word] = dictionary[word] + 1

        else:
            dictionary[word] = 1 #if only one word is present then the value is 1

    #Print 
     for key in list (dictionary.keys()):
        print(key.capitalize(),":", dictionary[key])

        f.close() #closes the file


def WordSearch(userSearch):

    #Makes user input lower case to help match better
    userSearch = userSearch.lower()

    f = open("CS210_Project_Three_Input_File.txt", "r") #Open the file in read mode

    wordCount = 0 #variable for number of words found

    #Check each line of the input file
    for line in f:
        line = line.strip() #remove any garbage spaces and newline characters
        word = line.lower() #lower case to help match better
        
        #Check if the found word is equal to the user's input
        if word == userSearch:
            wordCount += 1  #If yes then increase wordCount

    return wordCount #Return the number of times the user's input was found

    f.close()  #Close opened file

def CollectData():

    f = open("CS210_Project_Three_Input_File.txt", "r") #Open the input file in read mode

    frequency = open("frequency.dat", "w") #Create and/or write the file frequency.dat

    dictionary = dict() #creates an emtpy dictionary for store words

    #Check each line of the input file
    for line in f:
        line = line.strip() #remove any garbage spaces and newline characters

        word = line.lower() #lower case to help match better
        
        #Checking if the word is already in the dictionary and increasing by one
        if word in dictionary:
            dictionary[word] = dictionary[word] + 1

        else:
            dictionary[word] = 1 #if only one word is present then the value is 1

    #Write each key and value pair to frequency.dat
    for key in list (dictionary.keys()):
        frequency.write(str(key.capitalize()) + " " + str(dictionary[key])) #Format the key-value pair as strings followed by a newline.

    #Close the opened files
    f.close()
    frequency.close()

