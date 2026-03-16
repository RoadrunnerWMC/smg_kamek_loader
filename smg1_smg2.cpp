#include "kamekLoader.h"

// based on the Syati loader
// by SunakazeKun, Jonathan, Lord-Giganticus, bavario-lginc, shibboleet,
// Evanbowl, SuperHackio, and RoadrunnerWMC


// Custom code will be loaded into SystemHeap. However, the space that it provides is very limited,
// so the heaps need to be expanded early on during the game's initialization process. By default,
// SystemHeap has enough space to fit more than 80 KB of custom code (including .text and .bss from
// the CustomCode binaries). If our code requires more space, the loader will expand SystemHeap's
// memory by taking away some from HeapNapa/SceneHeapNapa.


#if !defined(SMG1) && !defined(SMG2)
#error "must specify -DSMG1 and/or -DSMG2"
#endif

#define ALIGN_32(a) ((a + 31) & ~31)


// enable crash debugger                               1P 1E 1J 1K 1C 2P 2E 2J 2W 2K
// ---------------------------------------------------------------------------------
#ifdef SMG1
kmCondWrite32(0x8039AA48, 0x98040068, 0x60000000);  // 1P
kmCondWrite32(0x8039AA2C, 0x98040068, 0x60000000);  //    1E 1J
kmCondWrite32(0x8039BF80, 0x98040068, 0x60000000);  //          1K
kmCondWrite32(0x804067CC, 0x98040068, 0x60000000);  //             1C
#endif
#ifdef SMG2
kmCondWrite32(0x804B7D90, 0x98040068, 0x60000000);  //                2P 2E 2J
kmCondWrite32(0x804B7E00, 0x98040068, 0x60000000);  //                         2W 2K
#endif
// ---------------------------------------------------------------------------------
#ifdef SMG1
kmCondWrite32(0x8039AB0C, 0x4082FFB8, 0x60000000);  // 1P
kmCondWrite32(0x8039AAF0, 0x4082FFB8, 0x60000000);  //    1E 1J
kmCondWrite32(0x8039C044, 0x4082FFB8, 0x60000000);  //          1K
kmCondWrite32(0x804068D4, 0x4082FFB4, 0x60000000);  //             1C
#endif
#ifdef SMG2
kmCondWrite32(0x804B7E54, 0x4082FFB8, 0x60000000);  //                2P 2E 2J
kmCondWrite32(0x804B7EC4, 0x4082FFB8, 0x60000000);  //                         2W 2K
#endif
// ---------------------------------------------------------------------------------
#ifdef SMG1
kmCondWrite32(0x804A402C, 0x4BFFC941, 0x60000000);  // 1P 1E
kmCondWrite32(0x804A400C, 0x4BFFC941, 0x60000000);  //       1J
kmCondWrite32(0x804A626C, 0x4BFFC941, 0x60000000);  //          1K
kmCondWrite32(0x806034D4, 0x4BFFCB1D, 0x60000000);  //             1C
#endif
#ifdef SMG2
kmCondWrite32(0x805B63A8, 0x4BFFC769, 0x60000000);  //                2P 2E 2J
kmCondWrite32(0x805B64A8, 0x4BFFC769, 0x60000000);  //                         2W 2K
#endif
// ---------------------------------------------------------------------------------
#ifdef SMG1
kmCondWrite32(0x804A432C, 0x48000160, 0x60000000);  // 1P 1E
kmCondWrite32(0x804A430C, 0x48000160, 0x60000000);  //       1J
kmCondWrite32(0x804A656C, 0x48000160, 0x60000000);  //          1K
kmCondWrite32(0x806037D4, 0x48000160, 0x60000000);  //             1C
#endif
#ifdef SMG2
kmCondWrite32(0x805B66B4, 0x48000160, 0x60000000);  //                2P 2E 2J
kmCondWrite32(0x805B67B4, 0x48000160, 0x60000000);  //                         2W 2K
#endif
// ---------------------------------------------------------------------------------


// FUNCTION TYPEDEFS HERE

void *allocAdapter(u32 size, bool isForCode, const loaderFunctions *funcs);
void freeAdapter(void *buffer, bool isForCode, const loaderFunctions *funcs);

struct loaderFunctionsEx {
	loaderFunctions base;
	// MORE FUNCTIONS HERE
};

#ifdef SMG1
const loaderFunctionsEx functions_1P_1E = {
	{(OSReport_t) 0x804A3E94,
	(OSFatal_t) 0x804A6C1C,
	(DVDConvertPathToEntrynum_t) 0x804BEF5C,
	(DVDFastOpen_t) 0x804BF264,
	(DVDReadPrio_t) 0x804BF844,
	(DVDClose_t) 0x804BF578,
	(sprintf_t) 0x8051D014,
	allocAdapter,
	freeAdapter}
};
const loaderFunctionsEx functions_1J = {
	{(OSReport_t) 0x804A3E74,
	(OSFatal_t) 0x804A6BFC,
	(DVDConvertPathToEntrynum_t) 0x804BEF3C,
	(DVDFastOpen_t) 0x804BF244,
	(DVDReadPrio_t) 0x804BF824,
	(DVDClose_t) 0x804BF558,
	(sprintf_t) 0x8051CFF4,
	allocAdapter,
	freeAdapter}
};
const loaderFunctionsEx functions_1K = {
	{(OSReport_t) 0x804A60D4,
	(OSFatal_t) 0x804A8298,
	(DVDConvertPathToEntrynum_t) 0x804C13E4,
	(DVDFastOpen_t) 0x804C16EC,
	(DVDReadPrio_t) 0x804C1CCC,
	(DVDClose_t) 0x804C1A00,
	(sprintf_t) 0x8051E5A4,
	allocAdapter,
	freeAdapter}
};
const loaderFunctionsEx functions_1C = {
	{(OSReport_t) 0x8060333C,
	(OSFatal_t) 0x80605500,
	(DVDConvertPathToEntrynum_t) 0x8061E4A0,
	(DVDFastOpen_t) 0x8061E7A8,
	(DVDReadPrio_t) 0x8061ED88,
	(DVDClose_t) 0x8061EABC,
	(sprintf_t) 0x8067B4AC,
	allocAdapter,
	freeAdapter}
};
#endif

#ifdef SMG2
const loaderFunctionsEx functions_2P_2E_2J = {
	{(OSReport_t) 0x805B6210,
	(OSFatal_t) 0x805B8500,
	(DVDConvertPathToEntrynum_t) 0x805D1370,
	(DVDFastOpen_t) 0x805D1680,
	(DVDReadPrio_t) 0x805D1A50,
	(DVDClose_t) 0x805D1810,
	(sprintf_t) 0x80633CBC,
	allocAdapter,
	freeAdapter}
};
const loaderFunctionsEx functions_2W_2K = {
	{(OSReport_t) 0x805B6310,
	(OSFatal_t) 0x805B8600,
	(DVDConvertPathToEntrynum_t) 0x805D1470,
	(DVDFastOpen_t) 0x805D1780,
	(DVDReadPrio_t) 0x805D1B50,
	(DVDClose_t) 0x805D1910,
	(sprintf_t) 0x8063422C,
	allocAdapter,
	freeAdapter}
};
#endif


union versionInfo {
	struct {
		u8 game;
		char region;
	};
	u16 pair;
};

static versionInfo sVersionInfo;

void unknownVersion() {
	// can't do much here!
	// we can't output a message on screen without a valid OSFatal addr;
	// all we can really do is set the screen to solid red before we die
	// (note: Dolphin Emulator currently ignores this)
	unsigned int *HW_VISOLID = (unsigned int*)0xcd000024;
	*HW_VISOLID = 0x5aef5101;

	for (;;);
}

void setVersionInfo() {
	switch (*((u32*)0x80017FC8))
	{
#ifdef SMG1
		case 0x4841A5CC: sVersionInfo.pair = '\1P'; break;
		case 0x4841A5B0: sVersionInfo.pair = '\1E'; break;
		case 0x4841A5AC: sVersionInfo.pair = '\1J'; break;
		case 0x90610010: sVersionInfo.pair = '\1K'; break;
		case 0x389C0008: sVersionInfo.pair = '\1C'; break;
#endif
#ifdef SMG2
		case 0x388427D4: sVersionInfo.pair = '\2P'; break;
		case 0x3884D0D4: sVersionInfo.pair = '\2E'; break;
		case 0x3884C8B4: sVersionInfo.pair = '\2J'; break;
		case 0x3884BF14: sVersionInfo.pair = '\2K'; break;
		case 0x3884D374: sVersionInfo.pair = '\2W'; break;
#endif
		default: unknownVersion();
	}
}


static const struct loaderFunctionsEx *sFuncs;

void setFuncs() {
	switch (sVersionInfo.pair) {
#ifdef SMG1
		case '\1P':
		case '\1E': sFuncs = &functions_1P_1E; break;
		case '\1J': sFuncs = &functions_1J; break;
		case '\1K': sFuncs = &functions_1K; break;
		case '\1C': sFuncs = &functions_1C; break;
#endif
#ifdef SMG2
		case '\2P':
		case '\2E':
		case '\2J': sFuncs = &functions_2P_2E_2J; break;
		case '\2K':
		case '\2W': sFuncs = &functions_2W_2K; break;
#endif
	}
}


// "X"s are filled in by setKamekBinaryName()
#if defined(SMG2) && !defined(SMG1)
static const char *sKamekBinaryName = "/Code/SB4X01.bin";
#else
static const char *sKamekBinaryName = "/Code/RMGX01.bin";
#endif
#define KAMEK_BINARY_NAME_GAME_ID_OFFSET 6

void setKamekBinaryName() {
	// If we're built to support both games, add an additional runtime
	// check for the game
#if defined(SMG1) && defined(SMG2)
	// sKamekBinaryName refers to SMG1 by default in this configuration,
	// so we only have to overwrite it if that's wrong
	if (sVersionInfo.game == 2) {
		sKamekBinaryName[KAMEK_BINARY_NAME_GAME_ID_OFFSET + 0] = 'S';
		sKamekBinaryName[KAMEK_BINARY_NAME_GAME_ID_OFFSET + 1] = 'B';
		sKamekBinaryName[KAMEK_BINARY_NAME_GAME_ID_OFFSET + 2] = '4';
	}
#endif

	sKamekBinaryName[KAMEK_BINARY_NAME_GAME_ID_OFFSET + 3] = sVersionInfo.region;
}


static u32 sCodeSize;

void setCodeSize() {
	sCodeSize = getKamekBinaryCodeSize(sFuncs, sKamekBinaryName);
}


/*****************************************************************************************************************/
/* Get size of CustomCode and expand SystemHeap if necessary                                                     */
/*****************************************************************************************************************/

void getCustomCodeSizeAndCreateHeaps(HeapMemoryWatcher *heapWatcher) {
	setVersionInfo();
	setFuncs();
	setKamekBinaryName();
	setCodeSize();
	heapWatcher->createHeaps();
}

#if defined(SB4W) || defined(SB4K)
kmCall(0x804BD058, getCustomCodeSizeAndCreateHeaps);
#elif defined (SB4E) || defined(SB4P) || defined(SB4J)
kmCall(0x804BCFE8, getCustomCodeSizeAndCreateHeaps);
#endif









void *allocAdapter(u32 size, bool isForCode, const loaderFunctions *funcs) {
	const loaderFunctionsEx *funcsEx = (const loaderFunctionsEx *)funcs;
	void **heapPtr = isForCode ? funcsEx->mHeap_g_gameHeaps : funcsEx->mHeap_g_archiveHeap;
	void *text = funcsEx->EGG_Heap_alloc(size, 0x20, *heapPtr);
	if (isForCode) {
		funcs->OSReport("Code start at %p\n", text);
		codeAddr = (u32)text;
	}
	return text;
}

void freeAdapter(void *buffer, bool isForCode, const loaderFunctions *funcs) {
	const loaderFunctionsEx *funcsEx = (const loaderFunctionsEx *)funcs;
	void **heapPtr = isForCode ? funcsEx->mHeap_g_gameHeaps : funcsEx->mHeap_g_archiveHeap;
	funcsEx->EGG_Heap_free(buffer, *heapPtr);
}

int loadBinary() {
	char path[64];
	sFuncs->base.sprintf(path, "/CustomCode/CustomCode_SB4%c.bin", sVersionInfo.region);
	loadKamekBinaryFromDisc(&sFuncs->base, path);

	return 1;
}

extern vu32 aiControl:0xCD006C00;

void loadIntoNSMBW() {
	// set version before we do anything else
	sVersionInfo = checkVersion();

	// choose functions
	// (these are all the same in v1 and v2, thankfully)
	switch (sVersionInfo.region) {
		case 'P': sFuncs = &functions_p; break;
		case 'E': sFuncs = &functions_e; break;
		case 'J': sFuncs = &functions_j; break;
		case 'K': sFuncs = &functions_k; break;
		case 'W': sFuncs = &functions_w; break;
		case 'C': sFuncs = &functions_c; break;
	}

	// report some info
	sFuncs->base.OSReport("<< KAMEK - LOADER \trelease build: " __DATE__ " " __TIME__ " (" STRINGIFY(__CWCC__) "_" STRINGIFY(__CWBUILD__) ") >>\n");
	// sFuncs->base.OSReport("Detected game version: %c%d\n", sVersionInfo.region, sVersionInfo.revision);

	// reset the AI control register because libogc doesn't reset it right,
	// so on console the SDK can't initialize audio correctly when coming from the Riivolution channel
	aiControl = 0;

	// remove the BCA check
	// this not only fixes some USB loaders running mods if the game id is changed,
	// but also gains some of the time lost due to kamek binary injections
	*sFuncs->bcaCheck = 0x60000000;
	// we call __flush_cache to remove any stale instructions after writing to RAM
	sFuncs->__flush_cache(sFuncs->myBackGround_PhaseMethod, 4);

	// modify myBackGround_PhaseMethod to load rels earlier & load the kamek binary
	u32 temp[20];
	sFuncs->memcpy(&temp, sFuncs->myBackGround_PhaseMethod, 0x50);

	// set rel loading functions as the first entries in the table
	sFuncs->myBackGround_PhaseMethod[0] = temp[15];
	sFuncs->myBackGround_PhaseMethod[1] = temp[16];
	sFuncs->myBackGround_PhaseMethod[2] = temp[17];

	// set kamek binary loader as the fourth entry
	sFuncs->myBackGround_PhaseMethod[3] = (u32)&loadBinary;

	// set all the other functions
	sFuncs->memcpy(&sFuncs->myBackGround_PhaseMethod[4], &temp, 0x3C);
	sFuncs->myBackGround_PhaseMethod[19] = temp[18];
	sFuncs->myBackGround_PhaseMethod[20] = temp[19];

	sFuncs->__flush_cache(sFuncs->myBackGround_PhaseMethod, 0x50);
}

kmBranch(0x800042f4, loadIntoNSMBW);
