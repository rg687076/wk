//
// Created by jun on 2021/06/14.
//
#include <vector>
#include <sstream>

#ifdef __ANDROID__
#include <android/log.h>
#else   /* __ANDROID__ */
#include "../../../../../../WinCG3DVewer/WinCG3DVewer/ComDef.h"
#endif  /* __ANDROID__ */
#include <fstream>
#include "FBX.h"
#include "import_fbx.h"

namespace fbx {

/**********************/
/* import_fbx::load() */
/**********************/
bool import_fbx::load(const std::vector<char> &ModelData) {
using ibinstream = std::istringstream;

	ibinstream ibs(std::string(ModelData.begin(), ModelData.end()));

	ibs.seekg(0, std::ios::end);
	int filesize = ibs.tellg();
	ibs.seekg(0, std::ios::beg);
	int fpos = ibs.tellg();

	/* MAGICWORD */
	const char magicword[23] = {'K','a','y','d','a','r','a',' ','F','B','X',' ','B','i','n','a','r','y',' ',' ',0x00,0x1A,0x00};
	char fbxmagic[sizeof(magicword)] = {};
	ibs.read(fbxmagic, sizeof(magicword));
	if (std::memcmp(magicword, fbxmagic, sizeof(magicword)) != 0) {
		__android_log_print(ANDROID_LOG_DEBUG, "aaaaa", "aaaaa Load(%s) Failed!! Unmatch MAGICWORD!!\n");
		return false;
	}

	/* FBXバージョン */
	int fbxversion;
	ibs.read(reinterpret_cast<char*>(&fbxversion), sizeof(int));

	__android_log_print(ANDROID_LOG_DEBUG, "aaaaa", "aaaaa FBX version(%d)\n", fbxversion);

	/* FBXUtil初期化 */
	bool ret = FbxUtil::init((Version)fbxversion);
	if (!ret) return false;

	/**********************/
	/* エレメント一括読出 */
	/**********************/
	std::vector<FbxElem> rootElem;
	while(true) {
		FbxElem allElems = FbxUtil::readElements(ibs);
		if(allElems.end_offset == 0)
			break;
#ifndef __ANDROID__
		//UTF-8からUTF-16へ変換
		const int nSize = ::MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)"D:\\testaaaaログ\\エレメント一覧.log", -1, NULL, 0);
		BYTE* buffUtf16 = new BYTE[nSize * 2 + 2];
		::MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)"D:\\testaaaaログ\\エレメント一覧.log", -1, (LPWSTR)buffUtf16, nSize);
		//UTF-16からShift-JISへ変換
		const int nSizeSJis = ::WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)buffUtf16, -1, NULL, 0, NULL, NULL);
		BYTE* buffSJis = new BYTE[nSizeSJis * 2];
		ZeroMemory(buffSJis, nSizeSJis * 2);
		::WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)buffUtf16, -1, (LPSTR)buffSJis, nSizeSJis, NULL, NULL);
		BYTE dstStr[100] = { 0 };
		memcpy(dstStr, buffSJis, nSizeSJis*2);
		delete[] buffUtf16;
		delete[] buffSJis;
		char cDstStr[100] = {};
		memcpy(cDstStr, dstStr, sizeof(cDstStr));

//		std::ofstream ofs(cDstStr, std::ios::app);
		std::ofstream ofs(cDstStr);
		ofs << allElems.toString(0);
		ofs.close();
#endif /*__ANDROID__*/
		rootElem.push_back(allElems);
	}

	/**********************/
	/* GlobalSettings取得 */
	/**********************/
	/* GlobalSettingsキーを探索 */
	std::vector<FbxElem>::iterator gsitr = std::find_if(rootElem.begin(), rootElem.end(), [](const FbxElem &item){ return item.id=="GlobalSettings"; });
	if(gsitr == rootElem.end())
		throw std::runtime_error("error ありえない!! GlobalSettingsキーがない!!");
	
	std::vector<FbxElem>::iterator p70itr = std::find_if(gsitr->elems.begin(), gsitr->elems.end(), [](const FbxElem& item) { return item.id == "Properties70"; });
	if (p70itr == gsitr->elems.end())
		throw std::runtime_error("error ありえない!! Properties70キーがない!!");

	FbxElem &gs  = *gsitr;
	FbxElem &p70 = *p70itr;

	double unitscale = FbxUtil::getPropDouble(p70, "UnitScaleFactor");
	//p70.props
	//unit_scale = elem_props_get_number(fbx_settings_props, b'UnitScaleFactor', 1.0)
	//unit_scale_org = elem_props_get_number(fbx_settings_props, b'OriginalUnitScaleFactor', 1.0)


	return true;
}

} /* namespace fbx */
