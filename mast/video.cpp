#include "mastint.h"
#include <stdio.h>
#ifdef unix
#include <unistd.h>
#include <sys/types.h>
#endif
#ifdef WIN32
#include <windows.h>
#include <io.h>
#endif

static FILE *videoFile = NULL;
static char videoFilename[256];
static int videoMode = 0;
static int rerecordCount, beginReset;

int frameCount;

#define SAVE_STATE_SIZE 25088

static int MastAcbVideoRead(struct MastArea *area) {
	fread(area->Data, area->Len, 1, videoFile);
	return 0;
}

static int MastAcbVideoWrite(struct MastArea *area) {
	fwrite(area->Data, area->Len, 1, videoFile);
	return 0;
}

void MvidStart(char *filename, int mode, int reset) {
	if (videoFile != NULL) {
		fclose(videoFile);
		videoFile = NULL;
	}

	videoMode = mode;
	strncpy(videoFilename, filename, sizeof(videoFilename)); videoFilename[sizeof(videoFilename)-1] = 0;
	frameCount = 0;

	if (mode == PLAYBACK_MODE) {
		videoFile = fopen(filename, "rb");
		if (videoFile != NULL) {
			fseek(videoFile, 0xc, SEEK_SET);
			fread(&rerecordCount, 4, 1, videoFile);
			fread(&reset, 4, 1, videoFile);

			fseek(videoFile, 0x20, SEEK_SET);
			if (reset) {
				MastHardReset();
			} else {
				MastAcb = MastAcbVideoRead;
				MastAreaDega();
			}
		}
	} else if (mode == RECORD_MODE) {
		videoFile = fopen(filename, "wb");
		if (videoFile != NULL) {
			int zero = 0;
			fwrite("MMV", 4, 1, videoFile);    // 0000: identifier
			fwrite(&MastVer, 4, 1, videoFile); // 0004: version
			fwrite(&zero, 4, 1, videoFile);    // 0008: frame count
			fwrite(&zero, 4, 1, videoFile);    // 000c: rerecord count
			rerecordCount = 0;
			fwrite(&reset, 4, 1, videoFile);   // 0010: begin from reset?
		
			fwrite(&zero, 4, 1, videoFile);    // 0014-001f: reserved
			fwrite(&zero, 4, 1, videoFile);
			fwrite(&zero, 4, 1, videoFile);

			if (reset) {
				MastHardReset();
			} else {
				MastAcb = MastAcbVideoWrite;
				MastAreaDega();
			}
		}
	}

	if (videoFile == NULL) {
		perror("while opening video file: fopen");
	}

	beginReset = reset;
}

void MvidStop() {
	if (videoFile != NULL) {
		MastInput[0] = MastInput[1] = 0;
		fclose(videoFile);
		videoFile = NULL;
	}
}
	
void MvidPreFrame() {
	int result;
	frameCount++;

	if (videoFile != NULL) {
		switch (videoMode) {
			case PLAYBACK_MODE:
				result = fread(MastInput, sizeof(MastInput), 1, videoFile);

				if (result == 0) {
					MvidStop();
				}

				break;
			case RECORD_MODE:
				fwrite(MastInput, sizeof(MastInput), 1, videoFile);

				fseek(videoFile, 0x8, SEEK_SET);
				fwrite(&frameCount, 4, 1, videoFile);
				fseek(videoFile, 0, SEEK_END);

				break;
		}
	}
}

void MvidPostLoadState() {
	if (videoFile != NULL) {
		int newSize = 0x20 + (beginReset ? 0 : SAVE_STATE_SIZE) + frameCount*sizeof(MastInput);

		fclose(videoFile);

		videoFile = fopen(videoFilename, "r+b");
#ifdef unix
		ftruncate(fileno(videoFile), newSize);
#else
#ifdef WIN32
		fseek(videoFile, newSize, SEEK_SET);
		SetEndOfFile((HANDLE)_get_osfhandle(_fileno(videoFile)));
#else
#error no truncate implementation available!
#endif
#endif
		rerecordCount++;

		fseek(videoFile, 0xc, SEEK_SET);
		fwrite(&rerecordCount, 4, 1, videoFile);

		fseek(videoFile, 0, SEEK_END);
		videoMode = RECORD_MODE;
	}
}
