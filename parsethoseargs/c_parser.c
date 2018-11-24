#include <string.h>
#include <stdlib.h>
// Includes all needed stuff.

typedef struct {
    char* ParsingString;
    int IgnoreQuotes;
    int HitAllArgs;
    char* LastParse;
} ArgParserStructure;
// The structure for the argument parser.

char Quote = '"';
// Defines a quote.

char Space = ' ';
// Defines a space.

static ArgParserStructure ArgParser_Next(ArgParserStructure structure) {
    if (strcmp(structure.ParsingString, "") == 0) {
        structure.HitAllArgs = 1;
        return structure;
    }
    // Returns if all arguments have been hit.

    int InQuotes = 0;
    // Sets if the parser is inside quotes.

    int ParsingStringLength = (int)strlen(structure.ParsingString);
    char* CurrentParse = calloc(ParsingStringLength, 1);
    // Defines the current parse.

    char* parsing_str = structure.ParsingString;
    while(*parsing_str != '\0') {
        char current_char = *parsing_str;
        // Gets the first character.

        if (current_char == Quote) {
            // This is a quote.
            if (InQuotes == 1) {
                // This is the end of some quoted text.
                int x = 0;
                int CurrentParseLength = (int)strlen(CurrentParse);
                char* NewParseString = calloc(ParsingStringLength + 1, 1);
                strcpy(NewParseString, structure.ParsingString);
                while (x != CurrentParseLength) {
                    NewParseString++;
                    x++;
                }
                NewParseString += 3;
                structure.ParsingString = NewParseString;
                structure.LastParse = CurrentParse;
                return structure;
            } else {
                // How do we handle the quote?
                if (structure.IgnoreQuotes) {
                    int CurrentParseLength = (int)strlen(CurrentParse);
                    CurrentParse[CurrentParseLength] = current_char;
                } else {
                    InQuotes = 1;
                }
            }
        } else if (current_char == Space) {
            // This is a space.
            if (InQuotes == 0) {
                // Probably count this as a break.
                if (!(strcmp(CurrentParse, "") == 0)) {
                    int x = 0;
                    int CurrentParseLength = (int)strlen(CurrentParse);
                    char *NewParseString = calloc((int)strlen(structure.ParsingString) + 1, 1);
                    strcpy(NewParseString, structure.ParsingString);
                    NewParseString++;
                    while (x != CurrentParseLength) {
                        NewParseString++;
                        x++;
                    }
                    structure.ParsingString = NewParseString;
                    structure.LastParse = CurrentParse;
                    return structure;
                }
            } else {
                // Add this to the quote text.
                int CurrentParseLength = (int)strlen(CurrentParse);
                CurrentParse[CurrentParseLength] = current_char;
            }
        } else {
            // Add this to the text.
            int CurrentParseLength = (int)strlen(CurrentParse);
            CurrentParse[CurrentParseLength] = current_char;
        }

        ++parsing_str;
        // Knocks off a character.
    }

    structure.ParsingString = "";
    structure.LastParse = CurrentParse;
    return structure;
    // All args done! Lets return the structure.
}
// Gets the next argument.
