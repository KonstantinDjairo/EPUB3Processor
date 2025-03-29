/**
* THIS IS THE HEADER TO IMPORT
*/
#import "EPUB3.h"


/**
* EXAMPLE USAGE
*/

// create an EPUB3Ref
EPUB3Error result;
EPUB3Ref epub = EPUB3CreateWithArchiveAtPath(<path to epub>, &result);

// extraction of EPUB
EPUB3Error result = EPUB3ExtractArchiveToPath(epub, <path to extract directory>);

// get title
char * title = EPUB3CopyTitle(epub);

// book unique identifier
char * identifier = EPUB3CopyIdentifier(epub);

// REFER TO EPUB3.h FOR ALL API CALLS
