#pragma warning(disable : 4819)
//
// Created by jun on 2021/06/14.
//
#include <vector>
#include <sstream>
#include<any>
#include <fstream>
#include <cassert>
#include <filesystem>

#ifdef __ANDROID__
#include <android/log.h>
#else   /* __ANDROID__ */
#include "../CG3DCom.h"
#endif  /* __ANDROID__ */
#include "CG3D.h"
#include "FBX.h"
#include "import_fbx.h"
#include "MatVec.h"

namespace fbx {
	/**********/
	/* load() */
	/**********/
	bool import_fbx::load(std::map<std::string, std::vector<char>> &AssetsData, const std::string& ModelName) {
	//		aOperator=<bpy_struct, IMPORT_SCENE_OT_fbx("IMPORT_SCENE_OT_fbx") at 0x00000255955C5C58>
			Context		aContext;		aContext.Scene.UnitSetting.System = UnitSettingSystem::METRIC;
			bool		aUuseManualOrientation = false;
			m::Axis		aAxisForward = m::Axis::_Z;
			m::Axis		aAxisUp = m::Axis::Y;
			double		aGlobalScale = 1.0;
			bool		aBakeSpaceTransform = false;
			bool		aUseCustomNormals = true;
			bool		aUseImageSearch = true;
			bool		aUseAlphaDecals = false;
			double		aDecalOffset = 0.0;
			bool		aUseAnim = true;
			double		aAnimOffset = 1.0;
			bool		aUseSubsurf = false;
			bool		aUseCustomProps = true;
			bool		aUseCustomPropsEnumAsString = true;
			bool		aIgnoreLeafBones = false;
			bool		aForceConnectChildren = false;
			bool		aAutomaticBoneOrientation = false;
			m::Axis		aPrimaryBoneAxis = m::Axis::Y;
			m::Axis		aSecondaryBoneAxis = m::Axis::X;
			bool		aUsePrepostRot = true;
	using ibinstream = std::istringstream;

		const std::vector<char> &ModelData = AssetsData.at(ModelName);
		ibinstream ibs(std::string(ModelData.begin(), ModelData.end()));

		ibs.seekg(0, std::ios::end);
		size_t filesize = (size_t)ibs.tellg();
		ibs.seekg(0, std::ios::beg);
		size_t fpos = (size_t)ibs.tellg();

		/* MAGICWORD */
		const char magicword[23] = {'K','a','y','d','a','r','a',' ','F','B','X',' ','B','i','n','a','r','y',' ',' ',0x00,0x1A,0x00};
		char fbxmagic[sizeof(magicword)] = {};
		ibs.read(fbxmagic, sizeof(magicword));
		if (std::memcmp(magicword, fbxmagic, sizeof(magicword)) != 0) {
			__android_log_print(ANDROID_LOG_DEBUG, "aaaaa", "aaaaa Load(%s) Failed!! Unmatch MAGICWORD!!\n", fbxmagic);
			return false;
		}

		/* FBX??????????????? */
		int fbxversion;
		ibs.read(reinterpret_cast<char*>(&fbxversion), sizeof(int));

		__android_log_print(ANDROID_LOG_DEBUG, "aaaaa", "aaaaa FBX version(%d)\n", fbxversion);

		/* FBXUtil????????? */
		bool ret = FbxUtil::init((Version)fbxversion);
		if (!ret) return false;


#ifndef __ANDROID__
		/**************************/
		/* ????????????????????????????????? */
		/**************************/
		//UTF-8??????UTF-16?????????
		const int nSize = ::MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)"D:\\testaaaa??????\\?????????????????????.log", -1, NULL, 0);
		BYTE* buffUtf16 = new BYTE[nSize * 2 + 2];
		::MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)"D:\\testaaaa??????\\?????????????????????.log", -1, (LPWSTR)buffUtf16, nSize);
		//UTF-16??????Shift-JIS?????????
		const int nSizeSJis = ::WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)buffUtf16, -1, NULL, 0, NULL, NULL);
		BYTE* buffSJis = new BYTE[nSizeSJis * 2];
		ZeroMemory(buffSJis, nSizeSJis * 2);
		::WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)buffUtf16, -1, (LPSTR)buffSJis, nSizeSJis, NULL, NULL);
		BYTE dstStr[100] = { 0 };
		memcpy(dstStr, buffSJis, nSizeSJis * 2);
		delete[] buffUtf16;
		delete[] buffSJis;
		char cDstStr[100] = {};
		memcpy(cDstStr, dstStr, sizeof(cDstStr));

		std::ofstream ofs(cDstStr);
		ofs.close();
#endif /*__ANDROID__*/

		/**************************/
		/* 001 ??????????????????????????? */
		/**************************/
		__android_log_print(ANDROID_LOG_INFO, "aaaaa", "001 ??????????????????????????? s %d", __LINE__);
		std::vector<FbxElem> rootElem;
		{
			while(true) {
				FbxElem allElems = FbxUtil::readElements(ibs);
				if(allElems.end_offset == 0)
					break;
#ifndef __ANDROID__
				//UTF-8??????UTF-16?????????
			const int nSize = ::MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)"D:\\testaaaalog\\?????????????????????.log", -1, NULL, 0);
			BYTE* buffUtf16 = new BYTE[nSize * 2 + 2];
			::MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)"D:\\testaaaalog\\?????????????????????.log", -1, (LPWSTR)buffUtf16, nSize);
			//UTF-16??????Shift-JIS?????????
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

			std::ofstream ofs(cDstStr, std::ios::app);
	//		std::ofstream ofs(cDstStr);
			ofs << allElems.toString(0);
			ofs.close();
#endif /*__ANDROID__*/
				rootElem.push_back(allElems);
			}
		}

		/**************************/
		/* 002 GlobalSettings?????? */
		/**************************/
		__android_log_print(ANDROID_LOG_INFO, "aaaaa", "002 GlobalSettings?????? s %d", __LINE__);
		/* GlobalSettings??????????????? */
		auto gsitr = std::find_if(rootElem.begin(), rootElem.end(), [](const FbxElem &item){ return item.id=="GlobalSettings"; });
		assert((gsitr != rootElem.end()) && "error ???????????????!! GlobalSettings???????????????!!");

		auto gsP70itr = std::find_if(gsitr->elems.begin(), gsitr->elems.end(), [](const FbxElem& item) { return item.id == "Properties70"; });
		assert((gsP70itr != gsitr->elems.end()) && "error ???????????????!! Properties70???????????????!!");

		FbxElem &gs  = *gsitr;
		FbxElem &gsP70 = *gsP70itr;

		double unitscale	= FbxUtil::getPropNumber(gsP70, "UnitScaleFactor", 1.0);
		double unitscaleOrg	= FbxUtil::getPropNumber(gsP70, "OriginalUnitScaleFactor", 1.0);
		double globalscale	= aGlobalScale * (unitscale / Units2FbxFactor(aContext.Scene));

		m::Axis axisforward;
		m::Axis axisup;
		if (!aUuseManualOrientation) {
			/* ?????????????????? */
			std::int64_t axisup1 = FbxUtil::getPropInteger(gsP70, "UpAxis", 2);
			std::int64_t axisup2 = FbxUtil::getPropInteger(gsP70, "UpAxisSign", 1);
			std::pair<std::int64_t, std::int64_t> axisup_pair = { axisup1, axisup2 };

			/* ?????????????????? */
			std::int64_t axisforward1 = FbxUtil::getPropInteger(gsP70, "FrontAxis", 1);
			std::int64_t axisforward2 = FbxUtil::getPropInteger(gsP70, "FrontAxisSign", 1);
			std::pair<std::int64_t, std::int64_t> axisforward_pair = { axisforward1, axisforward2 };

			/* ?????????????????? */
			std::int64_t axiscoord1 = FbxUtil::getPropInteger(gsP70, "CoordAxis", 0);
			std::int64_t axiscoord2 = FbxUtil::getPropInteger(gsP70, "CoordAxisSign", 1);
			std::pair<std::int64_t, std::int64_t> axiscoord_pair = { axiscoord1, axiscoord2 };

			/* ??????????????????????????? */
			std::tuple<std::pair<std::int64_t, std::int64_t>,
				std::pair<std::int64_t, std::int64_t>,
				std::pair<std::int64_t, std::int64_t>> axiskey = { axisup_pair, axisforward_pair, axiscoord_pair };

			std::pair<m::Axis, m::Axis> axis = RIGHT_HAND_AXES_RR.at(axiskey);
			axisforward = axis.second;
			axisup = axis.first;
		}

		/* ?????????????????? */
		m::Matrix4f ScaleM = m::MatVec::createScale((float)globalscale, (float)globalscale, (float)globalscale);
		/* ????????????????????? */
		m::Matrix4f AxisConvM = m::MatVec::createAxisConversion(axisforward, axisup);
		/* ??????????????????????????? */
		m::Matrix4f GlocalM = m::MatVec::MultMatrix(ScaleM, AxisConvM);
		/* ?????????????????????????????? */
		m::Matrix4f GlocalInvM = GlocalM.getInverse();
		/* ??????????????????????????????????????? */
		m::Matrix4f GlocalInvTranceposeM = GlocalInvM.getTrancepose();

		m::Matrix4f BoneCorrectionMatrix;
		if (!aAutomaticBoneOrientation) {
			if((aPrimaryBoneAxis == m::Axis::Y) && (aSecondaryBoneAxis == m::Axis::X)) {
				BoneCorrectionMatrix.setIdentity();
			}
			else {
				BoneCorrectionMatrix = m::MatVec::createAxisConversion(m::Axis::X, m::Axis::Y, aSecondaryBoneAxis, aPrimaryBoneAxis);
			}
		}

		/* Custom????????????????????? */
		double customfps = FbxUtil::getPropNumber(gsP70, "CustomFrameRate", 25.0);

		/* TimeMode */
		int timemode = FbxUtil::getPropEnum(gsP70, "TimeMode", 0);

		/* realfps */
		double realfps = customfps;
		auto findit = std::find_if(FBX_FRAMERATES_RR.begin(), FBX_FRAMERATES_RR.end(), [timemode](const std::pair<int, double> &item){
			return item.first == timemode;
		});
		if (findit != FBX_FRAMERATES_RR.end()) {
			if(findit->second < 0)
				realfps = 25.0f;
			else
				realfps = findit->second;
		}

		/* TODO : ??????????????????????????????????????? */
		aContext.Scene.Render.Fsp		= round(realfps);
		aContext.Scene.Render.FspBase	= aContext.Scene.Render.Fsp / realfps;

		FbxImportSettings settings = {
			//.Repeat					= ???
			.toAxeiss					= {axisup, axisforward},
			.globalMatrix				= GlocalM,
			.globalScale				= globalscale,
			.bakeSpaceTransform			= aBakeSpaceTransform,
			.globalMatrixInv			= std::move(GlocalInvM),
			.globalMatrixInvTransposed	= std::move(GlocalInvTranceposeM),
			.useCustomNormals			= aUseCustomNormals,
			.useImageSearch				= aUseImageSearch,
			.useAlphaDecals				= aUseAlphaDecals,
			.decalOffset				= aDecalOffset,
			.useAnim					= aUseAnim,
			.animOffset					= aAnimOffset,
			.useSubsurf					= aUseSubsurf,
			.useCustomProps				= aUseCustomProps,
			.useCustomPropsEnumAsString = aUseCustomPropsEnumAsString,
			//.nodalMaterialWrapMap		= ???,
			//.imageCache				= ???,
			.ignoreLeafBones			= aIgnoreLeafBones,
			.forceConnectChildren		= aForceConnectChildren,
			.automaticBoneOrientation	= aAutomaticBoneOrientation,
			.boneCorrectionMatrix		= std::move(BoneCorrectionMatrix),
			.usePrepostRot				= aUsePrepostRot,
		};

		/*********************/
		/* 003 Templates?????? */
		/*********************/
		__android_log_print(ANDROID_LOG_INFO, "aaaaa", "003 Templates?????? s %d", __LINE__);
		std::map<std::pair<std::string, std::string>, FbxElem> FbxTemplates = {};
		{
			/* Definitions??????????????? */
			auto defsitr = std::find_if(rootElem.begin(), rootElem.end(), [](const FbxElem& item) { return item.id == "Definitions"; });
			if (defsitr != rootElem.end()) {
				FbxElem &defs = *defsitr;
				for (FbxElem &fbxdef : defs.elems) {
					if (fbxdef.id == "ObjectType") {
						for (FbxElem &fbxsubdef : fbxdef.elems) {
							if (fbxsubdef.id == "PropertyTemplate") {
								assert((fbxdef.props[0].DataType() == General::Type::String)    && "error ???????????????!! ??????strng?????????!!");
								assert((fbxsubdef.props[0].DataType() == General::Type::String) && "error ???????????????!! ??????strng?????????!!");
								std::string key1 = fbxdef.props[0].getData<std::string>();
								std::string key2 = fbxsubdef.props[0].getData<std::string>();
								std::pair<std::string, std::string> key = { key1, key2 };
								FbxTemplates.insert({ key, fbxsubdef });
							}
						}
					}
				}
			}
		}

		/*****************/
		/* 004 Nodes?????? */
		/* ?????? : http://download.autodesk.com/us/fbx/20112/FBX_SDK_HELP/index.html?url=WS73099cc142f487551fea285e1221e4f9ff8-7fda.htm,topicNumber=d0e6388 */
		/*****************/
		__android_log_print(ANDROID_LOG_INFO, "aaaaa", "004 Nodes?????? s %d", __LINE__);
		/* Tables: (FBX_byte_id ->[FBX_data, None or Blender_datablock]) */
		std::map<std::int64_t, std::tuple<FbxElem, std::any>> FbxTableNodes = {};
		{
			auto nodesitr = std::find_if(rootElem.begin(), rootElem.end(), [](const FbxElem& item) { return item.id == "Objects"; });
			assert((nodesitr != rootElem.end()) && "error ???????????????!! Objects???????????????!!");

			FbxElem &nodes = *nodesitr;
			for (FbxElem &fbxobj : nodes.elems) {
				assert((fbxobj.props.size() >= 3) && "error ??????????????????3??????????????????????????????!!");
				assert(((fbxobj.props[0].DataType() == General::Type::Int64) && (fbxobj.props[1].DataType() == General::Type::String) && (fbxobj.props[2].DataType() == General::Type::String)) && "error ??????????????????int64,string,string??????????????????!!");
				std::int64_t fbxuuid = fbxobj.props[0].getData<std::int64_t>();
				FbxTableNodes.insert({ fbxuuid, {fbxobj, {}} });
			}
		}

		/***********************/
		/* 005 Connections?????? */
		/***********************/
		__android_log_print(ANDROID_LOG_INFO, "aaaaa", "005 Connections?????? s %d", __LINE__);
		{
			auto consitr = std::find_if(rootElem.begin(), rootElem.end(), [](const FbxElem& item) { return item.id == "Connections"; });
			assert((consitr != rootElem.end()) && "error ???????????????!! Connections???????????????!!");
			FbxElem &cons = *consitr;

			std::map<std::int64_t, std::map<std::int64_t, FbxElem>> FbxConnectionMap = {};
			std::map<std::int64_t, std::map<std::int64_t, FbxElem>> FbxConnectionMap_RR = {};

			for (FbxElem &fbxlink : cons.elems) {
				General &ctype = fbxlink.props[0];
				if ((fbxlink.props.size() >= 3) &&
					(fbxlink.props[1].DataType() == General::Type::Int64) && (fbxlink.props[2].DataType() == General::Type::Int64)) {
					std::int64_t csrc = fbxlink.props[1].getData<std::int64_t>();
					std::int64_t cdst = fbxlink.props[2].getData<std::int64_t>();
					FbxConnectionMap.insert({ csrc, {{cdst, fbxlink}} });
					FbxConnectionMap_RR.insert({ cdst, {{csrc, fbxlink}} });
				}
			}
		}

		/*****************/
		/* 006 Meshes?????? */
		/*****************/
		__android_log_print(ANDROID_LOG_INFO, "aaaaa", "006 Meshes?????? s %d", __LINE__);
		if(FbxTemplates.count({"Geometry", "FbxMesh"}) > 0) {
			//	FbxElem &fbxtmpl = FbxTemplates.at({ "Geometry", "KFbxMesh" });	/* ?????????FBX???7.4????????????????????????????????????K?????????????????????????????????????????? */
			FbxElem &fbxtmpl = FbxTemplates.at({ "Geometry", "FbxMesh" });

			for(auto &FbxTableNode : FbxTableNodes) {
				FbxElem &fbxobj = std::get<0>(FbxTableNode.second);
				if(fbxobj.id != "Geometry")
					continue;

				if (fbxobj.props[fbxobj.props.size()-1].getData<std::string>() == "Mesh") {
					cg::Mesh mesh = FbxUtil::cg3dReadGeometry(fbxtmpl, fbxobj, settings);
					FbxTableNode.second = { std::get<0>(FbxTableNode.second), std::ref(mesh) };
				}
			}
		}

		/********************************/
		/* 007 Materials & Textures?????? */
		/********************************/
		__android_log_print(ANDROID_LOG_INFO, "aaaaa", "007 Materials & Textures?????? s %d", __LINE__);
		/* 007-1 Materials */
		if(FbxTemplates.count({"Material", "FbxSurfacePhong"}) > 0) {
//			FbxElem &fbxtmpl = FbxTemplates.at({ "Material", "KFbxSurfacePhong" });	/* ?????????FBX???7.4????????????????????????????????????K?????????????????????????????????????????? */
			FbxElem &fbxtmpl = FbxTemplates.at({ "Material", "FbxSurfacePhong" });
			for(auto &FbxTableNode : FbxTableNodes) {
				FbxElem &fbxobj = std::get<0>(FbxTableNode.second);
				if(fbxobj.id != "Material")
					continue;

				cg::Material material = FbxUtil::cg3dReadMaterial(fbxtmpl, fbxobj, settings);
				FbxTableNode.second = { std::get<0>(FbxTableNode.second), std::ref(material) };
			}
		}

		std::string modelbasepath = std::filesystem::path(ModelName).parent_path().string();
		/* 007-2 Image & Textures */
		{
//		if (FbxTemplates.contains({ "Texture", "FbxFileTexture" })) {
//			//	?????????FBX???7.4????????????????????????????????????K??????????????????????????????????????????
//			FbxElem &fbxtmpltex = FbxTemplates.at({ "Texture", "FbxFileTexture" });
//			FbxElem &fbxtmplimg = FbxTemplates.at({ "Video", "FbxVideo" });

			/*	Important to run all 'Video' ones first, embedded images are stored in those nodes.
				XXX Note we simplify things here, assuming both matching Videoand Texture will use same file path,
				this may be a bit weak, if issue arise we'll fallback to plain connection stuff... */
			for (auto& FbxTableNode : FbxTableNodes) {
				FbxElem &fbxobj = std::get<0>(FbxTableNode.second);
				if (fbxobj.id != "Video")
					continue;
				cg::Image img = FbxUtil::cg3dReadTextureImage(AssetsData, fbxobj, modelbasepath, settings);
				FbxTableNode.second = { std::get<0>(FbxTableNode.second), std::ref(img) };
			}

			for (auto &FbxTableNode : FbxTableNodes) {
				FbxElem &fbxobj = std::get<0>(FbxTableNode.second);
				if (fbxobj.id != "Texture")
					continue;
				cg::Image img = FbxUtil::cg3dReadTextureImage(AssetsData, fbxobj, modelbasepath, settings);
				FbxTableNode.second = { std::get<0>(FbxTableNode.second), std::ref(img) };
			}
		}

		/***************************/
		/* 008 Cameras & Lamps?????? */
		/***************************/
		__android_log_print(ANDROID_LOG_INFO, "aaaaa", "008 Cameras & Lamps?????? s %d", __LINE__);
		/* 008-1 Cameras?????? */
		if(FbxTemplates.count({ "NodeAttribute", "FbxCamera" }) > 0) {
			assert(false && "?????????????????????????????????????????????!!");
			FbxElem &fbxtmplcamera = FbxTemplates.at({ "NodeAttribute", "FbxCamera" });
		}

		/* 008-2 Lamps?????? */
		if(FbxTemplates.count({ "NodeAttribute", "FbxLight" }) > 0) {
			assert(false && "?????????????????????????????????????????????!!");
			FbxElem &fbxtmpllamps = FbxTemplates.at({ "NodeAttribute", "FbxLight" });
		}

		/******************************/
		/* 009 Objects & Armatures?????? */
		/******************************/
		__android_log_print(ANDROID_LOG_INFO, "aaaaa", "009 Objects & Armatures?????? s %d", __LINE__);
		std::map<std::uint64_t, FbxImportHelperNode> FbxHelperNodes = {{0, FbxImportHelperNode(/*.isRoot=*/true)},};

		/* add fbx nodes */
		FbxElem &&fbxtmplObjsArms = (FbxTemplates.count({ "Model", "FbxNode" })>0) ? FbxTemplates.at({ "Model", "FbxNode" }) : FbxElem();
		for (auto &FbxTableNode : FbxTableNodes) {
			FbxElem &fbxObjObjsArms = std::get<0>(FbxTableNode.second);
			if (fbxObjObjsArms.id != "Model")
				continue;

			auto p70formobj = std::find_if(fbxObjObjsArms.elems.begin(), fbxObjObjsArms.elems.end(), [](const FbxElem &elm){
				return elm.id == "Properties70";
			});
			auto p70formtmpl= std::find_if(fbxtmplObjsArms.elems.begin(), fbxtmplObjsArms.elems.end(), [](const FbxElem &elm){
				return elm.id == "Properties70";
			});
			std::vector<FbxElem> fbxprops = {*p70formobj, *p70formtmpl};


			FBXTransformData transformdata = FbxUtil::cg3dReadObjectTransformPreprocess(fbxprops, fbxObjObjsArms, m::Matrix4f(m::Matrix4f::IDENTITY), aUsePrepostRot);
			std::string name = fbxObjObjsArms.props[2].getData<std::string>();
			bool isbone = (name=="LimbNode" || name=="Limb");

			std::any tmpany = std::get<1>(FbxTableNode.second);
			FbxHelperNodes.insert({ FbxTableNode.first , FbxImportHelperNode(fbxObjObjsArms, tmpany, transformdata, isbone) });
		}

		/* add parent - child relations and add blender data to the node */
		auto fbxConnectionsitr = std::find_if(rootElem.begin(), rootElem.end(), [](const FbxElem &item) { return item.id == "Connections"; });
		const FbxElem &fbxConnections = *fbxConnectionsitr;
		for (const FbxElem &fbxlink : fbxConnections.elems) {
			if (fbxlink.props[0].getData<std::string>() != "OO")
				continue;
			if (fbxlink.props[1].DataType()!= General::Type::Int64 || fbxlink.props[2].DataType() != General::Type::Int64)
				continue;

			std::int64_t c_src = fbxlink.props[1].getData<std::int64_t>();
			std::int64_t c_dst = fbxlink.props[2].getData<std::int64_t>();

			/* ???????????? */
			if (FbxHelperNodes.count(c_dst) == 0)
				continue;
			FbxImportHelperNode &parent = FbxHelperNodes.at(c_dst);

			if (FbxHelperNodes.count(c_src) == 0) {
				/* ???????????? */
				if(FbxTableNodes.count(c_src) == 0)
					continue;
				/* ??????????????? */
				auto [fbxsdata, cg3ddata] = FbxTableNodes.at(c_src);
				if (fbxsdata.id != "Geometry" && fbxsdata.id != "NodeAttribute")
					continue;
				parent.cg3ddata = cg3ddata;
			}
			else {
				/* ???????????? */
				auto child = FbxHelperNodes.at(c_src);
				child._parent = &parent;
			}
		}

		/* find armatures (either an empty below a bone or a new node inserted at the bone */

		/* mark nodes that have bone children */

		/* mark nodes that need a bone to attach child-bones to */

		/* mark leaf nodes that are only required to mark the end of their parent bone */

		/* get the bind pose from pose elements */

		/* get clustersand bind pose */

		/* convert bind poses from global space into local space */

		/* collect armature meshes */

		/* find the correction matrices to align FBX objects with their Blender equivalent */

		/* build the Object/Armature/Bone hierarchy */

		/* Link the Object/Armature/Bone hierarchy */

		/*********************/
		/* 010 ShapeKeys?????? */
		/*********************/

		/********************************/
		/* 011 Subdivision surfaces?????? */
		/********************************/

		/**********************/
		/* 012 Animations?????? */
		/**********************/

		/****************************/
		/* 013 Assign materials?????? */
		/****************************/

		/***************************/
		/* 014 Assign textures?????? */
		/***************************/

		/**************************************/
		/* 015 Cycles z-offset workaround?????? */
		/**************************************/

		return true;
	}
} /* namespace fbx */

