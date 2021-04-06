#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(){
    char line;

    bool stopWriting = false;
    bool multiComment = false;

    FILE * readFrom = fopen("test.txt", "r"); // This is the file you read from; replace path for your files
    FILE * writeTo = fopen("test2.txt", "w"); // This creates the file that doesn't have comments; Can be any filetype, not just txt

    if (readFrom != NULL){ // Checking if the readFrom file exists
        while ((line = fgetc(readFrom)) != EOF) // Looping through the file
        {
            if (line == '/'){ // Checking for the comment indicator
                line = fgetc(readFrom); // Checking the next char
                if (line == '/'){ // If its a single line comment
                    stopWriting = true; // Stop writing to the file
                } else if (line == '*'){ // If its a multiline comment
                    stopWriting = true; // Stop writing to the file
                    multiComment = true; // neccesary for checking the end comment indicator
                } else {
                    fprintf(writeTo, "/"); // Else just write the slash
                }
            }
            if (line == '\n' && !multiComment){ // If its a single line comment and a newline
                stopWriting = false; // You can start writing to the file
            }
            if (multiComment){ // If its a multiline comment
                if (line == '*'){ // Start of the end comment indicator
                    line = fgetc(readFrom); // Check the next char
                    if (line == '/'){ // If its the rest of the end comment indicator
                        multiComment = false; // The multiline comment is done
                        stopWriting = false; // You can start writing again
                        line = fgetc(readFrom); // Get the next char for writing to the file
                    }
                }
            }
            if (!stopWriting && line != EOF){ // If you can write and its not the end of the file
                fprintf(writeTo, "%c", line); // Write to the file
            }
        }
    }
    // Closing the files
    fclose(readFrom);
    fclose(writeTo);
}