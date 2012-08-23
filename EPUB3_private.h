#include <stdio.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xmlreader.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <sys/types.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <dirent.h>
#include "unzip.h"
#include "EPUB3.h"

#ifndef EPUB3_private_h
#define EPUB3_private_h

#define EXPORT __attribute__((visibility("default")))

typedef enum { kEPUB3_NO = 0 , kEPUB3_YES = 1 } EPUB3Bool;

const char * kEPUB3TypeID;
const char * kEPUB3MetadataTypeID;

#pragma mark - Internal XML Parsing State

typedef enum {
  kEPUB3OPFStateRoot = 0,
  kEPUB3OPFStateMetadata,
  kEPUB3OPFStateManifest,
  kEPUB3OPFStateSpine
} EPUB3OPFParseState;

typedef struct _EPUB3OPFParseStateContext {
  EPUB3OPFParseState state;
  const xmlChar *tagName;
  EPUB3Bool shouldParseTextNode;
  int depth;
} EPUB3OPFParseStateContext;

typedef EPUB3OPFParseStateContext * EPUB3OPFParseStateContextPtr;

#pragma mark - Type definitions

typedef struct EPUB3Type {
  const char *typeID;
  uint32_t refCount;
} EPUB3Type;

struct EPUB3Object {
  EPUB3Type _type;
};

typedef struct EPUB3Object *EPUB3ObjectRef;

struct EPUB3 {
  EPUB3Type _type;
  EPUB3MetadataRef metadata;
  char * archivePath;
  unzFile archive;
  uint32_t archiveFileCount;
};

struct EPUB3Metadata {
  EPUB3Type _type;
  EPUB3Version version;
  char * title;
  char * _uniqueIdentifierID;
  char * identifier;
  char * language;
  // char * modified;
};

#pragma mark - Function Declarations

void _EPUB3ObjectRelease(void *object);
void _EPUB3ObjectRetain(void *object);
void * _EPUB3ObjectInitWithTypeID(void *object, const char *typeID);

EPUB3Ref EPUB3Create();
EPUB3MetadataRef EPUB3MetadataCreate();
void EPUB3SetStringValue(char ** location, const char *value);
char * EPUB3CopyStringValue(char ** location);
void EPUB3SetMetadata(EPUB3Ref epub, EPUB3MetadataRef metadata);
EPUB3Error EPUB3CopyFileIntoBuffer(EPUB3Ref epub, void **buffer, uint32_t *bufferSize, uint32_t *bytesCopied, const char * filename);
EPUB3Error _EPUB3ParseXMLReaderNodeForOPF(EPUB3Ref epub, xmlTextReaderPtr reader, EPUB3OPFParseStateContextPtr *currentContext);
EPUB3Error EPUB3InitMetadataFromOPF(EPUB3Ref epub, const char * opfFilename);

#pragma mark - Validation
EPUB3Error EPUB3ValidateMimetype(EPUB3Ref epub);
EPUB3Error EPUB3CopyRootFilePathFromContainer(EPUB3Ref epub, char ** rootPath);
EPUB3Error EPUB3ValidateFileExistsAndSeekInArchive(EPUB3Ref epub, const char * filename);

#pragma mark - Utility Functions
uint32_t _GetFileCountInZipFile(unzFile file);
EPUB3Error EPUB3GetUncompressedSizeOfFileInArchive(EPUB3Ref epub, uint32_t *uncompressedSize, const char *filename);


#endif
